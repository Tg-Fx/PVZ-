#include "shop.h"

/**
 * @brief Shop类的构造函数
 *
 * 初始化商店，设置初始阳光数量为200，设置自然阳光生成计时器，
 * 并创建所有植物卡片作为商店的子项
 */
Shop::Shop()
{
    // 初始阳光数量为200
    sun = 200;
    // 初始化计数器
    counter = 0;
    // 设置自然阳光生成间隔，约7秒(7000毫秒)，考虑游戏帧率(33ms/帧)
    time = int(7.0 * 1000 / 33);

    // 创建所有植物卡片
    Card *card = nullptr;
    for (int i = 0; i < Card::name.size(); ++i)
    {
        // 根据Card::name静态数组中的植物名称创建卡片
        card = new Card(Card::name[i]);
        // 设置卡片的父项为商店，使卡片跟随商店移动
        card->setParentItem(this);
        // 设置卡片在商店中的位置，水平间隔65像素
        card->setPos(-157 + 65 * i, -2);
    }
}

/**
 * @brief 返回商店的外接矩形
 *
 * @return 商店的外接矩形，用于绘制和碰撞检测
 */
QRectF Shop::boundingRect() const
{
    // 返回商店的外接矩形，宽540，高90
    return QRectF(-270, -45, 540, 90);
}

/**
 * @brief 绘制商店
 *
 * 绘制商店背景图像和当前阳光数量
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 绘制商店背景图像
    painter->drawPixmap(QRect(-270, -45, 540, 90), QPixmap(":/images/Shop.png"));

    // 设置字体大小为15点
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);

    // 在指定位置绘制当前阳光数量
    painter->drawText(QRectF(-255, 18, 65, 22), Qt::AlignCenter, QString::number(sun));

    // 绘制一个点，可能是用于调试或标记
    painter->drawPoint(-220, 0);
}

/**
 * @brief 处理商店的游戏逻辑
 *
 * 定期在场景中生成自然阳光
 *
 * @param phase 更新阶段，0为准备阶段，1为执行阶段
 */
void Shop::advance(int phase)
{
    // 在准备阶段直接返回
    if (!phase)
        return;

    // 更新商店显示
    update();

    // 计数器递增，当达到设定时间时生成一个自然阳光
    if (++counter >= time)
    {
        // 重置计数器
        counter = 0;
        // 在场景中添加一个新的自然阳光
        scene()->addItem(new Sun);
    }
}

/**
 * @brief 在指定位置添加指定类型的植物
 *
 * 检查位置是否已有植物，扣除相应阳光，创建并添加植物到场景，
 * 并重置对应卡片的冷却计数器
 *
 * @param s 植物类型名称
 * @param pos 要放置植物的位置
 */
void Shop::addPlant(QString s, QPointF pos)
{
    // 获取指定位置的所有图形项
    QList<QGraphicsItem *> items = scene()->items(pos);

    // 检查该位置是否已有植物，如果有则直接返回
    foreach (QGraphicsItem *item, items)
        if (item->type() == Plant::Type)
            return;

    // 扣除相应的阳光成本
    sun -= Card::cost[Card::map[s]];

    // 根据植物名称创建对应类型的植物
    Plant *plant = nullptr;
    switch (Card::map[s])
    {
    case 0:
        plant = new SunFlower; break;  // 向日葵
    case 1:
        plant = new Peashooter; break; // 豌豆射手
    case 2:
        plant = new CherryBomb; break; // 樱桃炸弹
    case 3:
        plant = new WallNut; break;    // 坚果墙
    case 4:
        plant = new SnowPea; break;    // 寒冰射手
    case 5:
        plant = new PotatoMine; break; // 土豆地雷
    case 6:
        plant = new Repeater; break;   // 双发射手
    }

    // 设置植物位置并添加到场景
    plant->setPos(pos);
    scene()->addItem(plant);

    // 获取商店的所有子项（即所有卡片）
    QList<QGraphicsItem *> child = childItems();

    // 找到对应的卡片并重置其冷却计数器
    foreach (QGraphicsItem *item, child)
    {
        Card *card = qgraphicsitem_cast<Card *>(item);
        if (card->text == s)
            card->counter = 0;
    }

    // 重置自然阳光生成计数器，可能是为了平衡游戏节奏
    counter = 0;
}
