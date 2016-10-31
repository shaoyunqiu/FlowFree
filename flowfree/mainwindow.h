#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action5_5_triggered();
    void on_action6_6_triggered();
    void on_action7_7_triggered();
    void on_action8_8_triggered();
    void on_action9_9_triggered();

    void on_pushButton_start_clicked();

    void on_pushButton_introduction_clicked();

    void on_pushButton_help_clicked();

private:
    Ui::MainWindow *ui;
    Game* flowfree;
};

#endif // MAINWINDOW_H
