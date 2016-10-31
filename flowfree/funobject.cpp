#include "funobject.h"

class Game;

FunObject::FunObject(void(Game::*pfun)(QRect), QRect repRect,
                   QWidget *parent) :
    QWidget(parent)
    , pfun(pfun)
    , repRect(repRect)
{
}

void FunObject::operator()(Game* that)
{
    (that->*(this->pfun))(repRect);
}
