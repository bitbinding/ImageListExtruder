#ifndef IMAGEPREVIEWWIDGET_H
#define IMAGEPREVIEWWIDGET_H

#include <QWidget>
#include "mainwindow.h"

class ImagePreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePreviewWidget(QWidget *parent = 0);
    MainWindow *pWnd;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void restrictPosition();
    ~ImagePreviewWidget();
    int bgc;
    bool willScale;
    int posx;
    int posy;
    int mx0;
    int my0;
signals:

public slots:
};

#endif // IMAGEPREVIEWWIDGET_H
