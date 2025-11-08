#ifndef BLOCK_H
#define BLOCK_H

#include "other.h"
#include "plant.h"
#include "shop.h"
#include "shovel.h"
#include <QGraphicsSceneDragDropEvent>

/**
 * @brief 地图类，继承自Other基类
 *
 * 地图是游戏的主要交互区域，负责处理植物种植和铲除的拖放操作。
 * 管理游戏网格系统，将拖放位置转换为精确的网格坐标。
 */
class Map : public Other
{
public:
    /**
     * @brief 地图构造函数
     *
     * 初始化地图的拖放状态并启用拖放接受
     */
    Map();

    /**
     * @brief 返回地图的外接矩形
     *
     * @return 地图的外接矩形，定义地图的绘制和交互区域
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制地图
     *
     * 地图本身是透明的，主要用于处理交互事件
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 拖拽进入事件处理
     *
     * 当拖拽物体进入地图区域时触发，验证拖拽数据并更新状态
     *
     * @param event 拖拽进入事件
     */
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;

    /**
     * @brief 拖拽离开事件处理
     *
     * 当拖拽物体离开地图区域时触发，重置拖拽状态
     *
     * @param event 拖拽离开事件
     */
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;

    /**
     * @brief 拖放事件处理
     *
     * 当物体被放置在地图上时触发，处理植物种植或铲除操作
     *
     * @param event 拖放事件
     */
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    /**
     * @brief 拖拽悬停标志
     *
     * 表示当前是否有有效的拖拽物体悬停在地图上方
     * 用于视觉反馈（虽然当前实现中没有绘制反馈）
     */
    bool dragOver;
};

#endif // BLOCK_H
