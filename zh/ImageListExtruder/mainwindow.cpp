#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "io.h"
#include "direct.h"
#include <QFileDialog>
#include <sstream>
#include <QMessageBox>
#include <QKeyEvent>
#include "exportallthread.h"
#include "progressdialog.h"

using namespace std;

ExportAllThread *exportAllThread=NULL;

int strnumcmp(const char *s1,const char *s2){
    //比较可能有编号的字符串s1和s2，不优先区分大小写。
    int i=0;
    int nummode1=0;
    int nummode2=0;
    int numcmp=-2;
    unsigned char c01;
    unsigned char c02;
    unsigned char c1;
    unsigned char c2;
    int casecmp=0;
    for(i=0;s1[i]!=0 && s2[i]!=0;i++){
        c01=s1[i];
        c02=s2[i];
        if(c01>='0' && c01<='9'){
            nummode1=true;
        }else{
            nummode1=false;
        }
        if(c02>='0' && c02<='9'){
            nummode2=true;
        }else{
            nummode2=false;
        }
        if(nummode1 && nummode2 && numcmp==-2){
            numcmp=0;
        }
        if(numcmp==0){
            if(c01>c02){
                numcmp=1;
            }else if(c01<c02){
                numcmp=-1;
            }
        }
        if(numcmp>-2){
            if(nummode1 && !nummode2){
                return 1;
            }else if(!nummode1 && nummode2){
                return -1;
            }else if(!nummode1 && !nummode2){
                if(numcmp!=0){
                    return numcmp;
                }
            }else{
                continue;
            }
        }
        if(!nummode1 || !nummode2){
            numcmp=-2;
        }
        if(c01>='A' && c01<='Z'){
            c1=c01+32;
        }else{
            c1=c01;
        }
        if(c02>='A' && c02<='Z'){
            c2=c02+32;
        }else{
            c2=c02;
        }
        if(c1>c2){
            return 1;
        }else if(c1<c2){
            return -1;
        }else if(casecmp==0){
            if(c01>c02){
                casecmp=1;
            }else if(c01<c02){
                casecmp=-1;
            }
        }
    }
    if(nummode1 && nummode2){
        c01=s1[i];
        c02=s2[i];
        if(c01!=0){
            return 1;
        }else if(c02!=0){
            return -1;
        }else if(numcmp==1){
            return 1;
        }else if(numcmp==-1){
            return -1;
        }else{
            return casecmp;
        }
    }else{
        c01=s1[i];
        c02=s2[i];
        if(c01!=0){
            return 1;
        }else if(c02!=0){
            return -1;
        }else{
            return casecmp;
        }
    }
    return 0;
}

int strnumcmp(string &s1,string &s2){
    //比较可能有编号的字符串s1和s2，不优先区分大小写。
    return strnumcmp(s1.c_str(),s2.c_str());
}

void strNumSort(vector<string> &strArrSrc,vector<string> &strArrOut){
    //将vector<string>用strnumcmp的比较方法排序
    int length=strArrSrc.size();
    if(length<=0){
        strArrOut.clear();
        return;
    }

    int *arr=new int[length];
    int *arr2=new int[length];

    int i=0;


    for(i=0;i<length;i++){
        arr[i]=i;
        arr2[i]=i;
    }
    i=0;

    int j=0;
    int k=0;
    int l=0;
    int m=0;
    int n=0;
    int a=1;
    int b=a<<1;

    while(a<length){
        i=0;
        j=a;
        k=a;
        l=b;
        m=0;
        if(k>length){
            k=length;
        }
        if(l>length){
            l=length;
        }
        while(m<length){
            if(n==0){
                if(i>=k || j<l && strnumcmp(strArrSrc[arr[i]],strArrSrc[arr[j]])>0){
                    arr2[m]=arr[j];
                    j++;
                }else if(i<k){
                    arr2[m]=arr[i];
                    i++;
                }
            }else{
                if(i>=k || j<l && strnumcmp(strArrSrc[arr2[i]],strArrSrc[arr2[j]])>0){
                    arr[m]=arr2[j];
                    j++;
                }else if(i<k){
                    arr[m]=arr2[i];
                    i++;
                }
            }
            m++;
            if(m>=l){
                i=l;
                j=l+a;
                k+=b;
                l+=b;
                if(k>length){
                    k=length;
                }
                if(l>length){
                    l=length;
                }
            }
        }
        n=1-n;
        a=b;
        b=b<<1;
    }

    if((int)(strArrOut.size())!=length){
        strArrOut.resize(length);
    }
    for(i=0;i<length;i++){
        if(n==0){
            strArrOut[i]=strArrSrc[arr[i]];
        }else{
            strArrOut[i]=strArrSrc[arr2[i]];
        }
    }
    delete []arr;
    delete []arr2;
}

