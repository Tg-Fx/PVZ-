#include "potatomine.h"

/**
 * @brief 土豆地雷构造函数
 *
 * 初始化土豆地雷的属性：
 * - 攻击力：1800（极高伤害）
 * - 生命值：300
 * - 准备时间：约15秒
 * - 初始动画（未激活状态）
 */
PotatoMine::PotatoMine()
{
    // 设置攻击力为1800，能够秒杀大多数僵尸
    atk = 1800;
    // 设置生命值为300
    hp = 300;
    // 设置准备时间，约15秒(15000毫秒)，考虑游戏帧率(33ms/帧)
    time = int(15.0 * 1000 / 33);
    // 设置土豆地雷的初始动画（未激活状态）
    setMovie(":/images/PotatoMine1.gif");
}

/**
 * @brief 返回土豆地雷的外接矩形
 *
 * 在爆炸状态时扩大碰撞检测范围，其他状态使用植物基类的默认矩形
 *
 * @return 土豆地雷的外接矩形
 */
QRectF PotatoMine::boundingRect() const
{
    // 爆炸状态时扩大碰撞检测范围，其他状态使用植物基类的默认矩形
    return state == 2 ? QRectF(-75, -75, 150, 150) : Plant::boundingRect();
}

/**
 * @brief 处理土豆地雷的游戏逻辑
 *
 * 管理土豆地雷的三种状态：
 * - 状态0：准备阶段，等待激活
 * - 状态1：激活状态，检测周围僵尸
 * - 状态2：爆炸状态，对周围僵尸造成伤害
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void PotatoMine::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新土豆地雷的显示
    update();

    // 生命值低于等于0，删除土豆地雷
    if (hp <= 0)
        delete this;
    // 状态0：准备阶段完成，切换到激活状态
    else if (state == 0 && ++counter >= time)
    {
        // 切换到激活状态
        state = 1;
        // 重置计数器
        counter = 0;
        // 设置激活后的检测间隔，约1秒
        time = int(1.0 * 1000 / 33);
        // 设置激活状态的动画
        setMovie(":/images/PotatoMine.gif");
    }
    // 状态1：激活状态，检测周围是否有僵尸
    else if (state == 1 && ++counter >= time)
    {
        // 重置计数器
        counter = 0;
        // 获取碰撞的图形项
        QList<QGraphicsItem *> items = collidingItems();
        // 如果检测到僵尸，触发爆炸
        if (!items.isEmpty())
        {
            // 切换到爆炸状态
            state = 2;
            // 设置爆炸动画
            setMovie(":/images/PotatoMineBomb.gif");
            // 对范围内的所有僵尸造成伤害
            foreach (QGraphicsItem *item, items)
            {
                Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
                // 对僵尸造成巨大伤害
                zombie->hp -= atk;
                // 如果僵尸生命值低于等于0，删除僵尸
                if (zombie->hp <= 0)
                    delete zombie;
            }
        }
    }
    // 状态2：爆炸状态，动画播放结束后删除自身
    else if (state == 2 && movie->currentFrameNumber() == movie->frameCount() - 1)
        delete this;
}

/**
 * @brief 碰撞检测函数
 *
 * 检测土豆地雷周围50像素范围内是否有僵尸，且在同一行
 *
 * @param other 要检测碰撞的其他图形项
 * @param mode 碰撞检测模式（未使用）
 * @return 如果有僵尸在同一行且距离小于50像素返回true，否则返回false
 */
bool PotatoMine::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(mode)
    // 检测是否为僵尸、在同一行且水平距离小于50像素
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 50;
}
