#ifndef FALLINGPLATFORM_H
#define FALLINGPLATFORM_H
#include <QObject> // Qt core
#include <QGraphicsRectItem> // Qt Widgets
#include <QTimer> // Qt core
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <QGraphicsRectItem> // Qt Widgets
#include <QGraphicsScene> // Qt Widgets

class Player;

class FallingPlatform : public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    FallingPlatform(Player *player, QGraphicsItem* parent = nullptr);
    void setSpeed(int pspeed);
    int ppspeed = 5;
signals:
    void hitPlayer(); // Сигнал, который будем испускать при попадании платформы на игрока

private slots:
    void fall();
    void checkCollision();
private:
    Player* player;
};

#endif // FALLINGPLATFORM_H
