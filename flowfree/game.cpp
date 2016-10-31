#include "game.h"
#include "funobject.h"
#include <QPainter>
//#include <qDebug>
#include <QMouseEvent>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

const QColor Game::pieces[8] = {Qt::black, Qt::red, Qt::blue,
                               Qt::cyan, Qt::gray, Qt::magenta,
                               Qt::green, Qt::yellow};
const int Game::max_level[10] = {0, 0, 0, 0, 0, 4, 3, 3, 1, 0};

Game::Game(QWidget *parent) :
    QDialog(parent)
    , SQUARE(66)
    , LITTLESQUARE(40)
    , border_size(5)
    , current_level(1)
    , repaintRect(NULL)
    , last_level(new QPushButton("上一关", this))
    , next_level(new QPushButton("下一关", this))
    , game_restart(new QPushButton("重新开始", this))
    , complete(":/wav/flowfreewav/forward.wav")
    , interrupt(":/wav/flowfreewav/leak.wav")
    , current_play(NULL)
{
    this->setWindowIcon(QIcon(":/ico/flowfreeimg/flowfree.ico"));
    connect(this, SIGNAL(restart()), this, SLOT(slotsRestart()));
    connect(this, SIGNAL(nextlevel()), this, SLOT(slotsNextlevel()));
    connect(this->last_level, SIGNAL(clicked()), this, SLOT(slotsLastlevel()));
    connect(this->next_level, SIGNAL(clicked()), this, SLOT(slotsNextlevel()));
    connect(this->game_restart, SIGNAL(clicked()), this, SLOT(slotsRestart()));
    last_level->setFixedSize(100, 50);
    next_level->setFixedSize(100, 50);
    game_restart->setFixedSize(100, 50);
    //qDebug() << last_level->size() << " "
    //         << next_level->size() << " "
    //         << game_restart->size() << endl;
    QHBoxLayout *button_layout = new QHBoxLayout(this);
    button_layout->addWidget(last_level);
    button_layout->addWidget(game_restart);
    button_layout->addWidget(next_level);
    button_layout->setAlignment(Qt::AlignBottom);
}

void Game::slotsRestart()
{
    start();
}

void Game::slotsNextlevel()
{
    if (current_level < max_level[border_size])
        current_level++;
    start();
}

void Game::slotsLastlevel()
{
    if (current_level > 1)
        current_level--;
    start();
}

void Game::closeEvent(QCloseEvent *)
{
    current_level = 1;
}

void Game::start()
{
    if ((current_level > max_level[border_size])
        || (current_level < 1))
    {
        current_level = 1;
        border_size = 5;
    }
    preprocess();
    this->resize(QSize(SQUARE * border_size, SQUARE * border_size + 100));
    //  resize interface

    //qDebug() << "size: " << this->size() << endl;
    limiteHeight = SQUARE * border_size - 5;
    limiteWidth = SQUARE * border_size - 5;
    QString stitle = "flowfree level " +
            QString::number(border_size, 10);
    this->setWindowTitle(stitle);
    this->show();
    update();
}
//  start game

void Game::preprocess()
{
    memset(board, 0, sizeof(board));
    memset(win, 0, sizeof(win));
    for (int i = 0; i < 8; i++)
        linePath[i].clear();
    for (int i = 0; i < 8; i++)
        drawPath[i].clear();
    repaintRect = NULL;

    for (int i = 0; i < border_size; i++)
        for (int j = 0; j < border_size; j++)
        {
            ellipseRec[i][j] =
                    QRect(j * SQUARE + (SQUARE - LITTLESQUARE) / 2,
                          i * SQUARE + (SQUARE - LITTLESQUARE) / 2,
                          LITTLESQUARE, LITTLESQUARE);

            board_center[i][j] = QPoint(j * SQUARE + SQUARE / 2, i * SQUARE + SQUARE / 2);
        }
}
//  the process before begining

