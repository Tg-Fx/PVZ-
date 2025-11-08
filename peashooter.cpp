#include "peashooter.h"

/**
 * @brief 豌豆射手构造函数
 *
 * 初始化豌豆射手的属性，包括攻击力、生命值、攻击间隔和动画
 */
Peashooter::Peashooter()
{
    // 设置攻击力为25点
    atk = 25;

    // 设置生命值为300点
    hp = 300;

    // 设置攻击间隔，约1.4秒(1400毫秒)，考虑游戏帧率(33ms/帧)
    time = int(1.4 * 1000 / 33);

    // 设置豌豆射手的动画
    setMovie(":/images/Peashooter.gif");
}

/**
 * @brief 处理豌豆射手的游戏逻辑
 *
 * 更新豌豆射手状态，检查生命值，定期发射豌豆攻击僵尸
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void Peashooter::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新豌豆射手显示
    update();

    // 检查生命值，如果生命值小于等于0，删除自身
    if (hp <= 0)
        delete this;
    // 如果计数器达到攻击间隔，尝试发射豌豆
    else if (++counter >= time)
    {
        // 重置计数器
        counter = 0;

        // 检查是否有碰撞项（同一行的僵尸）
        if (!collidingItems().isEmpty())
        {
            // 创建一个新的豌豆，攻击力与豌豆射手相同
            Pea *pea = new Pea(atk);

            // 设置豌豆的位置，在豌豆射手右侧32像素处
            pea->setX(x() + 32);
            pea->setY(y());

            // 将豌豆添加到场景中
            scene()->addItem(pea);

            // 发射豌豆后直接返回
            return;
        }
    }
}

/**
 * @brief 检测与其他图形项的碰撞
 *
 * 用于检测同一行的僵尸，决定是否发射豌豆
 *
 * @param other 要检测碰撞的图形项
 * @param mode 选择模式（未使用）
 * @return 如果other是同一行的僵尸，返回true；否则返回false
 */
bool Peashooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(mode)

    // 检查other是否为僵尸类型，且y坐标与豌豆射手相同（同一行）
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y());
}
