#ifndef PEA_H
#define PEA_H

#include "other.h"

/**
 * @brief 豌豆类，继承自Other基类
 *
 * 豌豆是由豌豆射手和双发射手发射的投射物，能够对僵尸造成伤害。
 * 特点：
 * 1. 直线飞行，从植物位置向右移动
 * 2. 碰到僵尸时造成伤害并消失
 * 3. 有普通豌豆和冰冻豌豆两种类型
 * 4. 冰冻豌豆除了造成伤害外，还能减慢僵尸移动速度
 */
class Pea : public Other
{
public:
    /**
     * @brief 豌豆构造函数
     *
     * 初始化豌豆的属性，包括攻击力、类型和移动速度
     *
     * @param attack 豌豆的攻击力，默认为0
     * @param flag 是否为冰冻豌豆，默认为false（普通豌豆）
     */
    Pea(int attack = 0, bool flag = false);

    /**
     * @brief 返回豌豆的外接矩形
     *
     * @return 豌豆的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制豌豆
     *
     * 根据豌豆类型绘制不同的图像（普通豌豆或冰冻豌豆）
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 检测与其他图形项的碰撞
     *
     * 用于检测同一行的僵尸，决定是否造成伤害
     *
     * @param other 要检测碰撞的图形项
     * @param mode 选择模式（未使用）
     * @return 如果other是同一行且足够近的僵尸，返回true；否则返回false
     */
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;

    /**
     * @brief 处理豌豆的游戏逻辑
     *
     * 更新豌豆位置，检测碰撞，处理伤害逻辑
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

private:
    /**
     * @brief 是否为冰冻豌豆
     *
     * true表示冰冻豌豆，能减慢僵尸移动速度；false表示普通豌豆
     */
    bool snow;

    /**
     * @brief 豌豆的攻击力
     *
     * 决定对僵尸造成的伤害值
     */
    int atk;

    /**
     * @brief 豌豆的移动速度
     *
     * 单位为像素/帧
     */
    qreal speed;
};

#endif // PEA_H
