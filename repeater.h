#ifndef REAPTER_H
#define REAPTER_H

#include "plant.h"
#include "zombie.h"
#include "pea.h"

/**
 * @brief 双发射手类，继承自Plant基类
 *
 * 双发射手是一种能够连续发射两颗豌豆的植物，每次攻击会发射两颗豌豆。
 * 相比普通豌豆射手，双发射手在相同时间内能造成双倍伤害。
 */
class Repeater : public Plant
{
public:
    /**
     * @brief 双发射手构造函数
     *
     * 初始化双发射手的攻击力、生命值和攻击间隔
     */
    Repeater();

    /**
     * @brief 处理双发射手的游戏逻辑
     *
     * 定期检测前方是否有僵尸，有则连续发射两颗豌豆
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

    /**
     * @brief 碰撞检测函数
     *
     * 检测双发射手前方是否存在僵尸
     *
     * @param other 要检测碰撞的其他图形项
     * @param mode 碰撞检测模式（未使用）
     * @return 如果前方有僵尸返回true，否则返回false
     */
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // REAPTER_H