string _t(string str0){
    return QString::fromLocal8Bit(str0.c_str()).toStdString();
}

string _a(string str0){
    QString qstr=str0.c_str();
    return qstr.toLocal8Bit().data();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageEraserMaxCount=5;

    imageList.resize(0);
    imageEraserString="";
    currentImageIndex=0;
    ui->label_imageName->adjustSize();
    ui->pushButton_prev->setEnabled(false);
    ui->pushButton_next->setEnabled(false);
    ui->pushButton_zoomOut->setEnabled(false);
    ui->pushButton_zoomIn->setEnabled(false);
    ui->lineEdit_bgColorView->setReadOnly(true);
    QColor color=this->palette().window().color();
    int bgc=color.red()<<16|color.green()<<8|color.blue();
    char colorc[16];
    snprintf(colorc,15,"%06x",bgc);
    ui->lineEdit_bgColor->setText(colorc);
    ui->lineEdit_bgColorView->setStyleSheet("background:#"+QString(colorc));

    ui->widget->pWnd=this;
    ui->widget->bgc=bgc;

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(OnPushButton1()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(OnPushButton2()));
    connect(ui->pushButton_prev,SIGNAL(clicked()),this,SLOT(OnPushButton_prev()));
    connect(ui->pushButton_next,SIGNAL(clicked()),this,SLOT(OnPushButton_next()));
    connect(ui->pushButton_zoomOut,SIGNAL(clicked()),this,SLOT(OnPushButton_zoomOut()));
    connect(ui->pushButton_zoomIn,SIGNAL(clicked()),this,SLOT(OnPushButton_zoomIn()));
    connect(ui->pushButton_exportAll,SIGNAL(clicked()),this,SLOT(OnPushButton_exportAll()));

    connect(ui->lineEdit_bgColor,SIGNAL(textChanged(QString)),this,SLOT(OnBgColor()));

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(OnSlider()));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(OnSlider()));
    connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(OnSlider()));

    OnSlider();

    ui->pushButton->installEventFilter(this);
    ui->pushButton_2->installEventFilter(this);
    ui->pushButton_prev->installEventFilter(this);
    ui->pushButton_next->installEventFilter(this);
    ui->pushButton_zoomIn->installEventFilter(this);
    ui->pushButton_zoomOut->installEventFilter(this);
    ui->pushButton_exportAll->installEventFilter(this);
    ui->lineEdit_bgColor->installEventFilter(this);
    ui->widget->installEventFilter(this);
    ui->horizontalSlider->installEventFilter(this);
    ui->horizontalSlider_2->installEventFilter(this);
    ui->horizontalSlider_3->installEventFilter(this);




    exportAllThread=new ExportAllThread();
    exportAllThread->pWnd=this;

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnPushButton1(){
    QStringList list=QFileDialog::getOpenFileNames(this,"选择图片序列","","图片文件(*.png *.bmp *.jpg)");
    if(list.size()==0){
        return;
    }
    vector<string> imageList0;
    imageList0.resize(list.size());

    for(int i=0;i<(int)(imageList0.size());i++){
        imageList0[i]=list[i].toStdString();
    }
    imageList.resize(list.size());
    strNumSort(imageList0,imageList);
    if(imageList.size()==0){
        ui->label_List->setText("<未指定>");
        ui->label_imageName->setText("<未指定>");
        imagePreview=QImage();
    }else if(imageList.size()==1){
        ui->label_List->setText(imageList[0].c_str());
    }else if(imageList.size()==2){
        ui->label_List->setText(("\""+imageList[0]+"\",\n\""+imageList[imageList.size()-1]+"\"").c_str());
    }else{
        ui->label_List->setText(("\""+imageList[0]+"\",...\n\""+imageList[imageList.size()-1]+"\"").c_str());
    }
    currentImageIndex=0;
    ui->pushButton_prev->setEnabled(imageList.size()>=2 && currentImageIndex>0);
    ui->pushButton_next->setEnabled(imageList.size()>=2 && currentImageIndex<(int)(imageList.size())-1);
    ui->pushButton_zoomOut->setEnabled(!imageList.empty() && !ui->widget->willScale);
    ui->pushButton_zoomIn->setEnabled(!imageList.empty() && ui->widget->willScale);
    if(currentImageIndex>=0 && currentImageIndex<(int)(imageList.size())){
        int n=imageList[currentImageIndex].rfind('/');
        if(n>=0 && n<(int)(imageList[currentImageIndex].length())){
            ui->label_imageName->setText(imageList[currentImageIndex].substr(n+1).c_str());
        }else{
            ui->label_imageName->setText(imageList[currentImageIndex].c_str());
        }
        ui->label_imageName->adjustSize();
        updateImagePreview();
        ui->widget->restrictPosition();
        ui->widget->update();
    }
}

