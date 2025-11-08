#include "pea.h"
#include "zombie.h"

/**
 * @brief 豌豆构造函数
 *
 * 初始化豌豆的属性，包括攻击力、类型和移动速度
 *
 * @param attack 豌豆的攻击力，由发射的植物决定
 * @param flag 是否为冰冻豌豆，普通豌豆为false，寒冰射手发射的为true
 */
Pea::Pea(int attack, bool flag)
{
    // 设置豌豆类型，true表示冰冻豌豆，false表示普通豌豆
    snow = flag;

    // 设置攻击力，由发射的植物传入
    atk = attack;

    // 设置移动速度，约360像素/秒，考虑游戏帧率(33ms/帧)
    speed = 360.0 * 33 / 1000;
}

/**
 * @brief 返回豌豆的外接矩形
 *
 * @return 豌豆的外接矩形，用于绘制和碰撞检测
 */
QRectF Pea::boundingRect() const
{
    // 返回豌豆的外接矩形，宽24，高24，相对于中心点偏移
    return QRectF(-12, -28, 24, 24);
}

/**
 * @brief 绘制豌豆
 *
 * 根据豌豆类型绘制不同的图像（普通豌豆或冰冻豌豆）
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 根据豌豆类型绘制不同的图像
    // 如果snow为true，绘制冰冻豌豆；否则绘制普通豌豆
    painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(snow ? ":/images/PeaSnow.png" : ":/images/Pea.png"));
}

/**
 * @brief 检测与其他图形项的碰撞
 *
 * 用于检测同一行的僵尸，决定是否造成伤害
 *
 * @param other 要检测碰撞的图形项
 * @param mode 选择模式（未使用）
 * @return 如果other是同一行且足够近的僵尸，返回true；否则返回false
 */
bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(mode)

    // 检查other是否为僵尸类型，且y坐标与豌豆相同（同一行），x坐标差小于15像素（足够近）
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

/**
 * @brief 处理豌豆的游戏逻辑
 *
 * 更新豌豆位置，检测碰撞，处理伤害逻辑
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void Pea::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新豌豆显示
    update();

    // 获取碰撞的图形项（僵尸）
    QList<QGraphicsItem *> items = collidingItems();

    // 如果有碰撞的僵尸
    if (!items.isEmpty())
    {
        // 随机选择一个碰撞的僵尸（如果有多个）
        Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[QRandomGenerator::global()->bounded(items.size())]);

        // 对僵尸造成伤害
        zombie->hp -= atk;

        // 如果是冰冻豌豆且僵尸速度足够快，减慢僵尸移动速度
        if (snow && zombie->speed > 0.55)
            zombie->speed /= 2;

        // 豌豆击中僵尸后删除自身
        delete this;
        return;
    }

    // 如果没有碰撞的僵尸，向右移动
    setX(x() + speed);

    // 如果豌豆超出屏幕范围，删除自身
    if (x() > 1069)
        delete this;
}