QPoint Game::calculate(int x, int y)
{
//    //qDebug() << "shen: " << x << " " << y <<
//                " " << this->size() << endl;
    int nx = x / SQUARE;
    int ny = y / SQUARE;
    return QPoint(ny, nx);
}
//  after calculatint current row and col, store them as a QPoint
//

void Game::getCurrent(QMouseEvent *ev)
{
    this->current_rc = calculate(ev->x(), ev->y());
    this->current_color = board[current_rc.x()][current_rc.y()];
}
//  obtain current position and color
//

void Game::paintEvent(QPaintEvent *ev)
{
    paintBackground(ev);
    paintEllipse(ev);
    paintPolyline();
    if (repaintRect != NULL)
        (*repaintRect)(this);
}

void Game::paintBackground(QPaintEvent *)
{
    int bottomX = SQUARE * border_size;
    int bottomY = SQUARE * border_size;

    QPainter pgrid(this);
    pgrid.setBrush(Qt::black);
    pgrid.drawRect(QRect(QPoint(0, 0), QPoint(bottomX, bottomY)));
    //  black background
    //

    QPen linePen(Qt::white, 2);
    pgrid.setPen(linePen);
    for(int i = 1; i < border_size; i++)
    {
        pgrid.drawLine(0, i * SQUARE, bottomX, i * SQUARE);
        pgrid.drawLine(i * SQUARE, 0, i * SQUARE, bottomY);
    }
    //  draw square grid
    //
}
//  draw blackground
//

void Game::paintEllipse(QPaintEvent *)
{
    QPainter pEllipse(this);

    //QFile类提供读写文件的接口
    //QFile是一个用于读写文本文件和二进制文件和资源文件的I/O 设备
    QString map_file_name = ":/map/flowfreemap/"
            + QString::number(border_size)
            + "_" + QString::number(current_level) + ".txt";

    //将QFile与相关文件关联
    QFile map_file(map_file_name);

    //以只读和文本模式打开文件
    if(! map_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug() << "Could not open file for Reading";
        return;
    }

    //QTextStream提供一种读写文本文档边界的接口
    //将QTextStream与特定文件关联
    QTextStream outText(&map_file);

    //  关卡地图
    QString mapArr = outText.readAll();
    for (int i = 0; i < border_size; i++)
        for (int j = 0; j < border_size; j++)
        {
            int v = mapArr[i * border_size + j].toLatin1() - '0';
            if (! v)
                continue;
            QBrush colorBrush(pieces[v]);
            pEllipse.setBrush(colorBrush);
            pEllipse.drawEllipse(ellipseRec[i][j]);
            board[i][j] = v;
        }

    //关闭文件
    map_file.close();
}
//  draw small and dark ellipse
//

void Game::paintEllipseLighter(QRect rept)
{
    QPainter pEllipse(this);
    QColor alpha = pieces[last_color / 10];
    alpha.setAlpha(100);
    QBrush vbrush(alpha);
    pEllipse.setBrush(vbrush);
    pEllipse.drawEllipse(rept);
}
//  draw big and lighter ellipse
//

void Game::paintPolyline()
{
    QPainter pPloyline(this);

    for (int i = 1; i < 8; i++)
        if (drawPath[i].size() > 1)
        {
            pPloyline.setBrush(pieces[i]);
            QPen linePen(pieces[i], 10);
            linePen.setJoinStyle(Qt::MiterJoin);
            pPloyline.setPen(linePen);
            pPloyline.drawPolyline(drawPath[i]);

            QColor transparent = pieces[i];
            transparent.setAlpha(100);
            linePen.setBrush(transparent);
            linePen.setWidth(SQUARE);
            pPloyline.setPen(linePen);
            pPloyline.drawPolyline(drawPath[i]);
        }
}
//  draw polyline when user play the game
//

