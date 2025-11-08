#include "footballzombie.h"

/**
 * @brief 橄榄球僵尸构造函数
 *
 * 初始化橄榄球僵尸的属性：
 * - 生命值：1670（极高的耐久度，是所有僵尸中最高的）
 * - 攻击力：每秒100点伤害
 * - 移动速度：每秒80像素，但移动效率更高（除以2.5而非4.7）
 * - 设置橄榄球僵尸特有的行走动画
 */
FootballZombie::FootballZombie()
{
    // 设置生命值为1670，是所有僵尸类型中最高的，提供极强的耐久性
    hp = 1670;
    // 设置攻击力，每秒100点伤害，转换为每帧伤害
    atk = 100 * 33 / 1000;
    // 设置移动速度，每秒80像素，但除以2.5而非普通僵尸的4.7，意味着实际移动速度更快
    speed = 80.0 * 33 / 1000 / 2.5;
    // 设置橄榄球僵尸特有的行走动画，显示头戴橄榄球头盔的外观
    setMovie(":/images/FootballZombieWalk.gif");
}

/**
 * @brief 处理橄榄球僵尸的游戏逻辑
 *
 * 管理僵尸的三种状态：
 * - 状态0：行走状态，以较快速度向前移动
 * - 状态1：攻击状态，攻击植物
 * - 状态2：死亡状态，播放死亡动画
 *
 * 继承自Zombie基类的状态管理机制，但使用橄榄球僵尸特有的动画资源
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void FootballZombie::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

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
            // 设置橄榄球僵尸特有的死亡动画
            setMovie(":/images/FootballZombieDie.gif");
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
            // 设置橄榄球僵尸特有的攻击动画
            setMovie(":/images/FootballZombieAttack.gif");
        }
        return;
    }

    // 如果没有碰撞到植物且当前是攻击状态，切换回行走状态
    if (state)
    {
        // 切换回行走状态
        state = 0;
        // 设置橄榄球僵尸特有的行走动画
        setMovie(":/images/FootballZombieWalk.gif");
    }

    // 向前移动，由于speed值较大，移动速度比其他僵尸更快
    setX(x() - speed);
}
