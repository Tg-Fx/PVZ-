#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>

/**
 * @brief 僵尸基类，继承自QGraphicsItem
 *
 * 僵尸是游戏中的敌人单位，从右向左移动并攻击植物。
 * 不同类型的僵尸有不同的生命值、攻击力和移动速度。
 */
class Zombie : public QGraphicsItem
{
public:
    int hp;      // 僵尸生命值
    int atk;     // 僵尸攻击力
    int state;   // 僵尸状态：0=行走，1=攻击，2=减速，3=死亡
    qreal speed; // 僵尸移动速度

    // 自定义图元类型，用于QGraphicsItem::type()识别对象
    enum { Type = UserType + 2};

    // 构造函数：初始化僵尸属性
    Zombie();

    // 析构函数：释放动画资源
    ~Zombie() override;

    // 返回僵尸的外接矩形，用于绘制和碰撞检测
    QRectF boundingRect() const override;

    // 绘制僵尸，包括身体和头部（如果有）
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // 碰撞检测：判断是否与植物碰撞
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;

    // 返回自定义类型，用于场景中的对象识别
    int type() const override;

    // 设置僵尸身体动画
    void setMovie(QString path);

    // 设置僵尸头部动画（某些僵尸可能会掉头）
    void setHead(QString path);

protected:
    QMovie *movie; // 僵尸身体动画
    QMovie *head;  // 僵尸头部动画
};

#endif // ZOOMBIE_H
