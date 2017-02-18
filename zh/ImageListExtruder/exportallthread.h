#ifndef EXPORTALLTHREAD_H
#define EXPORTALLTHREAD_H

#include "qthread.h"
#include "mainwindow.h"

class ExportAllThread: public QThread{
    Q_OBJECT
    public:
        MainWindow *pWnd;

        std::string patht;
        int progress;
        int totalCount;
        bool willCancel;
        ExportAllThread(){
            pWnd=NULL;
            totalCount=0;
            progress=0;
            patht="";
            willCancel=false;
        }

        void run(){
            if(pWnd==NULL || pWnd->imageList.empty() || patht==""){
                return;
            }
            willCancel=false;
            totalCount=pWnd->imageList.size();
            progress=0;
            int i=0,j=0;
            std::string imageName;
            std::string imagePathName;
            for(i=0;i<(int)(pWnd->imageList.size());i++){
                pWnd->updateImagePreview(i);
                j=pWnd->imageList[i].rfind('/');
                if(j>=0){
                    imageName=pWnd->imageList[i].substr(j+1);
                }else{
                    imageName=pWnd->imageList[i];
                }
                j=imageName.rfind('.');
                if(j>=0){
                    imageName=imageName.substr(0,j)+".png";
                }else{
                    imageName=imageName+".png";
                }
                imagePathName=patht+imageName;
                pWnd->imagePreview.save(imagePathName.c_str());
                progress++;
                if(willCancel){
                    break;
                }
            }
            pWnd->updateImagePreview();
            patht="";
            willCancel=false;
        }
};

#endif // EXPORTALLTHREAD_H

