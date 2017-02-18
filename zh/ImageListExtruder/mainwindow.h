#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *object,QEvent *event);
    int currentImageIndex;
    std::vector<std::string> imageList;
    std::string imageEraserString;
    std::vector<QImage> imageEraserList;
    unsigned int imageEraserMaxCount;
    QImage imagePreview;
private:
    Ui::MainWindow *ui;
public slots:
    void OnPushButton1();
    void OnPushButton2();
    void OnPushButton_prev();
    void OnPushButton_next();
    void OnPushButton_zoomOut();
    void OnPushButton_zoomIn();
    void OnPushButton_exportAll();
    void OnBgColor();
    void OnSlider();
    void updateImagePreview(int index=-1);
};

#endif // MAINWINDOW_H
