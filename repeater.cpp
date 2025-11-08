#include "repeater.h"

/**
 * @brief 双发射手构造函数
 *
 * 初始化双发射手的属性：
 * - 攻击力：25（每颗豌豆）
 * - 生命值：300
 * - 攻击间隔：约1.4秒
 * - 初始动画
 */
Repeater::Repeater()
{
    // 设置每颗豌豆的攻击力为25
    atk = 25;
    // 设置生命值为300
    hp = 300;
    // 设置攻击间隔，约1.4秒(1400毫秒)，考虑游戏帧率(33ms/帧)
    time = int(1.4 * 1000 / 33);
    // 设置双发射手的初始动画
    setMovie(":/images/Repeater.gif");
}

/**
 * @brief 处理双发射手的游戏逻辑
 *
 * 定期检测前方是否有僵尸，如果有则连续发射两颗豌豆。
 * 两颗豌豆分别从不同位置发射，形成连续攻击效果。
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void Repeater::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新双发射手的显示
    update();

    // 生命值低于等于0，删除双发射手
    if (hp <= 0)
        delete this;
    // 计数器达到攻击间隔时间
    else if (++counter >= time)
    {
        // 重置计数器
        counter = 0;
        // 检测前方是否有僵尸
        QList<QGraphicsItem *> items = collidingItems();
        if (!collidingItems().isEmpty())
        {
            // 创建第一颗豌豆
            Pea *pea = new Pea(atk);
            // 设置第一颗豌豆的发射位置（双发射手前方32像素处）
            pea->setX(x() + 32);
            pea->setY(y());
            // 将第一颗豌豆添加到场景中
            scene()->addItem(pea);

            // 创建第二颗豌豆
            pea = new Pea(atk);
            // 设置第二颗豌豆的发射位置（双发射手前方64像素处）
            pea->setX(x() + 64);
            pea->setY(y());
            // 将第二颗豌豆添加到场景中
            scene()->addItem(pea);
            return;
        }
    }
}

/**
 * @brief 碰撞检测函数
 *
 * 检测双发射手前方是否存在僵尸，用于判断是否需要发射豌豆。
 * 只检测同一行上的僵尸。
 *
 * @param other 要检测碰撞的其他图形项
 * @param mode 碰撞检测模式（未使用）
 * @return 如果前方有僵尸且在同一行返回true，否则返回false
 */
bool Repeater::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(mode)
    // 检测是否为僵尸且在同一行
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y());
}