void MainWindow::OnPushButton2(){
    QStringList eraser0=QFileDialog::getOpenFileNames(this,"选择掩模文件","","图片文件(*.png *.bmp *.jpg)");
    if(eraser0.empty()){
        return;
    }
    if(eraser0.size()>imageEraserMaxCount){
        ostringstream ostr;
        ostr<<"掩模文件选取过多，最大支持"<<imageEraserMaxCount<<"个。";
        QMessageBox::information(this,"",ostr.str().c_str());
        return;
    }
    imageEraserString="";
    imageEraserList.clear();
    imageEraserList.resize(eraser0.size());
    int i=0,j=0;
    for(i=0;i<(int)(eraser0.size());i++){
        imageEraserList[j]=QImage(eraser0[i]);
        if(imageEraserList[j].isNull()){
            continue;
        }
        if(imageEraserList[j].format()!=QImage::Format_ARGB32){
            imageEraserList[j]=imageEraserList[j].convertToFormat(QImage::Format_ARGB32);
        }
        imageEraserString+="\""+eraser0[i].toStdString()+"\"";
        if(i<(int)(eraser0.size())-1){
            imageEraserString+=",\n";
        }
        j++;
    }
    if(j<(int)(imageEraserList.size())){
        imageEraserList.resize(j);
    }
    ui->label_Eraser->setText(imageEraserString.c_str());
    updateImagePreview();
    ui->widget->restrictPosition();
    ui->widget->update();
}

void MainWindow::OnPushButton_prev(){
    if(currentImageIndex<=0){
        return;
    }
    currentImageIndex--;
    ui->pushButton_prev->setEnabled(imageList.size()>=2 && currentImageIndex>0);
    ui->pushButton_next->setEnabled(imageList.size()>=2 && currentImageIndex<(int)(imageList.size())-1);
    ui->pushButton_zoomOut->setEnabled(!imageList.empty() && !ui->widget->willScale);
    ui->pushButton_zoomIn->setEnabled(!imageList.empty() && ui->widget->willScale);
    if(currentImageIndex>=0 && currentImageIndex<(int)(imageList.size())){
        int n=imageList[currentImageIndex].rfind('/');
        if(n>=0 && n<(int)(imageList[currentImageIndex].length())){
            ui->label_imageName->setText(imageList[currentImageIndex].substr(n+1).c_str());
        }else{
            ui->label_imageName->setText("");
        }
        ui->label_imageName->adjustSize();
        updateImagePreview();
        ui->widget->restrictPosition();
        ui->widget->update();
    }
}

