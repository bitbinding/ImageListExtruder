#include "imagepreviewwidget.h"
#include "exportallthread.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>

extern ExportAllThread *exportAllThread;

bool resizeImage(QImage &imgSrc,QImage &imgDest,int nw,int nh){
    if(imgSrc.isNull() || nw<=0 || nh<=0){
        return false;
    }
    int wid=imgSrc.width();
    int hei=imgSrc.height();
    if(wid<=0 || hei<=0){
        return false;
    }


    int i=0,j=0,k=0,l=0;
    int ix=0,iy=0;
    int ix1=0,iy1=0;
    int dx=0,dy=0;
    float x=0.0f,y=0.0f;
    int r=0,g=0,b=0,a=0,r2=0,g2=0,b2=0,a2=0;
    int sumarea=0,sumarea2=0,rate=0;

    int pitch0=imgSrc.bytesPerLine();
    int bytesPerPixel=imgSrc.depth()>>3;
    if(bytesPerPixel<3){
        return false;
    }

    imgDest=QImage(nw,nh,imgSrc.format());
    if(imgDest.isNull()){
        return false;
    }
    int pitcht=imgDest.bytesPerLine();
    int bytesPerPixelt=imgDest.depth()>>3;
    if(bytesPerPixelt<3){
        return false;
    }

    unsigned char *mByte=NULL;
    unsigned char *pByte=NULL;
    unsigned char *mByte0=imgSrc.bits();
    unsigned char *pByte0=imgDest.bits();
    bool hasAlpha=bytesPerPixel>=4 && bytesPerPixelt>=4;

    if(wid<=nw && hei<=nh){
        for(j=0;j<nh;j++){
            for(i=0;i<nw;i++){
                x=(float)i*wid/nw;
                y=(float)j*hei/nh;
                ix=(int)x;
                iy=(int)y;
                dx=(int)((x-(float)ix)*256);
                dy=(int)((y-(float)iy)*256);
                ix1=ix+1;
                iy1=iy+1;
                if(ix>=wid || ix<0){
                    ix=wid-1;
                }
                if(ix1>=wid || ix1<0){
                    ix1=wid-1;
                }
                if(iy>=hei || iy<0){
                    iy=hei-1;
                }
                if(iy1>=hei || iy1<0){
                    iy1=hei-1;
                }

                mByte=mByte0+iy*pitch0+ix*bytesPerPixel;
                r=(256-dx)*(256-dy)*(int)(*(mByte+2));
                g=(256-dx)*(256-dy)*(int)(*(mByte+1));
                b=(256-dx)*(256-dy)*(int)(*mByte);
                if(hasAlpha){
                    a=(256-dx)*(256-dy)*(int)(*(mByte+3));
                }else{
                    a=0;
                }

                mByte=mByte0+iy*pitch0+ix1*bytesPerPixel;
                r+=dx*(256-dy)*(int)(*(mByte+2));
                g+=dx*(256-dy)*(int)(*(mByte+1));
                b+=dx*(256-dy)*(int)(*mByte);
                if(hasAlpha)a+=dx*(256-dy)*(int)(*(mByte+3));

                mByte=mByte0+iy1*pitch0+ix*bytesPerPixel;
                r+=(256-dx)*dy*(int)(*(mByte+2));
                g+=(256-dx)*dy*(int)(*(mByte+1));
                b+=(256-dx)*dy*(int)(*mByte);
                if(hasAlpha)a+=(256-dx)*dy*(int)(*(mByte+3));

                mByte=mByte0+iy1*pitch0+ix1*bytesPerPixel;
                r+=dx*dy*(int)(*(mByte+2));
                g+=dx*dy*(int)(*(mByte+1));
                b+=dx*dy*(int)(*mByte);
                if(hasAlpha)a+=dx*dy*(int)(*(mByte+3));

                r=r>>16;
                g=g>>16;
                b=b>>16;
                if(hasAlpha)a=a>>16;
                if (r>255) {
                    r=255;
                } else if (r<0) {
                    r=0;
                }
                if (g>255) {
                    g=255;
                } else if (g<0) {
                    g=0;
                }
                if (b>255) {
                    b=255;
                } else if (b<0) {
                    b=0;
                }
                if(hasAlpha){
                    if (a>255) {
                        a=255;
                    } else if (a<0) {
                        a=0;
                    }
                }

                pByte=pByte0+j*pitcht+i*bytesPerPixelt;
                pByte[0]=b;
                pByte[1]=g;
                pByte[2]=r;
                if(hasAlpha)pByte[3]=a;
            }
        }
    }else/* if(wid>=nw && hei>=nh)*/{
        for(j=0;j<nh;j++){
            iy=j*hei/nh;
            iy1=(j+1)*hei/nh;
            if(iy>=iy1){iy1=iy+1;}
            for(i=0;i<nw;i++){
                ix=i*wid/nw;
                ix1=(i+1)*wid/nw;
                if(ix>=ix1){ix1=ix+1;}
                r=0;
                g=0;
                b=0;
                a=0;
                sumarea=0;
                for(l=iy;l<iy1;l++){
                    for(k=ix;k<ix1;k++){
                        if(k<wid && l<hei && k>=0 && l>=0){
                            mByte=mByte0+l*pitch0+k*bytesPerPixel;
                            r+=*(mByte+2);
                            g+=*(mByte+1);
                            b+=*mByte;
                            if(hasAlpha)a+=*(mByte+3);
                            sumarea++;
                        }
                    }
                }
                if(wid<nw){
                    r2=0;
                    g2=0;
                    b2=0;
                    a2=0;
                    sumarea2=0;
                    for(l=iy;l<iy1;l++){
                        for(k=ix1;k<=ix1;k++){
                            if(k<wid && l<hei && k>=0 && l>=0){
                                mByte=mByte0+l*pitch0+k*bytesPerPixel;
                                r2+=*(mByte+2);
                                g2+=*(mByte+1);
                                b2+=*mByte;
                                if(hasAlpha)a2+=*(mByte+3);
                                sumarea2++;
                            }
                        }
                    }
                    rate=i*wid*256/nw-i*wid/nw*256;
                }else if(hei<nh){
                    r2=0;
                    g2=0;
                    b2=0;
                    a2=0;
                    sumarea2=0;
                    for(l=iy1;l<=iy1;l++){
                        for(k=ix;k<ix1;k++){
                            if(k<wid && l<hei && k>=0 && l>=0){
                                mByte=mByte0+l*pitch0+k*bytesPerPixel;
                                r2+=*(mByte+2);
                                g2+=*(mByte+1);
                                b2+=*mByte;
                                if(hasAlpha)a2+=*(mByte+3);
                                sumarea2++;
                            }
                        }
                    }
                    rate=j*hei*256/nh-j*hei/nh*256;
                }else{
                    rate=0;
                }
                if(sumarea!=0){
                    if(rate<=0 || sumarea2==0){
                        r/=sumarea;
                        g/=sumarea;
                        b/=sumarea;
                        if(hasAlpha)a/=sumarea;
                    }else if(sumarea2!=0){
                        r=((256-rate)*r/sumarea+rate*r2/sumarea2)/256;
                        g=((256-rate)*g/sumarea+rate*g2/sumarea2)/256;
                        b=((256-rate)*b/sumarea+rate*b2/sumarea2)/256;
                        if(hasAlpha)a=((256-rate)*a/sumarea+rate*a2/sumarea2)/256;
                    }
                    if (r>255) {
                        r=255;
                    } else if (r<0) {
                        r=0;
                    }
                    if (g>255) {
                        g=255;
                    } else if (g<0) {
                        g=0;
                    }
                    if (b>255) {
                        b=255;
                    } else if (b<0) {
                        b=0;
                    }
                    if(hasAlpha){
                        if (a>255) {
                            a=255;
                        } else if (a<0) {
                            a=0;
                        }
                    }
                    pByte=pByte0+j*pitcht+i*bytesPerPixelt;
                    pByte[0]=b;
                    pByte[1]=g;
                    pByte[2]=r;
                    if(hasAlpha)pByte[3]=a;
                }
            }
        }
    }
    return true;
}