int Game::legal(const QPoint &current_pos)
{
    QPoint lastPos = linePath[last_color / 10][linePath[last_color / 10].size() - 1];
    //qDebug() << "lastPos vs currentPos: "
    //         << lastPos.x() << " " << lastPos.y()
    //         << " " << current_pos.x() << " "
    //         << current_pos.y() << endl
    //         << last_color << " " << current_color << endl;
    if (! (abs(current_pos.x() - lastPos.x()) +
        abs(current_pos.y() - lastPos.y()))
        )
    {
        //qDebug() << "no variable" << endl;
        return 0;
    }

    if (last_color == current_color)
    {
        //qDebug() << "circuit restriction" << endl;
        return -1;
    }
    //  circuit restriction

    if (current_pos == linePath[last_color / 10][0])
    {
        //qDebug() << "back to start restriction" << endl;
        return -1;
    }
    //  back to start restriction

    if ((abs(current_pos.x() - lastPos.x()) +
        abs(current_pos.y() - lastPos.y()))
        != 1)
    {
        //qDebug() << "dist restriction" << endl;
        return 0;
    }
    //  dist restriction

    if ((current_color > 0) && (current_color < 10) && (current_color * 10 != last_color))
    {
        //qDebug() << "penetrate other dot restriction    "
                 //<< current_color << " "
                 //<< last_color << endl;
        return 0;
    }
    //  penetrate other dot restriction


    //qDebug() << "go head" << endl;
    return 1;
}
//  judge whether the move is right or wrong

void Game::push_back(const QPoint &current_pos)
{
    linePath[last_color / 10].push_back(current_pos);
    drawPath[last_color / 10].push_back(board_center[current_pos.x()][current_pos.y()]);
}
//  add the point to path

void Game::clean(int color, int pos)
{
    int lsize = linePath[color].size();
    while (lsize-- > pos)
    {
        board[linePath[color][lsize].x()][linePath[color][lsize].y()] %= 10;
        linePath[color].pop_back();
        drawPath[color].pop_back();
    }
}
//  take away points from the path until the size equal to pos

void Game::clean(int color, QPoint nodot, int self)
{
    if ((current_play == &complete) && (self))
        current_play = NULL;
    int lsize = linePath[color].size();
    while (lsize-- > 0)
    {
        if ((self) && (nodot == linePath[color][lsize]))
            break;
        int row = linePath[color][lsize].x();
        int col = linePath[color][lsize].y();
        //qDebug() << "back row col: "
        //         << row << " " << col << endl;
        if (board[row][col] > 9)
            board[row][col] = 0;
        else
        {
            win[color] = 0;
            current_play = &interrupt;
            //qDebug() << "mabide" << endl;
        }
        //  break into the complete line

        linePathBackup[color].push_back(linePath[color][lsize]);
        drawPathBackup[color].push_back(drawPath[color][lsize]);
        if (nodot == linePath[color][lsize])
            lsize = 0;
        linePath[color].pop_back();
        drawPath[color].pop_back();
    }
}
//  different from the above in stop condition

void Game::backup()
{
    for (int i = 1; i < 8; i++)
        linePathBackup[i].clear();
    for (int i = 1; i < 8; i++)
        drawPathBackup[i].clear();
}
//  backup path to restore

void Game::backupRestore()
{
    int need = 0, done = 0;
    for (int i = 1; i < 8; i++)
        if ((i != last_color / 10)
            && (linePathBackup[i].size() > 0))
        {
            need++;
            int lsize = linePathBackup[i].size();
            while (lsize--)
            {
                int row = linePathBackup[i][lsize].x();
                int col = linePathBackup[i][lsize].y();
                if (board[row][col] > 9)
                    break;
//                //qDebug() << "color: " << i << " ";
//                //qDebug() << "restore row col: "
//                         << row << " " << col << endl;
                if (! board[row][col])
                {
//                    //qDebug() << "row col: "
//                             << row << " " << col
//                             << board[row][col] << endl;
                    board[row][col] = i * 10;
                }else
                {
                    win[i] = 1;
                    done++;
                }
                //  restore the complete line

                linePath[i].push_back(linePathBackup[i][lsize]);
                drawPath[i].push_back(drawPathBackup[i][lsize]);
                linePathBackup[i].pop_back();
                drawPathBackup[i].pop_back();
            }
        }
    if ((need == done) && (current_play == &interrupt))
        current_play = NULL;
}
//  restore the path

