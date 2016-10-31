#ifndef FUNOJECT_H
#define FUNOJECT_H

#include <QWidget>
#include <QRect>
class Game;
class FunObject : public QWidget
{
    Q_OBJECT
    friend class Game;
public:
    explicit FunObject(void(Game:: *pfun)(QRect), QRect repRect,
                      QWidget *parent = 0);

signals:

public slots:
private:
    void(Game::*pfun)(QRect);
    QRect repRect;
public:
    void operator()(Game*);
};

#endif // FUNOJECT_H
