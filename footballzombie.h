#ifndef FOOTBALLZOMBIE_H
#define FOOTBALLZOMBIE_H

#include "zombie.h"
#include "plant.h"

/**
 * @brief 橄榄球僵尸类，继承自Zombie基类
 *
 * 橄榄球僵尸是游戏中移动速度很快且耐久度高的僵尸类型，头戴橄榄球头盔。
 * 拥有极高的生命值和较快的移动速度，是游戏中的精英僵尸单位。
 */
class FootballZombie : public Zombie
{
public:
    /**
     * @brief 橄榄球僵尸构造函数
     *
     * 初始化橄榄球僵尸的生命值、攻击力和移动速度
     */
    FootballZombie();

    /**
     * @brief 处理橄榄球僵尸的游戏逻辑
     *
     * 管理僵尸的移动、攻击和死亡状态，继承自Zombie基类的状态机制
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;
};

#endif // FOOTBALLZOMBIE_H
