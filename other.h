#ifndef OTHER_H
#define OTHER_H

#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>

/**
 * @brief 其他游戏元素的基类
 *
 * Other类是除植物和僵尸外其他游戏元素的基类，
 * 商店Shop、地图Map、卡牌Card等。
 * 继承自QGraphicsItem，提供基本的图元类型识别功能。
 */
class Other : public QGraphicsItem
{
public:
    /**
     * @brief 自定义图元类型
     *
     * 用于QGraphicsItem::type()识别对象，
     * 值为UserType + 3，确保与植物(+1)和僵尸(+2)的类型不冲突
     */
    enum { Type = UserType + 3};

    /**
     * @brief 构造函数
     */
    Other();

    /**
     * @brief 返回图元类型
     *
     * 重写QGraphicsItem::type()方法，用于场景中识别该类型的对象
     * @return 自定义图元类型值
     */
    int type() const override;
};

#endif // OTHER_H
