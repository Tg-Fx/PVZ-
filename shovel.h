#ifndef SHOVEL_H
#define SHOVEL_H

#include "other.h"
#include "plant.h"

/**
 * @brief 铲子类，继承自Other基类
 *
 * 铲子是游戏中的工具，用于移除已种植的植物。
 * 支持拖放操作，玩家可以拖动铲子到地图上的植物位置进行铲除。
 */
class Shovel : public Other
{
public:
    /**
     * @brief 铲子构造函数
     *
     * 初始化铲子对象
     */
    Shovel();

    /**
     * @brief 返回铲子的外接矩形
     *
     * @return 铲子的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制铲子
     *
     * 绘制铲子的背景和图标
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 鼠标按下事件处理
     *
     * 设置鼠标光标为箭头形状
     *
     * @param event 鼠标按下事件
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief 鼠标移动事件处理
     *
     * 实现铲子的拖拽功能，创建拖拽操作
     *
     * @param event 鼠标移动事件
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief 鼠标释放事件处理
     *
     * 恢复鼠标光标为箭头形状
     *
     * @param event 鼠标释放事件
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief 移除植物
     *
     * 在指定位置查找并移除植物
     *
     * @param pos 要移除植物的位置
     */
    void removePlant(QPointF pos);
};

#endif // SHOVEL_H
