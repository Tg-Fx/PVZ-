#include "mower.h"

/**
 * @brief 割草机构造函数
 *
 * 初始化割草机的状态为未激活，设置移动速度
 */
Mower::Mower()
{
    // 初始状态为未激活
    flag = false;
    // 设置移动速度，每秒270像素，转换为每帧移动距离
    speed = 270.0 * 33 / 1000;
}

/**
 * @brief 返回割草机的外接矩形
 *
 * 定义割草机在场景中的绘制范围和碰撞检测区域
 *
 * @return 割草机的外接矩形
 */
QRectF Mower::boundingRect() const
{
    // 返回割草机的外接矩形，中心对称，宽高各60像素
    return QRectF(-30, -30, 60, 60);
}

/**
 * @brief 绘制割草机
 *
 * 绘制割草机的静态PNG图像
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Mower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // 绘制割草机的静态图像
    painter->drawPixmap(QRect(-30, -30, 60, 60), QPixmap(":/images/LawnMower.png"));
}

/**
 * @brief 碰撞检测函数
 *
 * 检测割草机前方15像素范围内是否有僵尸，且在同一行
 * 用于判断是否需要激活割草机
 *
 * @param other 要检测碰撞的其他图形项
 * @param mode 碰撞检测模式（未使用）
 * @return 如果有僵尸在同一行且距离小于15像素返回true，否则返回false
 */
bool Mower::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(mode)
    // 检测是否为僵尸、在同一行且水平距离小于15像素
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

/**
 * @brief 处理割草机的游戏逻辑
 *
 * 检测前方是否有僵尸触发割草机，激活后向前移动并消灭所有接触到的僵尸
 * 当割草机移动到屏幕右侧边界时自动删除
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void Mower::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新割草机的显示
    update();

    // 检测碰撞的图形项（僵尸）
    QList<QGraphicsItem *> items = collidingItems();
    // 如果检测到僵尸，激活割草机
    if (!items.empty())
    {
        // 设置激活标志
        flag = true;
        // 消灭所有接触到的僵尸
        foreach (QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            // 直接将僵尸生命值设为0，触发死亡
            zombie->hp = 0;
        }
    }

    // 如果割草机已激活，向前移动
    if (flag)
        setX(x() + speed);

    // 如果割草机移动到屏幕右侧边界（x > 1069），删除割草机
    if (x() > 1069)
        delete this;
}
