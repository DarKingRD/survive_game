#include "player.h"

Player::Player(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    QFileInfo fileinfo("cub1.jpg");
    QString str = fileinfo.absoluteFilePath();
    QByteArray bytes = str.toUtf8(); // Получаем QByteArray с UTF-8 представлением строки.
    const char* c_str = bytes.constData(); // Получаем указатель на массив символов типа char.
    // Загружаем текстуру из файла
    QPixmap playerPixmap(c_str);
    // Устанавливаем текстуру для игрока
    setBrush(playerPixmap);
    // Изменяем размеры игрока по размерам текстуры
    setRect(0, 0, playerPixmap.width(), playerPixmap.height());
}

void Player::keyPressEvent(QKeyEvent *event)
{
    int step = 20;
    if (event->key() == Qt::Key_Left)
    {
        if (x() > 0)
        {
            setPos(x() - step, y());
        }
    }
    else if (event->key() == Qt::Key_Right)
    {
        if (x() + rect().width() < scene()->width())
        {
            setPos(x() + step, y());
        }
    }
    else if (event->key() == Qt::Key_Up)
    {
        if (y() > 0)
        {
            setPos(x(), y() - step);
        }
    }
    else if (event->key() == Qt::Key_Down)
    {
        if (y() + rect().height() < scene()->height())
        {
            setPos(x(), y() + step);
        }
    }
    else
    {
        QGraphicsRectItem::keyPressEvent(event);
    }
}
