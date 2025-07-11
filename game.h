#ifndef GAME_H
#define GAME_H
#include <QObject> //QT core
#include <QGraphicsView> //Qt widgets
#include <QLCDNumber> // Qt widgets
#include <QProgressBar> // Qt widgets
#include <QKeyEvent> //Qt GUI
#include <QTimer> //Qt core
#include <QMessageBox> // Qt widgets
#include <QGraphicsScene> // Qt widgets
#include <QGraphicsRectItem> // Gt widgets
#include<QDebug> //QT core
#include<QPixmap> // QT GUI


class Player;
class FallingPlatform;
class MainWindow;

class Game: public QObject{
    Q_OBJECT
signals:
    void gameEnded();
public:
    explicit Game(QGraphicsView *view, QLCDNumber *scoreLCD, QProgressBar *ProgressBar, QObject *parent = nullptr);
    ~Game();
    void startGame();
    bool eventFilter(QObject *obj, QEvent *event);
    void endGame();
    bool gameEnd = false;

private slots:
    void generatePlatform();
    void increaseScore();
    void decreaseHP();
    void restartGame();
private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QTimer *timer;
    Player *player;
    QLCDNumber *scoreLCD;
    QProgressBar *ProgressBar;
    int score;
    int lvl;
    int hp;//частота появления
    int pspeed;
    int timescore;
};

#endif // GAME_H
