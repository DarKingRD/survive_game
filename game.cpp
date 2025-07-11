#include "game.h"
#include "player.h"
#include "fallingplatform.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

Game::Game(QGraphicsView *view, QLCDNumber *scoreLCD, QProgressBar *ProgressBar, QObject *parent):
    QObject(parent),
    view(view),
    scene(new QGraphicsScene(view)),
    timer(new QTimer(this)),
    player(new Player),
    scoreLCD(scoreLCD),
    ProgressBar(ProgressBar),
    score(0),
    lvl(1000),
    hp(100),
    pspeed(5),
    timescore(3000){
    view->setScene(scene); // задаём сцену
    scene->setSceneRect(0, 0, view->width()-10, view->height()-10); //её размеры
    view->installEventFilter(this); //ставим eventFilter для корректной работы управления в игре
    ProgressBar->setValue(hp);
    scoreLCD->display(score);
}

Game::~Game(){
    delete player;
    delete scene;
    delete timer;
    delete view;
}

void Game::startGame() {
    gameEnd = false;
    scene->clear(); //очищаем сцену
    scene->addItem(player); //добавляем на сцену игрока

    player->setPos(scene->width() / 2 - player->rect().width() / 2,
                   scene->height()-100 - player->rect().height()); //его позиция


    QTimer* timerplat = new QTimer(this);
    connect(timerplat, &QTimer::timeout, this, &Game::generatePlatform); //ген. пл.
    timerplat->start(lvl); // Интервал между генерацией платформ (в миллисекундах)

    connect(timer, &QTimer::timeout, this, &Game::increaseScore); //начисление очков
    timer->start(timescore);
}


bool Game::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        player->keyPressEvent(keyEvent);
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void Game::generatePlatform(){
    FallingPlatform* platform = new FallingPlatform(player);// Создаем экземпляр класса платформы
    platform->setSpeed(pspeed);
    scene->addItem(platform);
    connect(platform, SIGNAL(hitPlayer()), this, SLOT(decreaseHP()));
    if(gameEnd){
        delete platform;
        return;
    }
    if(platform->pos().y()>580){
        delete platform;
    }
}

void Game::decreaseHP(){
    hp = hp - 2;
    ProgressBar->setValue(hp);
    if (hp <= 0)
    {
        endGame();
    }
}
void Game::increaseScore(){
    score++;
    scoreLCD->display(score);
    if (score > 20) {
        pspeed = 10;
    }
    if (score >40){
        pspeed = 15;
    }
    if (score >60){
        pspeed = 20;
    }
    if (score >80)
    {
        pspeed = 25;
    }
    if (score > 100)
    {
        pspeed = 30;
    }
}

void Game::endGame()
{
    if(gameEnd){
        return;
    }
    gameEnd = true;
    QMessageBox msgBox;
    scene->clear();
    msgBox.setWindowTitle("Игра окончена!");
    msgBox.setText("Игра окончена!\nВы набрали следующее кол-во очков: " + QString::number(score));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    QObject::connect(&msgBox, &QMessageBox::destroyed, this, &Game::restartGame);
    msgBox.exec();
    timer->stop();
}

void Game::restartGame(){
    emit gameEnded();
    score = 0;
    hp = 0;
    ProgressBar->setValue(hp);
    scoreLCD->display(score);
}
