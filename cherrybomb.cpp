#include "cherrybomb.h"

/**
 * @brief 樱桃炸弹构造函数
 *
 * 初始化樱桃炸弹的属性，包括攻击力、生命值和动画
 */
CherryBomb::CherryBomb()
{
    // 设置攻击力为1800点，非常高的伤害值，能够一次性消灭大部分僵尸
    atk = 1800;

    // 设置生命值为300点
    hp = 300;

    // 设置樱桃炸弹的初始动画
    setMovie(":/images/CherryBomb.gif");
}

/**
 * @brief 返回樱桃炸弹的外接矩形
 *
 * 根据状态返回不同的外接矩形，爆炸状态下范围更大
 *
 * @return 樱桃炸弹的外接矩形，用于绘制和碰撞检测
 */
QRectF CherryBomb::boundingRect() const
{
    // 如果处于爆炸状态(state=1)，返回一个更大的矩形表示爆炸范围
    // 否则返回基类Plant的默认外接矩形
    return state ? QRectF(-150, -150, 300, 300) : Plant::boundingRect();
}

/**
 * @brief 处理樱桃炸弹的游戏逻辑
 *
 * 更新樱桃炸弹状态，处理爆炸逻辑和对僵尸的伤害
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void CherryBomb::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新樱桃炸弹显示
    update();

    // 检查生命值，如果生命值小于等于0，删除自身
    if (hp <= 0)
        delete this;
    // 如果处于初始状态(state=0)且初始动画播放完毕，触发爆炸
    else if (state == 0 && movie->currentFrameNumber() == movie->frameCount() - 1)
    {
        // 切换到爆炸状态
        state = 1;

        // 设置爆炸动画
        setMovie(":/images/Boom.gif");

        // 获取爆炸范围内的所有图形项
        QList<QGraphicsItem *> items = collidingItems();

        // 对爆炸范围内的每个僵尸造成伤害
        foreach (QGraphicsItem *item, items)
        {
            // 将图形项转换为僵尸对象
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);

            // 对僵尸造成伤害
            zombie->hp -= atk;

            // 如果僵尸生命值小于等于0，设置为燃烧状态
            if (zombie->hp <= 0)
            {
                // 设置僵尸状态为死亡(state=3)
                zombie->state = 3;

                // 设置僵尸的燃烧动画
                zombie->setMovie(":/images/Burn.gif");
            }
        }
    }
    // 如果处于爆炸状态(state=1)且爆炸动画播放完毕，删除自身
    else if (state == 1 && movie->currentFrameNumber() == movie->frameCount() - 1)
        delete this;
}

/**
 * @brief 检测与其他图形项的碰撞
 *
 * 用于检测爆炸范围内的僵尸
 *
 * @param other 要检测碰撞的图形项
 * @param mode 选择模式（未使用）
 * @return 如果other是在爆炸范围内的僵尸，返回true；否则返回false
 */
bool CherryBomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(mode)

    // 检查other是否为僵尸类型，且与樱桃炸弹的距离小于160像素
    // 使用QLineF计算两点之间的距离
    return other->type() == Zombie::Type && QLineF(pos(), other->pos()).length() < 160;
}
