#ifndef CONEZOMBIE_H
#define CONEZOMBIE_H

#include "zombie.h"
#include "plant.h"

/**
 * @brief 路障僵尸类，继承自Zombie基类
 *
 * 路障僵尸是普通僵尸的强化版本，头上戴有路障提供额外的防护。
 * 拥有比普通僵尸更高的生命值，但移动速度和攻击力与普通僵尸相同。
 */
class ConeZombie : public Zombie
{
public:
    /**
     * @brief 路障僵尸构造函数
     *
     * 初始化路障僵尸的生命值、攻击力和移动速度
     */
    ConeZombie();

    /**
     * @brief 处理路障僵尸的游戏逻辑
     *
     * 管理僵尸的移动、攻击和死亡状态
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;
};

#endif // CONEZOMBIE_H
