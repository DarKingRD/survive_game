#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem> //Qt widgets
#include <QKeyEvent> //Qt GUI
#include <QGraphicsScene> //Qt widgets
#include <QPixmap> //Qt GUI
#include<QFileInfo> //Qt Core

class Player : public QGraphicsRectItem{
public:
    Player(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PLAYER_H