void MainWindow::OnPushButton_next(){
    if(currentImageIndex>=(int)(imageList.size())-1){
        return;
    }
    currentImageIndex++;
    ui->pushButton_prev->setEnabled(imageList.size()>=2 && currentImageIndex>0);
    ui->pushButton_next->setEnabled(imageList.size()>=2 && currentImageIndex<(int)(imageList.size())-1);
    ui->pushButton_zoomOut->setEnabled(!imageList.empty() && !ui->widget->willScale);
    ui->pushButton_zoomIn->setEnabled(!imageList.empty() && ui->widget->willScale);
    if(currentImageIndex>=0 && currentImageIndex<(int)(imageList.size())){
        int n=imageList[currentImageIndex].rfind('/');
        if(n>=0 && n<(int)(imageList[currentImageIndex].length())){
            ui->label_imageName->setText(imageList[currentImageIndex].substr(n+1).c_str());
        }else{
            ui->label_imageName->setText("");
        }
        ui->label_imageName->adjustSize();
        updateImagePreview();
        ui->widget->restrictPosition();
        ui->widget->update();
    }
}

void MainWindow::OnPushButton_zoomOut(){
    ui->widget->willScale=true;
    ui->widget->posx=0;
    ui->widget->posy=0;

    ui->pushButton_zoomOut->setEnabled(!imageList.empty() && !ui->widget->willScale);
    ui->pushButton_zoomIn->setEnabled(!imageList.empty() && ui->widget->willScale);

    ui->widget->restrictPosition();
    ui->widget->update();

}

void MainWindow::OnPushButton_zoomIn(){
    ui->widget->posx=!imagePreview.isNull()?(ui->widget->width()-imagePreview.width())>>1:0;
    ui->widget->posy=!imagePreview.isNull()?(ui->widget->height()-imagePreview.height())>>1:0;
    ui->widget->willScale=false;

    ui->pushButton_zoomOut->setEnabled(!imageList.empty() && !ui->widget->willScale);
    ui->pushButton_zoomIn->setEnabled(!imageList.empty() && ui->widget->willScale);

    ui->widget->restrictPosition();
    ui->widget->update();

}

void MainWindow::OnPushButton_exportAll(){
    if(exportAllThread->isRunning()){
        //QMessageBox::critical(this,"","，无法导出，另一个线程正在运行。");
        return;
    }
    if(imageList.empty()){
        QMessageBox::information(this,"","图片序列不能为空。");
        return;
    }
    /*if(imageEraser.isNull()){
        QMessageBox::information(this,"","必须指定掩模图像。");
        return;
    }
    if(ui->horizontalSlider_2->value()<0){
        QMessageBox::information(this,"","最大色差值必须大于或等于零。");
        return;
    }*/
    int i,j;
    i=0;
    j=imageList[0].rfind('/');
    string path="";
    if(j>=0){
        path=imageList[0].substr(0,j+1);
    }
    string extrudeDir0="extruded";
    string extrudeDir=extrudeDir0;
    ostringstream ostr;
    i=-1;
    do{
        i++;
        ostr.str("");
        if(i==0){
            ostr<<path<<extrudeDir0<<"/";
        }else{
            ostr<<path<<extrudeDir0<<i<<"/";
        }
    }while(_access(_a(ostr.str()).c_str(),0)==0);

    if(i>0){
        ostr.str("");
        ostr<<extrudeDir0<<i;
        extrudeDir=ostr.str();
    }
    string patht=path+extrudeDir+"/";
    if(QMessageBox::question(this,"",("确实要将结果保存到\""+patht+"\"下？").c_str(),QMessageBox::Yes|QMessageBox::No)!=QMessageBox::Yes){
        return;
    }
    if(_mkdir(_a(patht).c_str())!=0){
        QMessageBox::critical(this,"","建立文件夹失败。");
        return;
    }

    exportAllThread->patht=patht;
    exportAllThread->progress=0;
    exportAllThread->totalCount=this->imageList.size();
    exportAllThread->start();

    ProgressDialog dlg(this);
    dlg.exec();

    //QMessageBox::information(this,"","导出完成。");
}

