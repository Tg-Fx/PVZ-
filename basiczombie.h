#ifndef BASICZOMBIE_H
#define BASICZOMBIE_H

#include "zombie.h"
#include "plant.h"


/**
 * @brief 普通僵尸类，继承自Zombie基类
 *
 * 普通僵尸是最基础的僵尸类型，以缓慢的速度向前移动，遇到植物时会停下来攻击。
 * 具有标准的生命值、攻击力和移动速度，是游戏中最常见的僵尸敌人。
 */
class BasicZombie : public Zombie
{
public:
    /**
     * @brief 普通僵尸构造函数
     *
     * 初始化普通僵尸的生命值、攻击力和移动速度
     */
    BasicZombie();

    /**
     * @brief 处理普通僵尸的游戏逻辑
     *
     * 管理僵尸的移动、攻击和死亡状态
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;
};

#endif // BASICZOMBIE_H
