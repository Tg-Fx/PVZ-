#include "basiczombie.h"
#include <QRandomGenerator>

/**
 * @brief 普通僵尸构造函数
 *
 * 初始化普通僵尸的属性：
 * - 生命值：270
 * - 攻击力：每秒100点伤害
 * - 移动速度：每秒80像素
 * - 随机选择行走动画
 */
BasicZombie::BasicZombie()
{
    // 设置生命值为270
    hp = 270;
    // 设置攻击力，每秒100点伤害，转换为每帧伤害
    atk = 100 * 33 / 1000;
    // 设置移动速度，每秒80像素，转换为每帧移动距离
    speed = 80.0 * 33 / 1000 / 4.7;
    // 随机选择两种行走动画之一，增加视觉多样性
    if (QRandomGenerator::global()->bounded(2))
        setMovie(":/images/ZombieWalk1.gif");
    else
        setMovie(":/images/ZombieWalk2.gif");
}

/**
 * @brief 处理普通僵尸的游戏逻辑
 *
 * 管理僵尸的三种状态：
 * - 状态0：行走状态，向前移动
 * - 状态1：攻击状态，攻击植物
 * - 状态2：死亡状态，播放死亡动画
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void BasicZombie::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase) return;

    // 更新僵尸的显示
    update();

    // 生命值低于等于0，进入死亡状态
    if (hp <= 0)
    {
        // 如果当前不是死亡状态，切换到死亡状态
        if (state < 2)
        {
            // 切换到死亡状态
            state = 2;
            // 设置死亡动画
            setMovie(":/images/ZombieDie.gif");
            // 设置头部动画（死亡时头部可能分离）
            setHead(":/images/ZombieHead.gif");
        }
        // 死亡动画播放结束后删除僵尸
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }

    // 检测碰撞的图形项（植物）
    QList<QGraphicsItem *> items = collidingItems();
    // 如果检测到植物，进入攻击状态
    if (!items.isEmpty())
    {
        // 获取碰撞到的第一个植物
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
        // 对植物造成伤害
        plant->hp -= atk;
        // 如果当前不是攻击状态，切换到攻击状态
        if (state != 1)
        {
            // 切换到攻击状态
            state = 1;
            // 设置攻击动画
            setMovie(":/images/ZombieAttack.gif");
        }
        return;
    }

    // 如果没有碰撞到植物且当前是攻击状态，切换回行走状态
    if (state)
    {
        // 切换回行走状态
        state = 0;
        // 随机选择行走动画
        if (QRandomGenerator::global()->bounded(2))
            setMovie(":/images/ZombieWalk1.gif");
        else
            setMovie(":/images/ZombieWalk2.gif");
    }

    // 向前移动
    setX(x() - speed);
}