ImagePreviewWidget::ImagePreviewWidget(QWidget *parent) : QWidget(parent)
{
    bgc=0;
    pWnd=NULL;
    willScale=true;
    posx=0;
    posy=0;
    mx0=0;
    my0=0;
    this->setAutoFillBackground(true);
}

ImagePreviewWidget::~ImagePreviewWidget()
{
    pWnd=NULL;
}

void ImagePreviewWidget::paintEvent(QPaintEvent *event){
    if(pWnd==NULL || pWnd->imagePreview.isNull() || this->width()==0 || this->height()==0 || (exportAllThread!=NULL && exportAllThread->isRunning())){
        return;
    }

    QPainter painter(this);

    int r0=bgc>>16&0xff;
    int g0=bgc>>8&0xff;
    int b0=bgc&0xff;

    if(!willScale){
        painter.fillRect(posx,posy,pWnd->imagePreview.width(),pWnd->imagePreview.height(),QColor(r0,g0,b0));
        painter.drawImage(posx,posy,pWnd->imagePreview);
        return;
    }

    int wid0=pWnd->imagePreview.width();
    int hei0=pWnd->imagePreview.height();
    int wid=this->width();
    int hei=this->height();
    int widt=wid0;
    int heit=hei0;
    QRect rect;
    if(wid0<wid && hei0<hei){
        rect.setRect((wid-wid0)>>1,(hei-hei0)>>1,wid0,hei0);
    }else if(wid0*hei>hei0*wid){
        widt=wid;
        heit=hei0*wid/wid0;
        rect.setRect((wid-widt)>>1,(hei-heit)>>1,widt,heit);
    }else{
        widt=wid0*hei/hei0;
        heit=hei;
        rect.setRect((wid-widt)>>1,(hei-heit)>>1,widt,heit);
    }
    QImage imgSrc=pWnd->imagePreview.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    QImage imgDest;
    resizeImage(imgSrc,imgDest,rect.width(),rect.height());


    painter.fillRect(rect,QColor(r0,g0,b0));
    painter.drawImage(rect.x(),rect.y(),imgDest);
}

void ImagePreviewWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        mx0=event->x();
        my0=event->y();
    }
}

void ImagePreviewWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton && !willScale){
        posx+=event->x()-mx0;
        posy+=event->y()-my0;
        mx0=event->x();
        my0=event->y();
        restrictPosition();
        update();
    }
}

void ImagePreviewWidget::resizeEvent(QResizeEvent *event){
    if(willScale || pWnd==NULL || pWnd->imagePreview.isNull() || (exportAllThread!=NULL && exportAllThread->isRunning())){
        return;
    }
    int dx=(event->size().width()>>1)-(event->oldSize().width()>>1);
    int dy=(event->size().height()>>1)-(event->oldSize().height()>>1);
    posx+=dx;
    posy+=dy;
    restrictPosition();
    update();
}


void ImagePreviewWidget::restrictPosition(){
    if(willScale || pWnd==NULL || pWnd->imagePreview.isNull() || this->width()==0 || this->height()==0 || (exportAllThread!=NULL && exportAllThread->isRunning())){
        return;
    }

    int wid0=pWnd->imagePreview.width();
    int hei0=pWnd->imagePreview.height();
    int wid=this->width();
    int hei=this->height();

    int xmin,xmax,ymin,ymax;
    if(wid<wid0){
        xmin=wid-wid0;
        xmax=0;
    }else{
        xmin=0;
        xmax=wid-wid0;
    }

    if(hei<hei0){
        ymin=hei-hei0;
        ymax=0;
    }else{
        ymin=0;
        ymax=hei-hei0;
    }

    if(posx<xmin){
        posx=xmin;
    }
    if(posy<ymin){
        posy=ymin;
    }
    if(posx>xmax){
        posx=xmax;
    }
    if(posy>ymax){
        posy=ymax;
    }

}