void Game::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()!= Qt::LeftButton)
        return;
    if ((ev->x() < 5) || (ev->x() > limiteHeight)
            || (ev->y() < 5) || (ev->y() > limiteWidth))
        return;
    //  illegal cordinate
    current_play = NULL;
    getCurrent(ev);
    if (! this->current_color)
        return;
    //  clicking black grid is invalid
    backup();
    last_color = current_color;
    //  the color will be lasting

    if (current_color < 10)
    {
        win[current_color] = 0;
        last_color *= 10;
        clean(current_color, 0);
        push_back(current_rc);
    }
    //  start a new path, storing the start dot

    if (repaintRect != NULL)
    {
        delete repaintRect;
        repaintRect = NULL;
    }
    QRect rectEli(ev->x() - SQUARE / 2, ev->y() - SQUARE / 2
        , SQUARE, SQUARE);
    repaintRect = new FunObject(&Game::paintEllipseLighter,
                        rectEli);
    repaint();
}
//  initial

void Game::mouseReleaseEvent(QMouseEvent *)
{
    //qDebug() << "you have released" << endl;
    last_color = 0;
    if (repaintRect != NULL)
    {
        delete repaintRect;
        repaintRect = NULL;
    }
    int tot = 0;
    for (int i = 1; i < 8; i++)
        if (win[i])
        {
            tot += drawPath[i].size();
            //qDebug() << "windraw:   " <<
            //            i << " " <<
                        drawPath[i].size();
        }
    //qDebug() << "oh tot: " << tot << endl;
    if (tot == border_size * border_size)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"You win","重玩(Yes) 下一关(No) 重选地图(Close)",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Close);
        if (reply == QMessageBox::Yes)
            emit slotsRestart();
        else if (reply == QMessageBox::No)
            emit slotsNextlevel();
        else
            emit close();
    }
    if (current_play != NULL)
        current_play->play();
    //qDebug() << "wav: "
    //         << current_play << " " << &interrupt << endl;
    repaint();
}
//  end

void Game::mouseMoveEvent(QMouseEvent *ev)
{
    if ((ev->x() < 5) || (ev->x() > limiteHeight)
            || (ev->y() < 5) || (ev->y() > limiteWidth))
        return;
    //  illegal cordinate

    getCurrent(ev);
    if (! this->last_color)
        return;
    if (repaintRect != NULL)
    {
        delete repaintRect;
        repaintRect = NULL;
    }
    QRect rectEli(ev->x() - SQUARE / 2, ev->y() - SQUARE / 2
                  , SQUARE, SQUARE);
    repaintRect = new FunObject(&Game::paintEllipseLighter,
                                rectEli);
    int re = legal(current_rc);
    if (re == 1)
    {
        if (! win[last_color / 10])
        {
            if (current_color > 9)
                clean(current_color / 10, current_rc);
            if ((current_color > 9) || (! current_color))
                board[current_rc.x()][current_rc.y()] = current_color = last_color;
            else
            {
                win[last_color / 10] = 1;
                if (current_play != &interrupt)
                    current_play = &complete;
            }
            //  have got a complete line
            push_back(current_rc);
        }
        //else
            //qDebug() << "iwin: "
            //         << last_color / 10 << " "
            //         << win[last_color / 10] << endl;
            //for (int i = 1; i < 8; i++)
                //if (win[i])
                    //qDebug() << "headwincolor: "
                    //     << i << " "
                    //     << win[i] << endl;

    }
    else if (re == -1)
    {
        clean(last_color / 10, current_rc, 1);
        backupRestore();
        //for (int i = 1; i < 8; i++)
            //if (win[i])
                //qDebug() << "restorewincolor: "
                //         << i << " "
                //         << win[i] << endl;
    }
    repaint();
}
//  game process

