#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"
#include "zombie.h"
#include "pea.h"

/**
 * @brief 豌豆射手类，继承自Plant基类
 *
 * 豌豆射手是基础的攻击型植物，能够定期发射豌豆攻击同一行的僵尸。
 * 特点：
 * 1. 中等生命值
 * 2. 中等攻击力
 * 3. 适中的攻击速度
 * 4. 直线攻击，只能攻击同一行的僵尸
 */
class Peashooter : public Plant
{
public:
    /**
     * @brief 豌豆射手构造函数
     *
     * 初始化豌豆射手的属性，包括攻击力、生命值、攻击间隔和动画
     */
    Peashooter();

    /**
     * @brief 处理豌豆射手的游戏逻辑
     *
     * 更新豌豆射手状态，检查生命值，定期发射豌豆攻击僵尸
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

    /**
     * @brief 检测与其他图形项的碰撞
     *
     * 用于检测同一行的僵尸，决定是否发射豌豆
     *
     * @param other 要检测碰撞的图形项
     * @param mode 选择模式（未使用）
     * @return 如果other是同一行的僵尸，返回true；否则返回false
     */
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // PEASHOOTER_H
