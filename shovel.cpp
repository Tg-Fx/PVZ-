#include "shovel.h"

/**
 * @brief 铲子构造函数
 *
 * 空实现，铲子不需要特殊的初始化操作
 */
Shovel::Shovel()
{

}

/**
 * @brief 返回铲子的外接矩形
 *
 * 定义铲子在场景中的绘制范围和碰撞检测区域
 *
 * @return 铲子的外接矩形
 */
QRectF Shovel::boundingRect() const
{
    // 返回铲子的外接矩形，中心对称，宽高各80像素
    return QRectF(-40, -40, 80, 80);
}

/**
 * @brief 绘制铲子
 *
 * 绘制铲子的背景框和铲子图标，背景框较大，图标较小
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // 绘制铲子背景框
    painter->drawPixmap(QRect(-40, -40, 80, 80), QPixmap(":/images/ShovelBank.png"));
    // 绘制铲子图标
    painter->drawPixmap(QRect(-35, -35, 70, 70), QPixmap(":/images/Shovel.png"));
}

/**
 * @brief 鼠标按下事件处理
 *
 * 设置鼠标光标为箭头形状，准备开始拖拽
 *
 * @param event 鼠标按下事件
 */
void Shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(event)
    // 设置鼠标光标为箭头形状
    setCursor(Qt::ArrowCursor);
}

/**
 * @brief 鼠标移动事件处理
 *
 * 实现铲子的拖拽功能：
 * - 检查移动距离是否达到拖拽阈值
 * - 创建拖拽操作和MIME数据
 * - 设置拖拽图像和热点
 * - 执行拖拽操作
 *
 * @param event 鼠标移动事件
 */
void Shovel::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 检查移动距离是否达到系统拖拽阈值，避免误操作
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance())
        return;

    // 创建拖拽操作
    QDrag *drag = new QDrag(event->widget());
    // 创建MIME数据用于传递拖拽信息
    QMimeData *mime = new QMimeData;
    // 加载铲子图标
    QImage image(":/images/Shovel.png");
    // 设置拖拽文本标识为"Shovel"
    mime->setText("Shovel");
    // 设置拖拽图像数据
    mime->setImageData(image);
    // 将MIME数据设置到拖拽操作
    drag->setMimeData(mime);
    // 设置拖拽时显示的图像，缩放为70x70像素
    drag->setPixmap(QPixmap::fromImage(image).scaled(70, 70));
    // 设置拖拽热点为中心点
    drag->setHotSpot(QPoint(35, 35));
    // 执行拖拽操作
    drag->exec();
    // 设置鼠标光标为箭头形状
    setCursor(Qt::ArrowCursor);
}

/**
 * @brief 鼠标释放事件处理
 *
 * 恢复鼠标光标为箭头形状
 *
 * @param event 鼠标释放事件
 */
void Shovel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(event)
    // 设置鼠标光标为箭头形状
    setCursor(Qt::ArrowCursor);
}

/**
 * @brief 移除植物
 *
 * 在指定位置查找植物，如果找到则删除该植物
 *
 * @param pos 要查找和移除植物的场景位置
 */
void Shovel::removePlant(QPointF pos)
{
    // 获取指定位置的所有图形项
    QList<QGraphicsItem *> items = scene()->items(pos);
    // 遍历所有图形项
    foreach (QGraphicsItem *item, items)
        // 如果图形项是植物类型
        if (item->type() == Plant::Type)
        {
            // 删除植物
            delete item;
            // 找到并删除一个植物后立即返回
            return;
        }
}
