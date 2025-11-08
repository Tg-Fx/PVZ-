#ifndef POTATOMINE_H
#define POTATOMINE_H

#include "plant.h"
#include "zombie.h"

/**
 * @brief 土豆地雷类，继承自Plant基类
 *
 * 土豆地雷是一种埋设在地下的爆炸型植物，需要时间准备才能激活。
 * 激活后当有僵尸接近时会爆炸，对一定范围内的僵尸造成巨大伤害。
 */
class PotatoMine : public Plant
{
public:
    /**
     * @brief 土豆地雷构造函数
     *
     * 初始化土豆地雷的攻击力、生命值和准备时间
     */
    PotatoMine();

    /**
     * @brief 返回土豆地雷的外接矩形
     *
     * 在爆炸状态时扩大碰撞检测范围
     *
     * @return 土豆地雷的外接矩形
     */
    QRectF boundingRect() const override;

    /**
     * @brief 处理土豆地雷的游戏逻辑
     *
     * 管理土豆地雷的准备、激活和爆炸状态
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

    /**
     * @brief 碰撞检测函数
     *
     * 检测土豆地雷周围是否有僵尸进入爆炸范围
     *
     * @param other 要检测碰撞的其他图形项
     * @param mode 碰撞检测模式（未使用）
     * @return 如果有僵尸进入爆炸范围返回true，否则返回false
     */
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // POTATOMINE_H
