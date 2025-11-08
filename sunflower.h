#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h"
#include "sun.h"

/**
 * @brief 向日葵类，继承自Plant基类
 *
 * 向日葵是一种资源生产型植物，不具备攻击能力
 * 其主要功能是定期产生阳光(Sun)
 */
class SunFlower : public Plant
{
public:
    /**
     * @brief 向日葵构造函数
     *
     * 初始化向日葵的生命值、产生阳光的时间间隔，并设置动画
     */
    SunFlower();

    /**
     * @brief 推进游戏逻辑
     *
     * 重写自Plant::advance()，处理向日葵的行为逻辑：
     * 1. 检查生命值，决定是否存活
     * 2. 计时并在达到指定时间间隔时产生阳光
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;
};

#endif // SUNFLOWER_H
