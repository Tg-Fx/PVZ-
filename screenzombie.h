#ifndef SCREENZOMBIE_H
#define SCREENZOMBIE_H

#include "zombie.h"
#include "plant.h"

/**
 * @brief 读报僵尸类，继承自Zombie基类
 *
 * 读报僵尸是游戏中一种特殊的僵尸类型，手持路牌（屏幕）提供额外的防护。
 * 拥有与铁桶僵尸相同的高生命值，但移动速度和攻击力与普通僵尸相同。
 * 当路牌被破坏后，读报僵尸会进入愤怒状态。
 */
class ScreenZombie : public Zombie
{
public:
    /**
     * @brief 读报僵尸构造函数
     *
     * 初始化读报僵尸的生命值、攻击力和移动速度
     */
    ScreenZombie();

    /**
     * @brief 处理读报僵尸的游戏逻辑
     *
     * 管理僵尸的移动、攻击和死亡状态，继承自Zombie基类的状态机制
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;
};

#endif // SCREENZOMBIE_H
