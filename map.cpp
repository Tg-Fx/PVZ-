#include "map.h"

/**
 * @brief 地图构造函数
 *
 * 初始化拖拽状态为false，并启用地图接受拖放操作
 */
Map::Map()
{
    // 初始状态：没有拖拽悬停
    dragOver = false;
    // 启用地图接受拖放操作
    setAcceptDrops(true);
}

/**
 * @brief 返回地图的外接矩形
 *
 * 定义地图的交互区域，覆盖整个游戏网格
 *
 * @return 地图的外接矩形
 */
QRectF Map::boundingRect() const
{
    // 返回地图的外接矩形，覆盖游戏网格区域
    // 左上角坐标(-369, -235)，宽738，高470
    return QRectF(-369, -235, 738, 470);
}

/**
 * @brief 绘制地图
 *
 * 地图本身是透明的，不进行实际绘制
 * 主要用于提供交互区域和碰撞检测
 *
 * @param painter 绘图设备（未使用）
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 标记未使用的参数，避免编译警告
    // 地图是透明的，不需要实际绘制
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // 可选：绘制调试边框
    // painter->setPen(Qt::black);
    // painter->drawRect(boundingRect());
}

/**
 * @brief 拖拽进入事件处理
 *
 * 验证拖拽数据是否包含文本（植物名称或"Shovel"）
 * 如果有效则接受事件并更新拖拽状态
 *
 * @param event 拖拽进入事件
 */
void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    // 检查拖拽数据是否包含文本（植物名称或"Shovel"）
    if (event->mimeData()->hasText())
    {
        // 接受拖拽事件
        event->setAccepted(true);
        // 设置拖拽悬停标志
        dragOver = true;
        // 更新地图显示（虽然当前没有视觉反馈）
        update();
    }
    else
        // 拒绝无效的拖拽数据
        event->setAccepted(false);
}

/**
 * @brief 拖拽离开事件处理
 *
 * 当拖拽物体离开地图区域时，重置拖拽悬停状态
 *
 * @param event 拖拽离开事件
 */
void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(event);
    // 重置拖拽悬停标志
    dragOver = false;
    // 更新地图显示
    update();
}

/**
 * @brief 拖放事件处理
 *
 * 处理植物种植或铲除操作：
 * - 将鼠标坐标转换为网格坐标
 * - 如果是铲子则执行铲除操作
 * - 如果是植物则执行种植操作
 *
 * @param event 拖放事件
 */
void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    // 重置拖拽悬停标志
    dragOver = false;

    // 检查拖拽数据是否包含文本
    if (event->mimeData()->hasText())
    {
        // 获取拖拽的文本（植物名称或"Shovel"）
        QString s = event->mimeData()->text();
        // 将事件位置转换为场景坐标
        QPointF pos = mapToScene(event->pos());

        // 将场景坐标转换为网格坐标
        // x坐标转换：将位置对齐到82像素宽的网格，起始位置290
        pos.setX((int(pos.x()) - 249) / 82 * 82 + 290);
        // y坐标转换：将位置对齐到98像素高的网格，起始位置130
        pos.setY((int(pos.y()) - 81) / 98 * 98 + 130);

        // 如果是铲子操作
        if (s == "Shovel")
        {
            // 获取场景中的铲子对象
            Shovel *shovel = qgraphicsitem_cast<Shovel *>(scene()->items(QPointF(830, 15))[0]);
            // 执行铲除植物操作
            shovel->removePlant(pos);
        }
        else
        {
            // 获取场景中的商店对象
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);
            // 执行种植植物操作
            shop->addPlant(s, pos);
        }
    }
    // 更新地图显示
    update();
}
