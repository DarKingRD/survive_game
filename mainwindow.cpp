#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "player.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->resize(900, 580);
    this->setFixedSize(900, 580); // фикс. размеры
    setWindowTitle("Уворачивайся!");
    ui->pushButton->setEnabled(true); //активная кнопка
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked); //конектим кнопку с функцией запуска
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}
void MainWindow::on_pushButton_clicked()
{
    if (isGameStarted) {
            return; // Игнорируем повторный клик на кнопку, если игра уже запущена
        }
    isGameStarted = true;
    ui->pushButton->setEnabled(false); //кнопку делаем неактивной
    game = new Game(ui->graphicsView, ui->score, ui->progressBar); //игра запускается в специальной области //тут добавь ui->progressBar
    connect(game, &Game::gameEnded, this, &MainWindow::p);
    game->startGame(); //функция запуска игры
}

void MainWindow::p()
{
    isGameStarted = false;
    ui->pushButton->setEnabled(true);
}
