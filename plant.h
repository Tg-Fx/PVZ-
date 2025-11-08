#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>

// 植物基类
class Plant : public QGraphicsItem
{
public:
    int hp;
    int state; // 植物状态（具体含义由各派生类定义/使用）
    enum { Type = UserType + 1}; // 自定义图元类型，用于 QGraphicsItem::type() 识别对象
    Plant();
    ~Plant() override;
    QRectF boundingRect() const override; // 返回植物的边界矩形
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 绘制当前帧动画到外接矩形区域
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override; // 简化的碰撞判定：仅同一行且横向距离较近的僵尸算碰撞
    int type() const override; // 返回自定义类型常量，便于场景/逻辑识别
    void setMovie(QString path); // 设置并启动植物的动画资源（Gif/帧序列）
protected:
    QMovie *movie; // 动画对象，用于渲染当前帧
    int atk; // 攻击力
    int counter; // 通用计数器（用于冷却/节拍/状态切换等）
    int time; // 时间片或冷却时间
};

#endif // PLANT_H
