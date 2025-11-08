#ifndef BUCKETZOMBIE_H
#define BUCKETZOMBIE_H

#include "zombie.h"
#include "plant.h"

/**
 * @brief 铁桶僵尸类，继承自Zombie基类
 *
 * 铁桶僵尸是游戏中耐久度很高的僵尸类型，头上戴着铁桶提供极强的防护。
 * 拥有极高的生命值，是普通僵尸生命值的5倍多，但移动速度和攻击力与普通僵尸相同。
 */
class BucketZombie : public Zombie
{
public:
    /**
     * @brief 铁桶僵尸构造函数
     *
     * 初始化铁桶僵尸的生命值、攻击力和移动速度
     */
    BucketZombie();

    /**
     * @brief 处理铁桶僵尸的游戏逻辑
     *
     * 管理僵尸的移动、攻击和死亡状态，继承自Zombie基类的状态机制
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;
};

#endif // BUCKETZOMBIE_H
