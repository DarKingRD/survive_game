#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow> // Qt widgets
#include <QGraphicsScene> //Qt widgets
#include <QTimer> //Qt core

class Game;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots:
    void on_pushButton_clicked();
    void p();

private:
    Ui::MainWindow *ui;
    QGraphicsView *graphicsView;
    QTimer *timer;
    Game *game;
    bool isGameStarted = false;// Новое свойство для отслеживания состояния игры
};
#endif // MAINWINDOW_H
