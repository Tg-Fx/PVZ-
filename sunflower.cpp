#include "sunflower.h"
#include <QDebug>

/**
 * @brief 向日葵构造函数
 *
 * 初始化向日葵的基本属性：
 * - 生命值设为300
 * - 产生阳光的时间间隔约为10秒(10000毫秒)，考虑游戏帧率(33ms每帧)进行换算
 * - 设置向日葵的动画为SunFlower.gif
 */
SunFlower::SunFlower()
{
    // 设置生命值为300
    hp = 300;

    // 设置产生阳光的时间间隔
    // 计算方式：10秒 * 1000(转换为毫秒) / 33(每帧毫秒数)
    // 即大约每10秒产生一个阳光
    time = int(10.0 * 1000 / 33);

    // 设置向日葵的动画
    setMovie(":/images/SunFlower.gif");
}

/**
 * @brief 处理向日葵的游戏逻辑
 *
 * 该函数在每一帧被调用，负责：
 * 1. 更新向日葵的显示
 * 2. 检查生命值，如果生命值小于等于0则删除自身
 * 3. 计时并在达到指定时间间隔时产生阳光
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void SunFlower::advance(int phase)
{
    // 在准备阶段直接返回，只在执行阶段处理逻辑
    if (!phase)
        return;

    // 更新显示
    update();

    // 检查生命值，如果死亡则删除自身
    if (hp <= 0)
        delete this;
    // 计时并产生阳光
    else if (++counter >= time)
    {
        // 重置计数器
        counter = 0;

        // 在当前位置创建一个新的阳光对象并添加到场景中
        scene()->addItem(new Sun(pos()));
    }
}


