#ifndef SHOP_H
#define SHOP_H

#include "plant.h"
#include "other.h"
#include "card.h"
#include "sun.h"
#include "sunflower.h"
#include "peashooter.h"
#include "cherrybomb.h"
#include "wallnut.h"
#include "snowpea.h"
#include "potatomine.h"
#include "repeater.h"
#include "basiczombie.h"

/**
 * @brief 商店类，继承自Other基类
 *
 * 商店是游戏界面顶部的植物卡片栏，负责：
 * 1. 显示和管理所有可用的植物卡片
 * 2. 存储和显示玩家当前拥有的阳光数量
 * 3. 定期在场景中生成自然阳光
 * 4. 处理植物的购买和放置逻辑
 */
class Shop : public Other
{
public:
    /**
     * @brief 玩家当前拥有的阳光数量
     *
     * 公开成员变量，允许其他类（如Sun）直接修改
     */
    int sun;

    /**
     * @brief 商店构造函数
     *
     * 初始化商店，设置初始阳光数量，创建所有植物卡片
     */
    Shop();

    /**
     * @brief 返回商店的外接矩形
     *
     * @return 商店的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制商店
     *
     * 绘制商店背景和当前阳光数量
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 处理商店的游戏逻辑
     *
     * 定期在场景中生成自然阳光
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

    /**
     * @brief 在指定位置添加指定类型的植物
     *
     * 检查位置是否已有植物，扣除相应阳光，创建并添加植物到场景
     *
     * @param s 植物类型名称
     * @param pos 要放置植物的位置
     */
    void addPlant(QString s, QPointF pos);

private:
    /**
     * @brief 计数器，用于控制自然阳光的生成频率
     */
    int counter;

    /**
     * @brief 生成自然阳光的时间间隔
     */
    int time;
};

#endif // SHOP_H
