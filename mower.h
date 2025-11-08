#ifndef MOWER_H
#define MOWER_H

#include "other.h"
#include "zombie.h"

/**
 * @brief 割草机类，继承自Other基类
 *
 * 割草机是游戏中的防御装置，位于每行的最左侧。
 * 当僵尸接近到一定距离时，割草机会被激活并向前移动，消灭该行上的所有僵尸。
 */
class Mower : public Other
{
public:
    /**
     * @brief 割草机构造函数
     *
     * 初始化割草机的状态和移动速度
     */
    Mower();

    /**
     * @brief 返回割草机的外接矩形
     *
     * @return 割草机的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制割草机
     *
     * 绘制割草机的静态图像
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 碰撞检测函数
     *
     * 检测割草机前方是否有僵尸进入触发范围
     *
     * @param other 要检测碰撞的其他图形项
     * @param mode 碰撞检测模式（未使用）
     * @return 如果有僵尸进入触发范围返回true，否则返回false
     */
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;

    /**
     * @brief 处理割草机的游戏逻辑
     *
     * 检测僵尸触发，激活割草机并向前移动消灭僵尸
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

private:
    /**
     * @brief 激活标志
     *
     * 表示割草机是否已被激活并开始移动
     * false：未激活，静止状态
     * true：已激活，向前移动状态
     */
    bool flag;

    /**
     * @brief 移动速度
     *
     * 割草机激活后的移动速度，单位：像素/帧
     */
    qreal speed;
};

#endif
