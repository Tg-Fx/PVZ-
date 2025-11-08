#ifndef CARD_H
#define CARD_H

#include "other.h"

/**
 * @brief 植物卡片类，继承自Other基类
 *
 * 卡片类代表商店中的植物选择卡片，负责：
 * 1. 显示植物图标、名称和阳光成本
 * 2. 处理卡片的冷却时间
 * 3. 实现拖放功能，允许玩家将植物放置到游戏场景中
 */
class Card : public Other
{
public:
    /**
     * @brief 冷却计数器
     *
     * 记录卡片当前的冷却状态，当counter < cool[map[text]]时，
     * 卡片处于冷却状态，不能使用
     */
    int counter;

    /**
     * @brief 卡片对应的植物名称
     *
     * 用于标识卡片代表的植物类型，如"SunFlower"、"Peashooter"等
     */
    QString text;

    /**
     * @brief 卡片构造函数
     *
     * @param s 植物名称
     */
    Card(QString s);

    /**
     * @brief 植物名称到索引的映射
     *
     * 将植物名称映射到对应的索引，用于在其他静态数组中查找相关信息
     */
    const static QMap<QString, int> map;

    /**
     * @brief 所有可用植物的名称数组
     *
     * 存储所有可用植物的名称，用于创建卡片
     */
    const static QVector<QString> name;

    /**
     * @brief 各植物的阳光成本数组
     *
     * 存储各植物的阳光成本，索引与name数组对应
     */
    const static QVector<int> cost;

    /**
     * @brief 各植物的冷却时间数组
     *
     * 存储各植物的冷却时间（以帧为单位），索引与name数组对应
     */
    const static QVector<int> cool;

    /**
     * @brief 返回卡片的外接矩形
     *
     * @return 卡片的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制卡片
     *
     * 绘制卡片背景、植物图标、阳光成本和冷却遮罩
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 处理卡片的游戏逻辑
     *
     * 更新卡片的冷却状态
     *
     * @param phase 更新阶段，0为准备阶段，1为执行阶段
     */
    void advance(int phase) override;

    /**
     * @brief 处理鼠标按下事件
     *
     * 检查卡片是否可用（冷却完成且有足够阳光）
     *
     * @param event 鼠标事件
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief 处理鼠标移动事件
     *
     * 实现卡片的拖放功能
     *
     * @param event 鼠标事件
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief 处理鼠标释放事件
     *
     * 重置鼠标指针
     *
     * @param event 鼠标事件
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    // 暂无私有成员
};

#endif // CARD_H
