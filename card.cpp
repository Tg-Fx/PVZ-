#include "card.h"
#include "shop.h"

/**
 * @brief 植物名称到索引的映射
 *
 * 将植物名称映射到对应的索引，用于在其他静态数组中查找相关信息：
 * - SunFlower(向日葵): 0
 * - Peashooter(豌豆射手): 1
 * - CherryBomb(樱桃炸弹): 2
 * - WallNut(坚果墙): 3
 * - SnowPea(寒冰射手): 4
 * - PotatoMine(土豆地雷): 5
 * - Repeater(双发射手): 6
 */
const QMap<QString, int> Card::map = {{"SunFlower", 0}, {"Peashooter", 1}, {"CherryBomb", 2}, {"WallNut", 3},
                                      {"SnowPea", 4}, {"PotatoMine", 5}, {"Repeater", 6}};

/**
 * @brief 所有可用植物的名称数组
 *
 * 存储所有可用植物的名称，用于创建卡片和索引其他数组
 */
const QVector<QString> Card::name = {"SunFlower", "Peashooter", "CherryBomb", "WallNut",
                                     "SnowPea", "PotatoMine", "Repeater"};

/**
 * @brief 各植物的阳光成本数组
 *
 * 存储各植物的阳光成本，索引与name数组对应：
 * - SunFlower(向日葵): 50阳光
 * - Peashooter(豌豆射手): 100阳光
 * - CherryBomb(樱桃炸弹): 150阳光
 * - WallNut(坚果墙): 50阳光
 * - SnowPea(寒冰射手): 175阳光
 * - PotatoMine(土豆地雷): 25阳光
 * - Repeater(双发射手): 200阳光
 */
const QVector<int> Card::cost = {50, 100, 150, 50, 175, 25, 200};

/**
 * @brief 各植物的冷却时间数组
 *
 * 存储各植物的冷却时间（以帧为单位），索引与name数组对应：
 * - 227帧约为7.5秒（33ms/帧）
 * - 606帧约为20秒（33ms/帧）
 */
const QVector<int> Card::cool = {227, 227, 606, 606, 227, 606, 227};

/**
 * @brief Card类的构造函数
 *
 * 初始化卡片，设置植物名称和冷却计数器
 *
 * @param s 植物名称
 */
Card::Card(QString s)
{
    // 设置卡片对应的植物名称
    text = s;
    // 初始化冷却计数器为0，表示卡片刚开始处于冷却状态
    counter = 0;
}

/**
 * @brief 返回卡片的外接矩形
 *
 * @return 卡片的外接矩形，用于绘制和碰撞检测
 */
QRectF Card::boundingRect() const
{
    // 返回卡片的外接矩形，宽100，高60
    return QRectF(-50, -30, 100, 60);
}

/**
 * @brief 绘制卡片
 *
 * 绘制卡片背景、植物图标、阳光成本和冷却遮罩
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 缩放绘图设备，使卡片图像适应大小
    painter->scale(0.6, 0.58);

    // 绘制卡片背景
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/images/Card.png"));

    // 绘制植物图标
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/images/" + text + ".png"));

    // 设置字体大小为15点
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);

    // 绘制植物的阳光成本
    // painter->drawText(-30, 60, QString().sprintf("%3d", cost[map[text]]));
    painter->drawText(-30, 60, QString::asprintf("%3d", cost[map[text]]));

    // 如果卡片处于冷却状态，绘制半透明黑色遮罩
    if (counter < cool[map[text]])
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        // 遮罩高度随冷却进度减少，形成冷却进度条效果
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[map[text]])));
    }
}

/**
 * @brief 处理卡片的游戏逻辑
 *
 * 更新卡片的冷却状态
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void Card::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新卡片显示
    update();

    // 如果卡片处于冷却状态，冷却计数器递增
    if (counter < cool[map[text]])
        ++counter;
}

/**
 * @brief 处理鼠标按下事件
 *
 * 检查卡片是否可用（冷却完成且有足够阳光）
 *
 * @param event 鼠标事件
 */
void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(event)

    // 如果卡片处于冷却状态，拒绝接受事件（不能使用）
    if (counter < cool[map[text]])
        event->setAccepted(false);

    // 获取父项（商店）
    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());

    // 如果阳光不足，拒绝接受事件（不能使用）
    if (cost[map[text]] > shop->sun)
        event->setAccepted(false);

    // 设置鼠标指针为箭头
    setCursor(Qt::ArrowCursor);
}

/**
 * @brief 处理鼠标移动事件
 *
 * 实现卡片的拖放功能，创建拖放对象并设置相关数据
 *
 * @param event 鼠标事件
 */
void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 如果鼠标移动距离小于拖放启动距离，直接返回（防止意外拖放）
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance())
        return;

    // 创建拖放对象
    QDrag *drag = new QDrag(event->widget());

    // 创建MIME数据对象，用于传递植物信息
    QMimeData *mime = new QMimeData;

    // 加载植物图像
    QImage image(":/images/" + text + ".png");

    // 设置MIME数据的文本（植物名称）和图像
    mime->setText(text);
    mime->setImageData(image);

    // 设置拖放对象的MIME数据
    drag->setMimeData(mime);

    // 设置拖放对象的图像
    drag->setPixmap(QPixmap::fromImage(image));

    // 设置拖放对象的热点（鼠标指针相对于图像的位置）
    drag->setHotSpot(QPoint(35, 35));

    // 执行拖放操作
    drag->exec();

    // 设置鼠标指针为箭头
    setCursor(Qt::ArrowCursor);
}

/**
 * @brief 处理鼠标释放事件
 *
 * 重置鼠标指针
 *
 * @param event 鼠标事件
 */
void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(event)

    // 设置鼠标指针为箭头
    setCursor(Qt::ArrowCursor);
}
