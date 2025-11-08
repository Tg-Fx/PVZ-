#ifndef WALLNUT_H
#define WALLNUT_H

#include "plant.h"

/**
 * @brief 坚果墙类，继承自Plant基类
 *
 * 坚果墙是一种高生命值的防御型植物，主要作用是为其他植物抵挡僵尸的攻击。
 * 随着生命值的减少，坚果墙的外观会发生变化，显示不同程度的损坏状态。
 */
class WallNut : public Plant
{
public:
    /**
     * @brief 坚果墙构造函数
     *
     * 初始化坚果墙的生命值和动画
     */
    WallNut();

    /**
     * @brief 处理坚果墙的游戏逻辑
     *
     * 根据生命值更新坚果墙的状态和外观
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;
};

#endif // WALLNUT_H
