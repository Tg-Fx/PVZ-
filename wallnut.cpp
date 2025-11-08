#include "wallnut.h"
#include <QDebug>

/**
 * @brief 坚果墙构造函数
 *
 * 初始化坚果墙的生命值为4000，并设置初始动画
 */
WallNut::WallNut()
{
    // 设置坚果墙的生命值为4000，是普通植物的4倍
    hp = 4000;
    // 设置坚果墙的初始动画
    setMovie(":/images/WallNut.gif");
}

/**
 * @brief 处理坚果墙的游戏逻辑
 *
 * 根据坚果墙的当前生命值更新其状态：
 * - 生命值低于等于0：删除坚果墙
 * - 生命值在1333以下：切换到严重损坏状态
 * - 生命值在1333到2667之间：切换到轻微损坏状态
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void WallNut::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新坚果墙的显示
    update();

    // 生命值低于等于0，删除坚果墙
    if (hp <= 0)
        delete this;
    // 生命值在1333以下且未处于严重损坏状态
    else if (hp <= 1333 && state != 2)
    {
        // 切换到严重损坏状态
        state = 2;
        // 设置严重损坏状态的动画
        setMovie(":/images/WallNut2.gif");
    }
    // 生命值在1333到2667之间且未处于轻微损坏状态
    else if (1333 < hp && hp <= 2667 && state != 1)
    {
        // 切换到轻微损坏状态
        state = 1;
        // 设置轻微损坏状态的动画
        setMovie(":/images/WallNut1.gif");
    }
}
