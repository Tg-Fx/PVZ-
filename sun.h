#ifndef SUN_H
#define SUN_H

#include "other.h"

/**
 * @brief 阳光类，继承自Other基类
 *
 * 阳光有两种来源：
 * 1. 自然掉落：从天空随机位置掉落到地图上的随机位置
 * 2. 向日葵产生：从向日葵位置产生并掉落到附近位置
 *
 * 阳光会在一段时间后自动消失，玩家需要及时点击收集
 */
class Sun : public Other
{
public:
    /**
     * @brief 默认构造函数，创建从天空掉落的阳光
     *
     * 在地图上方随机位置创建阳光，并设置其掉落目标位置为地图内随机位置
     */
    Sun();

    /**
     * @brief 带参数构造函数，创建从指定位置(通常是向日葵位置)产生的阳光
     *
     * @param pos 阳光产生的初始位置，通常是向日葵的位置
     */
    Sun(QPointF pos);

    /**
     * @brief 析构函数，释放动画资源
     */
    ~Sun() override;

    /**
     * @brief 返回阳光的外接矩形
     *
     * @return 阳光的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制阳光
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 处理鼠标点击事件
     *
     * 当玩家点击阳光时，增加商店的阳光数量，并标记阳光为已收集状态
     *
     * @param event 鼠标事件
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief 处理阳光的游戏逻辑
     *
     * 控制阳光的下落动画和生命周期
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

private:
    QMovie *movie;  // 阳光动画
    QPointF dest;   // 阳光的目标位置
    int counter;    // 计数器，用于计算阳光存在的时间
    int time;       // 阳光的最大存在时间
    qreal speed;    // 阳光下落的速度
};

#endif // SUN_H
