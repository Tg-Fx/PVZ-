#include "snowpea.h"

/**
 * @brief 寒冰射手构造函数
 *
 * 初始化寒冰射手的属性：
 * - 攻击力：25
 * - 生命值：300
 * - 攻击间隔：约1.4秒
 * - 初始动画
 */
SnowPea::SnowPea()
{
    // 设置攻击力为25
    atk = 25;
    // 设置生命值为300
    hp = 300;
    // 设置攻击间隔，约1.4秒(1400毫秒)，考虑游戏帧率(33ms/帧)
    time = int(1.4 * 1000 / 33);
    // 设置寒冰射手的初始动画
    setMovie(":/images/SnowPea.gif");
}

/**
 * @brief 处理寒冰射手的游戏逻辑
 *
 * 定期检测前方是否有僵尸，如果有则发射冰冻豌豆。
 * 冰冻豌豆具有减速效果，可以减缓被击中僵尸的移动速度。
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void SnowPea::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新寒冰射手的显示
    update();

    // 生命值低于等于0，删除寒冰射手
    if (hp <= 0)
        delete this;
    // 计数器达到攻击间隔时间
    else if (++counter >= time)
    {
        // 重置计数器
        counter = 0;
        // 检测前方是否有僵尸
        if (!collidingItems().isEmpty())
        {
            // 创建冰冻豌豆，第二个参数true表示这是冰冻豌豆
            Pea *pea = new Pea(atk, true);
            // 设置豌豆的发射位置（寒冰射手前方32像素处）
            pea->setX(x() + 32);
            pea->setY(y());
            // 将豌豆添加到场景中
            scene()->addItem(pea);
            return;
        }
    }
}

/**
 * @brief 碰撞检测函数
 *
 * 检测寒冰射手前方是否存在僵尸，用于判断是否需要发射豌豆。
 * 只检测同一行上的僵尸。
 *
 * @param other 要检测碰撞的其他图形项
 * @param mode 碰撞检测模式（未使用）
 * @return 如果前方有僵尸且在同一行返回true，否则返回false
 */
bool SnowPea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(mode)
    // 检测是否为僵尸且在同一行
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y());
}
