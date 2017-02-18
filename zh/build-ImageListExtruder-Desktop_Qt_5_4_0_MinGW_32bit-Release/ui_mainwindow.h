/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "imagepreviewwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_List;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLabel *label_Eraser;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_bgColor;
    QLineEdit *lineEdit_bgColorView;
    QPushButton *pushButton_exportAll;
    ImagePreviewWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QPushButton *pushButton_prev;
    QPushButton *pushButton_zoomOut;
    QLabel *label_imageName;
    QPushButton *pushButton_zoomIn;
    QPushButton *pushButton_next;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLabel *label_arg1;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLabel *label_arg2;
    QSlider *horizontalSlider_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLabel *label_arg3;
    QSlider *horizontalSlider_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 406);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        label_List = new QLabel(centralWidget);
        label_List->setObjectName(QStringLiteral("label_List"));

        verticalLayout_2->addWidget(label_List);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        label_Eraser = new QLabel(centralWidget);
        label_Eraser->setObjectName(QStringLiteral("label_Eraser"));

        verticalLayout_2->addWidget(label_Eraser);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_bgColor = new QLineEdit(centralWidget);
        lineEdit_bgColor->setObjectName(QStringLiteral("lineEdit_bgColor"));
        sizePolicy.setHeightForWidth(lineEdit_bgColor->sizePolicy().hasHeightForWidth());
        lineEdit_bgColor->setSizePolicy(sizePolicy);
        lineEdit_bgColor->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(lineEdit_bgColor);

        lineEdit_bgColorView = new QLineEdit(centralWidget);
        lineEdit_bgColorView->setObjectName(QStringLiteral("lineEdit_bgColorView"));
        sizePolicy.setHeightForWidth(lineEdit_bgColorView->sizePolicy().hasHeightForWidth());
        lineEdit_bgColorView->setSizePolicy(sizePolicy);
        lineEdit_bgColorView->setMaximumSize(QSize(50, 16777215));
        lineEdit_bgColorView->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(lineEdit_bgColorView);

        pushButton_exportAll = new QPushButton(centralWidget);
        pushButton_exportAll->setObjectName(QStringLiteral("pushButton_exportAll"));

        horizontalLayout_4->addWidget(pushButton_exportAll);


        verticalLayout_2->addLayout(horizontalLayout_4);

        widget = new ImagePreviewWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setFocusPolicy(Qt::ClickFocus);

        verticalLayout_2->addWidget(widget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_2->addWidget(label_8);

        pushButton_prev = new QPushButton(centralWidget);
        pushButton_prev->setObjectName(QStringLiteral("pushButton_prev"));
        sizePolicy.setHeightForWidth(pushButton_prev->sizePolicy().hasHeightForWidth());
        pushButton_prev->setSizePolicy(sizePolicy);
        pushButton_prev->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(pushButton_prev);

        pushButton_zoomOut = new QPushButton(centralWidget);
        pushButton_zoomOut->setObjectName(QStringLiteral("pushButton_zoomOut"));
        sizePolicy.setHeightForWidth(pushButton_zoomOut->sizePolicy().hasHeightForWidth());
        pushButton_zoomOut->setSizePolicy(sizePolicy);
        pushButton_zoomOut->setMinimumSize(QSize(0, 0));
        pushButton_zoomOut->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(pushButton_zoomOut);

        label_imageName = new QLabel(centralWidget);
        label_imageName->setObjectName(QStringLiteral("label_imageName"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_imageName->sizePolicy().hasHeightForWidth());
        label_imageName->setSizePolicy(sizePolicy3);
        label_imageName->setTextFormat(Qt::AutoText);
        label_imageName->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_imageName);

        pushButton_zoomIn = new QPushButton(centralWidget);
        pushButton_zoomIn->setObjectName(QStringLiteral("pushButton_zoomIn"));
        sizePolicy.setHeightForWidth(pushButton_zoomIn->sizePolicy().hasHeightForWidth());
        pushButton_zoomIn->setSizePolicy(sizePolicy);
        pushButton_zoomIn->setMinimumSize(QSize(0, 0));
        pushButton_zoomIn->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(pushButton_zoomIn);

        pushButton_next = new QPushButton(centralWidget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        sizePolicy.setHeightForWidth(pushButton_next->sizePolicy().hasHeightForWidth());
        pushButton_next->setSizePolicy(sizePolicy);
        pushButton_next->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(pushButton_next);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        label_arg1 = new QLabel(centralWidget);
        label_arg1->setObjectName(QStringLiteral("label_arg1"));
        label_arg1->setMinimumSize(QSize(50, 0));

        horizontalLayout_5->addWidget(label_arg1);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(-1);
        horizontalSlider->setMaximum(255);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(0);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_7->addWidget(label_6);

        label_arg2 = new QLabel(centralWidget);
        label_arg2->setObjectName(QStringLiteral("label_arg2"));
        sizePolicy3.setHeightForWidth(label_arg2->sizePolicy().hasHeightForWidth());
        label_arg2->setSizePolicy(sizePolicy3);
        label_arg2->setMinimumSize(QSize(50, 0));

        horizontalLayout_7->addWidget(label_arg2);

        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setMinimum(-1);
        horizontalSlider_2->setMaximum(255);
        horizontalSlider_2->setPageStep(1);
        horizontalSlider_2->setValue(0);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(horizontalSlider_2);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_8->addWidget(label_7);

        label_arg3 = new QLabel(centralWidget);
        label_arg3->setObjectName(QStringLiteral("label_arg3"));
        sizePolicy3.setHeightForWidth(label_arg3->sizePolicy().hasHeightForWidth());
        label_arg3->setSizePolicy(sizePolicy3);
        label_arg3->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(label_arg3);

        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setMinimum(0);
        horizontalSlider_3->setMaximum(100);
        horizontalSlider_3->setPageStep(1);
        horizontalSlider_3->setValue(0);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(horizontalSlider_3);


        verticalLayout_2->addLayout(horizontalLayout_8);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ImageListExtruder", 0));
        label->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207\345\272\217\345\210\227\357\274\232", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", 0));
        label_List->setText(QApplication::translate("MainWindow", "<\346\234\252\346\214\207\345\256\232>", 0));
        label_2->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\216\251\346\250\241\345\233\276\347\211\207\357\274\232", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", 0));
        label_Eraser->setText(QApplication::translate("MainWindow", "<\346\234\252\346\214\207\345\256\232>", 0));
        label_3->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\351\242\204\350\247\210\357\274\232", 0));
        label_4->setText(QApplication::translate("MainWindow", "\350\203\214\346\231\257\351\242\234\350\211\262", 0));
        pushButton_exportAll->setText(QApplication::translate("MainWindow", "\345\205\250\351\203\250\345\257\274\345\207\272", 0));
        label_8->setText(QString());
        pushButton_prev->setText(QApplication::translate("MainWindow", "<-", 0));
        pushButton_zoomOut->setText(QApplication::translate("MainWindow", "-", 0));
        label_imageName->setText(QApplication::translate("MainWindow", "<\346\234\252\346\214\207\345\256\232>", 0));
        pushButton_zoomIn->setText(QApplication::translate("MainWindow", "+", 0));
        pushButton_next->setText(QApplication::translate("MainWindow", "->", 0));
        label_9->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\350\211\262\345\267\256\357\274\232", 0));
        label_arg1->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\350\211\262\345\267\256\357\274\232", 0));
        label_arg2->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "\351\200\211\345\214\272\346\224\266\347\274\251\357\274\232", 0));
        label_arg3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
