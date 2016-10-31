/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action5_5;
    QAction *action6_6;
    QAction *action7_7;
    QAction *action8_8;
    QAction *action9_9;
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_introduction;
    QPushButton *pushButton_help;
    QPushButton *pushButton_start;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        action5_5 = new QAction(MainWindow);
        action5_5->setObjectName(QStringLiteral("action5_5"));
        action6_6 = new QAction(MainWindow);
        action6_6->setObjectName(QStringLiteral("action6_6"));
        action7_7 = new QAction(MainWindow);
        action7_7->setObjectName(QStringLiteral("action7_7"));
        action8_8 = new QAction(MainWindow);
        action8_8->setObjectName(QStringLiteral("action8_8"));
        action9_9 = new QAction(MainWindow);
        action9_9->setObjectName(QStringLiteral("action9_9"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(130, 60, 144, 136));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_introduction = new QPushButton(widget);
        pushButton_introduction->setObjectName(QStringLiteral("pushButton_introduction"));
        pushButton_introduction->setMinimumSize(QSize(140, 40));
        QFont font;
        font.setFamily(QStringLiteral("Franklin Gothic Demi"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pushButton_introduction->setFont(font);

        verticalLayout->addWidget(pushButton_introduction);

        pushButton_help = new QPushButton(widget);
        pushButton_help->setObjectName(QStringLiteral("pushButton_help"));
        pushButton_help->setMinimumSize(QSize(140, 40));
        pushButton_help->setFont(font);

        verticalLayout->addWidget(pushButton_help);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton_start = new QPushButton(widget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setMinimumSize(QSize(140, 40));
        pushButton_start->setFont(font);

        verticalLayout_2->addWidget(pushButton_start);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(action5_5);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action6_6);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action7_7);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action8_8);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action9_9);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action5_5->setText(QApplication::translate("MainWindow", "5*5", 0));
        action6_6->setText(QApplication::translate("MainWindow", "6*6", 0));
        action7_7->setText(QApplication::translate("MainWindow", "7*7", 0));
        action8_8->setText(QApplication::translate("MainWindow", "8*8", 0));
        action9_9->setText(QApplication::translate("MainWindow", "9*9", 0));
        pushButton_introduction->setText(QApplication::translate("MainWindow", "Introduction", 0));
        pushButton_help->setText(QApplication::translate("MainWindow", "Help", 0));
        pushButton_start->setText(QApplication::translate("MainWindow", "start", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
