#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <qDebug>

#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    , flowfree(new Game(this))
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/ico/flowfreeimg/flowfree.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action5_5_triggered()
{
    //qDebug() << "set border: " << 5 << endl;
    flowfree->setBorder(5);
}

void MainWindow::on_action6_6_triggered()
{
    //qDebug() << "set border: " << 6 << endl;
    flowfree->setBorder(6);
}

void MainWindow::on_action7_7_triggered()
{
    //qDebug() << "set border: " << 7 << endl;
    flowfree->setBorder(7);
}

void MainWindow::on_action8_8_triggered()
{
    //qDebug() << "set border: " << 8 << endl;
    flowfree->setBorder(8);
}

void MainWindow::on_action9_9_triggered()
{
    //qDebug() << "set border: " << 9 << endl;
    flowfree->setBorder(9);
}

void MainWindow::on_pushButton_start_clicked()
{
    //qDebug() << "start! " << endl;
    flowfree->start();
}

void MainWindow::on_pushButton_introduction_clicked()
{
    QString info = "<h2>更多信息请进入网站</h2>\
            <a href = 'http://flowfree.flowanswers.com/'>\
            <h3>http://flowfree.flowanswers.com/</h3></a>";
    QMessageBox::information(this, "introduction", info);
}

void MainWindow::on_pushButton_help_clicked()
{
    QString info = "<h2>更多帮助请进入网站</h2>\
            <a href = 'http://flowfreesolutions.com/'>\
            <h3>http://flowfreesolutions.com/</h3></a>";
    QMessageBox::information(this, "introduction", info);
}
