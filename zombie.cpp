#include "zombie.h"
#include "plant.h"
#include <QDebug>

/**
 * @brief 僵尸类构造函数
 *
 * 初始化僵尸的基本属性，包括动画指针、生命值、攻击力、状态和速度
 */
Zombie::Zombie()
{
    // 初始化动画指针为空
    movie = head = nullptr;
    // 初始化生命值、攻击力和状态为0
    hp = atk = state = 0;
    // 初始化移动速度为0
    speed = 0.0;
}

/**
 * @brief 僵尸类析构函数
 *
 * 释放动画资源，防止内存泄漏
 */
Zombie::~Zombie()
{
    delete movie;
    delete head;
}

/**
 * @brief 获取僵尸的外接矩形
 *
 * 定义僵尸在场景中的绘制范围和碰撞检测区域
 * @return 僵尸的外接矩形
 */
QRectF Zombie::boundingRect() const
{
    // 返回一个较大的矩形，确保能容纳僵尸的完整图像
    // 左上角坐标(-80,-100)，宽200，高140
    return QRectF(-80, -100, 200, 140);
}

/**
 * @brief 绘制僵尸
 *
 * 根据僵尸的状态绘制其身体和头部（如果有）
 * 当僵尸被减速时，会对图像进行蓝色处理
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 获取当前身体动画帧
    QImage image = movie->currentImage();

    // 当僵尸速度较慢且非死亡状态时，应用蓝色效果（表示被减速）
    if (speed < 0.55 && state != 3)
    {
        // 如果不是减速状态，则降低动画速度
        if (state != 2)
            movie->setSpeed(50);

        // 获取图像尺寸
        int w = image.width();
        int h = image.height();

        // 遍历图像像素，增加蓝色通道值
        for (int i = 0; i < h; ++i)
        {
            uchar *line = image.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 200;  // 设置蓝色通道值为200
        }
    }

    // 绘制僵尸身体
    painter->drawImage(QRectF(-70, -100, 140, 140), image);

    // 如果有头部动画，则绘制头部
    if (head)
    {
        image = head->currentImage();

        // 同样对头部应用蓝色效果（如果被减速）
        if (speed < 0.55)
        {
            int w = image.width();
            int h = image.height();
            for (int i = 0; i < h; ++i)
            {
                uchar *line = image.scanLine(i);
                for (int j = 5; j < w - 5; ++j)
                    line[j << 2] = 200;  // 设置蓝色通道值为200
            }
        }

        // 绘制僵尸头部，位置略有偏移
        painter->drawImage(QRectF(0, -100, 140, 140), image);
    }
}

/**
 * @brief 碰撞检测
 *
 * 判断僵尸是否与其他图元（主要是植物）发生碰撞
 *
 * @param other 要检测碰撞的其他图元
 * @param mode 碰撞检测模式（未使用）
 * @return 是否发生碰撞
 */
bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)

    // 仅当其他图元是植物类型、在同一行且横向距离小于30时，才认为发生碰撞
    return other->type() == Plant::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 30;
}

/**
 * @brief 返回图元类型
 *
 * @return 僵尸的自定义类型值
 */
int Zombie::type() const
{
    return Type;
}

/**
 * @brief 设置僵尸身体动画
 *
 * @param path 动画文件路径
 */
void Zombie::setMovie(QString path)
{
    // 释放旧动画资源
    if (movie)
        delete movie;

    // 创建并启动新动画
    movie = new QMovie(path);
    movie->start();
}

/**
 * @brief 设置僵尸头部动画
 *
 * @param path 头部动画文件路径
 */
void Zombie::setHead(QString path)
{
    // 释放旧头部动画资源
    if (head)
        delete head;

    // 创建并启动新头部动画
    head = new QMovie(path);
    head->start();
}
