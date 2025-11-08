#ifndef SNOWPEA_H
#define SNOWPEA_H

#include "plant.h"
#include "zombie.h"
#include "pea.h"

/**
 * @brief 寒冰射手类，继承自Plant基类
 *
 * 寒冰射手是一种能够发射冰冻豌豆的植物，其攻击具有减速效果。
 * 被冰冻豌豆击中的僵尸会移动速度减慢，为其他植物创造更多攻击时间。
 */
class SnowPea : public Plant
{
public:
    /**
     * @brief 寒冰射手构造函数
     *
     * 初始化寒冰射手的攻击力、生命值和动画
     */
    SnowPea();

    /**
     * @brief 处理寒冰射手的游戏逻辑
     *
     * 定期检测前方是否有僵尸，有则发射冰冻豌豆
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

    /**
     * @brief 碰撞检测函数
     *
     * 检测寒冰射手前方是否存在僵尸
     *
     * @param other 要检测碰撞的其他图形项
     * @param mode 碰撞检测模式（未使用）
     * @return 如果前方有僵尸返回true，否则返回false
     */
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // SNOWPEA_H