bool MainWindow::eventFilter(QObject *object,QEvent *event){
    if(event->type()==QEvent::KeyPress){
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
        if(keyEvent->key()==Qt::Key_Left && object!=ui->lineEdit_bgColor){
            if(ui->pushButton_prev->isEnabled()){
                ui->pushButton_prev->setFocus();
                OnPushButton_prev();
                if(!ui->pushButton_prev->isEnabled() && ui->pushButton_next->isEnabled()){
                    ui->pushButton_next->setFocus();
                }
            }
            return true;
        }
        if(keyEvent->key()==Qt::Key_Right && object!=ui->lineEdit_bgColor){
            if(ui->pushButton_next->isEnabled()){
                ui->pushButton_next->setFocus();
                OnPushButton_next();
                if(ui->pushButton_prev->isEnabled() && !ui->pushButton_next->isEnabled()){
                    ui->pushButton_prev->setFocus();
                }
            }
            return true;
        }
        if((keyEvent->key()==Qt::Key_Down || keyEvent->key()=='-') && object!=ui->lineEdit_bgColor){
            if(ui->pushButton_zoomOut->isEnabled()){
                OnPushButton_zoomOut();
            }
            return true;
        }
        if((keyEvent->key()==Qt::Key_Up || keyEvent->key()=='+' || keyEvent->key()=='=') && object!=ui->lineEdit_bgColor){
            if(ui->pushButton_zoomIn->isEnabled()){
                OnPushButton_zoomIn();
            }
            return true;
        }
        if(keyEvent->key()==Qt::Key_A && object!=ui->lineEdit_bgColor){
            if(!ui->widget->willScale && !imagePreview.isNull()){
                ui->widget->posx++;
                ui->widget->restrictPosition();
                ui->widget->repaint();
            }
            return true;
        }
        if(keyEvent->key()==Qt::Key_W && object!=ui->lineEdit_bgColor){
            if(!ui->widget->willScale && !imagePreview.isNull()){
                ui->widget->posy++;
                ui->widget->restrictPosition();
                ui->widget->repaint();
            }
            return true;
        }
        if(keyEvent->key()==Qt::Key_D && object!=ui->lineEdit_bgColor){
            if(!ui->widget->willScale && !imagePreview.isNull()){
                ui->widget->posx--;
                ui->widget->restrictPosition();
                ui->widget->repaint();
            }
            return true;
        }
        if(keyEvent->key()==Qt::Key_S && object!=ui->lineEdit_bgColor){
            if(!ui->widget->willScale && !imagePreview.isNull()){
                ui->widget->posy--;
                ui->widget->restrictPosition();
                ui->widget->repaint();
            }
            return true;
        }
        if(keyEvent->key()!=Qt::Key_Return){
            return QMainWindow::eventFilter(object, event);
        }
        if(object==ui->pushButton){
            OnPushButton1();
        }else if(object==ui->pushButton_2){
            OnPushButton2();
        }else if(object==ui->pushButton_prev){
            OnPushButton_prev();
            if(!ui->pushButton_prev->isEnabled() && ui->pushButton_next->isEnabled()){
                ui->pushButton_next->setFocus();
            }
        }else if(object==ui->pushButton_next){
            OnPushButton_next();
            if(ui->pushButton_prev->isEnabled() && !ui->pushButton_next->isEnabled()){
                ui->pushButton_prev->setFocus();
            }
        }else if(object==ui->pushButton_zoomOut){
            OnPushButton_zoomOut();
            if(ui->pushButton_prev->isEnabled() && !ui->pushButton_next->isEnabled()){
                ui->pushButton_prev->setFocus();
            }
        }else if(object==ui->pushButton_zoomIn){
            OnPushButton_zoomIn();
        }else if(object==ui->pushButton_exportAll){
            OnPushButton_exportAll();
        }
    }
    return QMainWindow::eventFilter(object, event);
}

void MainWindow::OnBgColor(){
    int bgc=strtol(ui->lineEdit_bgColor->text().toStdString().c_str(),NULL,16);
    ui->widget->bgc=bgc;
    char colorc[16];
    snprintf(colorc,15,"%06x",bgc);
    //ui->lineEdit_bgColor->setText(colorc);
    ui->lineEdit_bgColorView->setStyleSheet("background:#"+QString(colorc));
    ui->widget->restrictPosition();
    ui->widget->update();
}

