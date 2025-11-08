#include "sun.h"
#include "shop.h"

/**
 * @brief 默认构造函数，创建从天空掉落的阳光
 *
 * 初始化阳光的属性：
 * - 设置随机的目标位置在地图范围内
 * - 初始位置在屏幕上方
 * - 设置下落速度、存在时间和动画
 */
Sun::Sun()
{
    // 设置随机目标位置：x坐标在290到290+82*7之间，y坐标在130到130+98*5之间
    // 这个范围对应游戏地图的有效区域
    // dest = QPointF(290 + qrand() % (82 * 7), 130 + qrand() % (98 * 5));
    dest = QPointF(290 + QRandomGenerator::global()->bounded(82 * 7),
                   130 + QRandomGenerator::global()->bounded(98 * 5));

    // 设置初始位置在目标x坐标的正上方，y坐标为70（屏幕上方）
    setPos(QPointF(dest.x(), 70));

    // 设置下落速度：60像素/秒 * 50 / 1000
    speed = 60.0 * 50 / 1000;

    // 初始化计数器
    counter = 0;

    // 设置阳光存在时间为10秒（考虑游戏帧率33ms每帧）
    time = int(10.0 * 1000 / 33);

    // 创建并启动阳光动画
    movie = new QMovie(":/images/Sun.gif");
    movie->start();

    // 设置只接受鼠标左键点击
    setAcceptedMouseButtons(Qt::LeftButton);
}

/**
 * @brief 带参数构造函数，创建从指定位置产生的阳光
 *
 * @param pos 阳光产生的初始位置，通常是向日葵的位置
 */
Sun::Sun(QPointF pos)
{
    // 设置目标位置在初始位置附近的随机位置
    // x坐标在pos.x()-15到pos.x()+15之间
    // y坐标在pos.y()+15到pos.y()+45之间
    dest = QPointF(pos.x() + QRandomGenerator::global()->bounded(30) - 15,
                   pos.y() + QRandomGenerator::global()->bounded(30) + 15);

    // 设置初始位置在目标x坐标处，y坐标与传入位置相同
    setPos(QPointF(dest.x(), pos.y()));

    // 设置下落速度
    speed = 60 * 50 / 1000;

    // 初始化计数器
    counter = 0;

    // 设置阳光存在时间为10秒
    time = int(10.0 * 1000 / 33);

    // 创建并启动阳光动画
    movie = new QMovie(":/images/Sun.gif");
    movie->start();

    // 设置只接受鼠标左键点击
    setAcceptedMouseButtons(Qt::LeftButton);
}

/**
 * @brief 析构函数，释放动画资源
 */
Sun::~Sun()
{
    // 释放动画资源，避免内存泄漏
    if (movie)
        delete movie;
}

/**
 * @brief 返回阳光的外接矩形
 *
 * @return 阳光的外接矩形，用于绘制和碰撞检测
 */
QRectF Sun::boundingRect() const
{
    // 返回一个以原点为中心，宽高为70的正方形
    return QRectF(-35, -35, 70, 70);
}

/**
 * @brief 绘制阳光
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 在外接矩形内绘制当前动画帧
    painter->drawImage(boundingRect(), movie->currentImage());
}

/**
 * @brief 处理鼠标点击事件
 *
 * 当玩家点击阳光时，增加商店的阳光数量，并标记阳光为已收集状态
 *
 * @param event 鼠标事件
 */
void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

    // 获取场景中位于(300,15)位置的商店对象
    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);

    // 增加商店的阳光数量25个
    shop->sun += 25;

    // 将计数器设为最大值，使阳光在下一帧被删除
    counter = time;

    // 标记事件已被处理
    event->setAccepted(true);
}

/**
 * @brief 处理阳光的游戏逻辑
 *
 * 控制阳光的下落动画和生命周期
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void Sun::advance(int phase)
{
    // 在准备阶段直接返回，只在执行阶段处理逻辑
    if (!phase)
        return;

    // 更新显示
    update();

    // 计数器增加，如果达到最大存在时间则删除自身
    if (++counter >= time)
        delete this;
    // 如果当前位置未到达目标位置，则继续下落
    else if (y() < dest.y())
        setY(y() + speed);
}
