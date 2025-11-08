#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H

#include "plant.h"
#include "zombie.h"

/**
 * @brief 樱桃炸弹类，继承自Plant基类
 *
 * 樱桃炸弹是一种一次性使用的爆炸型植物，能够对周围区域的所有僵尸造成大量伤害。
 * 特点：
 * 1. 极高的攻击力，能够一次性消灭大部分僵尸
 * 2. 爆炸范围大，能够同时攻击多个僵尸
 * 3. 一次性使用，爆炸后自动消失
 * 4. 爆炸有延迟，需要等待动画播放完毕
 */
class CherryBomb : public Plant
{
public:
    /**
     * @brief 樱桃炸弹构造函数
     *
     * 初始化樱桃炸弹的属性，包括攻击力、生命值和动画
     */
    CherryBomb();

    /**
     * @brief 返回樱桃炸弹的外接矩形
     *
     * 根据状态返回不同的外接矩形，爆炸状态下范围更大
     *
     * @return 樱桃炸弹的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 处理樱桃炸弹的游戏逻辑
     *
     * 更新樱桃炸弹状态，处理爆炸逻辑和对僵尸的伤害
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

    /**
     * @brief 检测与其他图形项的碰撞
     *
     * 用于检测爆炸范围内的僵尸
     *
     * @param other 要检测碰撞的图形项
     * @param mode 选择模式（未使用）
     * @return 如果other是在爆炸范围内的僵尸，返回true；否则返回false
     */
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // CHERRYBOMB_H