void MainWindow::OnSlider(){
    ostringstream ostr;
    ostr<<ui->horizontalSlider->value();
    ui->label_arg1->setText(ostr.str().c_str());
    ostr.str("");
    ostr<<ui->horizontalSlider_2->value();
    ui->label_arg2->setText(ostr.str().c_str());
    ostr.str("");
    ostr<<ui->horizontalSlider_3->value()<<"%";
    ui->label_arg3->setText(ostr.str().c_str());
    updateImagePreview();
    ui->widget->restrictPosition();
    ui->widget->update();
}

void MainWindow::updateImagePreview(int index){
    if(index<0){
        index=currentImageIndex;
    }
    if(index<0 || index>=(int)(imageList.size())){
        imagePreview=QImage();
        return;
    }
    QImage imgSrc=QImage(QString::fromStdString(imageList[index]));
    if(imgSrc.isNull()){
        imagePreview=QImage();
        return;
    }



    int dcolormin=ui->horizontalSlider->value();
    int dcolormax=ui->horizontalSlider_2->value();
    int shrinkRate=ui->horizontalSlider_3->value();
    if(dcolormin>dcolormax){
        dcolormin=dcolormax;
    }

    bool willErase=(dcolormax>=0 && !imageEraserList.empty());

    if(!willErase && shrinkRate==0){
        imagePreview=imgSrc.convertToFormat(QImage::Format_ARGB32);
        return;
    }
    if(imagePreview.isNull() || imagePreview.width()!=imgSrc.width() || imagePreview.height()!=imgSrc.height()){
        imagePreview=QImage(imgSrc.width(),imgSrc.height(),QImage::Format_ARGB32);
    }
    if(imgSrc.format()!=QImage::Format_ARGB32){
        imgSrc=imgSrc.convertToFormat(QImage::Format_ARGB32);
    }
    unsigned char *mByte0=imgSrc.bits();
    unsigned char *pByte0=imagePreview.bits();
    unsigned char **eByte0=NULL;
    unsigned char *mByte=NULL;
    unsigned char *pByte=NULL;
    unsigned char *eByte=NULL;
    int wid=imagePreview.width();
    int hei=imagePreview.height();
    int *wid0=NULL;
    int *hei0=NULL;
    int dr;
    int dg;
    int db;
    int da;
    int dmax0;
    int dmax0min;
    int widthStep=imagePreview.bytesPerLine();
    int *widthStep0=NULL;
    int bytesPerPixel=imagePreview.depth()>>3;
    if(bytesPerPixel<4 || widthStep!=imgSrc.bytesPerLine() || imagePreview.depth()!=imgSrc.depth()){
        imagePreview=QImage();
        return;
    }
    int i,j,k;

    if(willErase && !imageEraserList.empty()){
        int eraserCount=imageEraserList.size();
        eByte0=new unsigned char *[eraserCount];
        wid0=new int[eraserCount];
        hei0=new int[eraserCount];
        widthStep0=new int[eraserCount];
        for(k=0;k<eraserCount;k++){
            if(!imageEraserList[k].isNull() && imagePreview.depth()==imageEraserList[k].depth()){
                eByte0[k]=imageEraserList[k].bits();
                wid0[k]=imageEraserList[k].width();
                hei0[k]=imageEraserList[k].height();
                widthStep0[k]=imageEraserList[k].bytesPerLine();
            }else{
                eByte0[k]=NULL;
                wid0[k]=0;
                hei0[k]=0;
                widthStep0[k]=0;
            }
        }
        for(j=0;j<hei;j++){
            for(i=0;i<wid;i++){
                mByte=mByte0+j*widthStep+i*bytesPerPixel;
                pByte=pByte0+j*widthStep+i*bytesPerPixel;

                pByte[0]=mByte[0];
                pByte[1]=mByte[1];
                pByte[2]=mByte[2];

                dmax0min=256;
                for(k=0;k<eraserCount;k++){
                    if(eByte0[k]==NULL || wid0[k]==0 || hei0[k]==0 || widthStep0[k]==0){
                        continue;
                    }
                    if(i<wid0[k] && j<hei0[k]){
                        eByte=eByte0[k]+j*widthStep0[k]+i*bytesPerPixel;
                    }else{
                        eByte=eByte0[k]+(j%hei0[k])*widthStep0[k]+(i%wid0[k])*bytesPerPixel;
                    }

                    dr=(int)(mByte[2])-(int)(eByte[2]);
                    dg=(int)(mByte[1])-(int)(eByte[1]);
                    db=(int)(mByte[0])-(int)(eByte[0]);
                    da=(int)(mByte[3])-(int)(eByte[3]);

                    dmax0=abs(dr);
                    if(dmax0<abs(dg))dmax0=abs(dg);
                    if(dmax0<abs(db))dmax0=abs(db);
                    //if(dmax<abs(da))dmax=abs(da);

                    if(dmax0min>dmax0){
                        dmax0min=dmax0;
                    }
                }

                if(dmax0min>dcolormax){
                    pByte[3]=mByte[3];
                }else if(dmax0min<=dcolormin){
                    pByte[3]=0;
                }else{
                    pByte[3]=mByte[3]*(dmax0min-dcolormin)/(dcolormax-dcolormin);
                }
            }
        }
        delete []eByte0;
        eByte0=NULL;

        delete []wid0;
        wid0=NULL;

        delete []hei0;
        hei0=NULL;

        delete []widthStep0;
        widthStep0=NULL;
    }else{
        for(j=0;j<hei;j++){
            for(i=0;i<wid;i++){
                mByte=mByte0+j*widthStep+i*bytesPerPixel;
                pByte=pByte0+j*widthStep+i*bytesPerPixel;

                pByte[0]=mByte[0];
                pByte[1]=mByte[1];
                pByte[2]=mByte[2];
                pByte[3]=mByte[3];
            }
        }
    }
    if(shrinkRate>0){
        unsigned char *alphaAbove=new unsigned char[2*wid];
        unsigned char alphaLeft=0;
        int alphamin=255;
        int timeCount=(shrinkRate-1)/100+1;
        int shrinkRatet=100;//(shrinkRate-1)%100+1;

        /*bool willExpand=true;
        int alphamax=0;
        int alphamaxr=0;
        int alphamaxg=0;
        int alphamaxb=0;
        int alphaLimit=16;*/

        for(k=0;k<timeCount;k++){
            shrinkRatet=k<timeCount-1?100:(shrinkRate-1)%100+1;
            for(j=0;j<hei;j++){
                for(i=0;i<wid;i++){
                    pByte=pByte0+j*widthStep+i*bytesPerPixel;
                    alphamin=255;
                    if(j>0){
                        if(i>0 && alphamin>alphaAbove[i-1]){
                            alphamin=alphaAbove[i-1];
                        }
                        if(alphamin>alphaAbove[i]){
                            alphamin=alphaAbove[i];
                        }
                        if(i>wid-1 && alphamin>alphaAbove[i+1]){
                            alphamin=alphaAbove[i+1];
                        }
                    }
                    if(i>0 && alphamin>alphaLeft){
                        alphamin=alphaLeft;
                    }
                    if(alphamin>pByte[3]){
                        alphamin=pByte[3];
                    }
                    if(i>wid-1 && alphamin>pByte[bytesPerPixel+3]){
                        alphamin=pByte[bytesPerPixel+3];
                    }
                    if(j<hei-1){
                        if(i>0 && alphamin>pByte[widthStep-bytesPerPixel+3]){
                            alphamin=pByte[widthStep-bytesPerPixel+3];
                        }
                        if(alphamin>pByte[widthStep+3]){
                            alphamin=pByte[widthStep+3];
                        }
                        if(i>wid-1 && alphamin>pByte[widthStep+bytesPerPixel+3]){
                            alphamin=pByte[widthStep+bytesPerPixel+3];
                        }
                    }
                    alphaAbove[wid+i]=pByte[3];
                    alphaLeft=pByte[3];
                    pByte[3]=pByte[3]-(pByte[3]-alphamin)*shrinkRatet/100;
                }
                for(i=0;i<wid;i++){
                    alphaAbove[i]=alphaAbove[wid+i];
                }
            }
        }
        /*for(k=0;k<timeCount;k++){
            if(!willExpand){
                break;
            }
            shrinkRatet=k<timeCount-1?100:(shrinkRate-1)%100+1;
            for(j=0;j<hei;j++){
                for(i=0;i<wid;i++){
                    pByte=pByte0+j*widthStep+i*bytesPerPixel;
                    alphamax=0;

                    if(alphamax<pByte[3]){
                        alphamax=pByte[3];
                        alphamaxr=pByte[2];
                        alphamaxg=pByte[1];
                        alphamaxb=pByte[0];
                    }

                    if(j>0 && alphamax<alphaAbove[i]){
                        alphamax=alphaAbove[i];
                        alphamaxr=pByte[-widthStep+2];
                        alphamaxg=pByte[-widthStep+1];
                        alphamaxb=pByte[-widthStep];
                    }

                    if(i>0 && alphamax<alphaLeft){
                        alphamax=alphaLeft;
                        alphamaxr=pByte[-bytesPerPixel+2];
                        alphamaxg=pByte[-bytesPerPixel+1];
                        alphamaxb=pByte[-bytesPerPixel];
                    }

                    if(i>wid-1 && alphamax<pByte[bytesPerPixel+3]){
                        alphamax=pByte[bytesPerPixel+3];
                        alphamaxr=pByte[bytesPerPixel+2];
                        alphamaxg=pByte[bytesPerPixel+1];
                        alphamaxb=pByte[bytesPerPixel];
                    }

                    if(j<hei-1 && alphamax<pByte[widthStep+3]){
                        alphamax=pByte[widthStep+3];
                        alphamaxr=pByte[widthStep+2];
                        alphamaxg=pByte[widthStep+1];
                        alphamaxb=pByte[widthStep];
                    }


                    if(j>0){
                        if(i>0 && alphamax<alphaAbove[i-1]){
                            alphamax=alphaAbove[i-1];
                            alphamaxr=pByte[-widthStep-bytesPerPixel+2];
                            alphamaxg=pByte[-widthStep-bytesPerPixel+1];
                            alphamaxb=pByte[-widthStep-bytesPerPixel];
                        }
                        if(i>wid-1 && alphamax<alphaAbove[i+1]){
                            alphamax=alphaAbove[i+1];
                            alphamaxr=pByte[-widthStep+bytesPerPixel+2];
                            alphamaxg=pByte[-widthStep+bytesPerPixel+1];
                            alphamaxb=pByte[-widthStep+bytesPerPixel];
                        }
                    }
                    if(j<hei-1){
                        if(i>0 && alphamax<pByte[widthStep-bytesPerPixel+3]){
                            alphamax=pByte[widthStep-bytesPerPixel+3];
                            alphamaxr=pByte[widthStep-bytesPerPixel+2];
                            alphamaxg=pByte[widthStep-bytesPerPixel+1];
                            alphamaxb=pByte[widthStep-bytesPerPixel];
                        }
                        if(i>wid-1 && alphamax<pByte[widthStep+bytesPerPixel+3]){
                            alphamax=pByte[widthStep+bytesPerPixel+3];
                            alphamaxr=pByte[widthStep+bytesPerPixel+2];
                            alphamaxg=pByte[widthStep+bytesPerPixel+1];
                            alphamaxb=pByte[widthStep+bytesPerPixel];
                        }
                    }
                    alphaAbove[wid+i]=pByte[3];
                    alphaLeft=pByte[3];
                    if(pByte[3]<alphaLimit && alphamax>=alphaLimit){
                        pByte[2]=alphamaxr;
                        pByte[1]=alphamaxg;
                        pByte[0]=alphamaxb;
                    }
                    pByte[3]=pByte[3]+(alphamax-pByte[3])*shrinkRatet/100;
                }
                for(i=0;i<wid;i++){
                    alphaAbove[i]=alphaAbove[wid+i];
                }
            }
        }*/
        delete []alphaAbove;
    }
}
