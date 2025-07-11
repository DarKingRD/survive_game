#include "fallingplatform.h"
#include "player.h"
#include "game.h"

FallingPlatform::FallingPlatform(Player* player, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), player(player){
    setBrush(Qt::darkGreen);
    setRect(0, 0, 50 + rand() % (350 - 50 + 1),13);
    setPos(0 + rand() % (690 - 0 + 1), -10);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FallingPlatform::fall);
    connect(timer, &QTimer::timeout, this, &FallingPlatform::checkCollision);
    int time_fall = 50;
    timer->start(time_fall); // Интервал между падениями платформы (в миллисекундах), почему то от этого зависит и время падения платформы
}
void FallingPlatform::setSpeed(int pspeed){
    ppspeed=pspeed;
}
void FallingPlatform::fall(){
    // Двигаем платформу вниз
    setY(y()+ ppspeed);
    if (y() > 580 || x() > 900 || x() < -50) {
                scene()->removeItem(this);
                delete this;
            }
}
void FallingPlatform::checkCollision(){
    bool pc = false;
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    foreach(QGraphicsItem* item, collidingItemsList){
        if (item->collidesWithItem(player) && item->type() == FallingPlatform::Type){
            pc = true;
            break;
        }
    } if (pc)
        emit hitPlayer();
}
