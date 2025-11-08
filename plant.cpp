#include "plant.h"
#include "zombie.h"


Plant::Plant()
{
    // 初始化动画指针为空；基础属性清零
    movie = nullptr;
    atk = counter = state = time = 0;
}

Plant::~Plant()
{
    // 释放动画资源，避免内存泄漏
    delete movie;
}

QRectF Plant::boundingRect() const
{
    // 固定大小的外接矩形
    return QRectF(-35, -35, 70, 70);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // 将当前动画帧绘制到 boundingRect 范围
    painter->drawImage(boundingRect(), movie->currentImage());
}

bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    // 仅检测与“僵尸类型”对象的碰撞：
    // - 必须同一行（y 坐标近似相等）
    // - 横向距离在 30 像素以内
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 30;
}

int Plant::type() const
{
    // 返回该类的自定义图元类型编号
    return Type;
}

void Plant::setMovie(QString path)
{
    // 切换动画资源：清理旧动画，加载并启动新动画
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}

