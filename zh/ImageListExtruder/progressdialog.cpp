#include "progressdialog.h"
#include "ui_progressdialog.h"
#include "exportallthread.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <sstream>

extern ExportAllThread *exportAllThread;

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    timerID=0;
    if(exportAllThread!=NULL){
        timerID=startTimer(50);
    }
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::timerEvent(QTimerEvent *event){
    if(exportAllThread!=NULL && exportAllThread->totalCount>0){
        ui->progressBar->setValue(exportAllThread->progress*100/exportAllThread->totalCount);
        std::ostringstream ostr;
        ostr<<exportAllThread->progress<<"/"<<exportAllThread->totalCount;
        ui->label->setText(ostr.str().c_str());
        if(!exportAllThread->isRunning()){
            killTimer(timerID);
            if(exportAllThread->progress>=exportAllThread->totalCount){
                QMessageBox::information(NULL,"","导出完成。");
            }
            QDialog::accept();
        }
    }
}

void ProgressDialog::closeEvent(QCloseEvent *event){
    if(exportAllThread!=NULL && exportAllThread->isRunning()){
        event->ignore();
        exportAllThread->willCancel=true;
    }else{
        event->accept();
    }
}


