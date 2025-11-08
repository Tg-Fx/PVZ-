#ifndef BUTTON_H
#define BUTTON_H

#include <QTimer>
#include <QMediaPlayer>
// #include <QAudioOutput>
#include "other.h"

/**
 * @brief 控制按钮类，继承自Other基类
 *
 * 控制按钮是游戏中的暂停/继续按钮，位于界面右上角。
 * 用于控制游戏的暂停和继续，同时管理背景音乐的播放状态。
 */
class Button : public Other
{
public:
    /**
     * @brief 按钮构造函数
     *
     * 初始化按钮关联的媒体播放器、音频输出和计时器
     *
     * @param player 媒体播放器对象，用于控制背景音乐
     * @param audio 音频输出对象，用于音频输出配置
     * @param t 游戏主计时器对象，用于控制游戏逻辑更新
     */
    // Button(QMediaPlayer *player, QAudioOutput *audio, QTimer *t);
    Button(QMediaPlayer *player, QTimer *t);

    /**
     * @brief 返回按钮的外接矩形
     *
     * @return 按钮的外接矩形，用于绘制和碰撞检测
     */
    QRectF boundingRect() const override;

    /**
     * @brief 绘制按钮
     *
     * 绘制按钮背景和根据计时器状态显示"PAUSE"或"CONTINUE"文本
     *
     * @param painter 绘图设备
     * @param option 样式选项（未使用）
     * @param widget 控件（未使用）
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief 鼠标按下事件处理
     *
     * 处理按钮点击，切换游戏暂停/继续状态和背景音乐播放
     *
     * @param event 鼠标按下事件
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /**
     * @brief 媒体播放器
     *
     * 控制游戏背景音乐的播放和停止
     */
    QMediaPlayer *mediaPlayer;

    // /**
    //  * @brief 音频输出
    //  *
    //  * 配置和管理音频输出设备
    //  */
    // QAudioOutput *audioOutput;

    /**
     * @brief 游戏主计时器
     *
     * 控制游戏逻辑的更新频率，暂停/继续操作的核心对象
     */
    QTimer *timer;
};

#endif // BUTTON_H
