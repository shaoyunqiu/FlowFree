#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QString>
#include <cstring>
#include <QPainter>
//#include <QDebug>
#include <QPushButton>
#include <QSound>

using std::memset;

class FunObject;

class Game : public QDialog
{
    Q_OBJECT
    friend class FunObject;
public:
    explicit Game(QWidget *parent = 0);

signals:
    void restart();
    void nextlevel();

public slots:
    void slotsRestart();
    void slotsNextlevel();
    void slotsLastlevel();

public:
    void closeEvent(QCloseEvent * event);
    void setBorder(int new_size)
    {
        border_size = new_size;
    }
    void start();

private:
    void preprocess();
    QPoint calculate(int x, int y);
    void getCurrent(QMouseEvent *ev);
    void paintBackground(QPaintEvent *ev);
    void paintEllipse(QPaintEvent *ev);
    void paintEllipseLighter(QRect);
    void paintPolyline();
    int legal(const QPoint&current_pos);
    void push_back(const QPoint&current_pos);
    void clean(int color, int pos);
    void clean(int color, QPoint nodot, int = 0);
    void backup();
    void backupRestore();
    //  normal function
    //

    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

public:
    const int SQUARE, LITTLESQUARE;

private:
    int border_size, limiteWidth, limiteHeight, current_level;
    int current_color, last_color;
    int win[10];
    int board[10][10];

    QPoint current_rc;    
    QPoint board_center[10][10];

    QVector<QPoint> linePath[10], drawPath[10];
    QVector<QPoint> linePathBackup[10], drawPathBackup[10];

    QRect ellipseRec[10][10];

    FunObject* repaintRect;

    QPushButton *last_level, *next_level, *game_restart;

    QSound complete, interrupt, *current_play;

private:
    static const QColor pieces[8];
    static const int max_level[10];
};

#endif // GAME_H
