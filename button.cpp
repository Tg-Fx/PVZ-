#include "button.h"

/**
 * @brief 按钮构造函数
 *
 * 初始化按钮关联的媒体播放器、音频输出和计时器引用
 * 配置媒体播放器的音频输出
 *
 * @param player 媒体播放器对象，用于控制背景音乐
 * @param audio 音频输出对象，用于音频输出配置
 * @param t 游戏主计时器对象，用于控制游戏逻辑更新
 */
Button::Button(QMediaPlayer *player, QTimer *t)
{
    // 保存媒体播放器对象引用
    mediaPlayer = player;

    // // 保存音频输出对象引用
    // audioOutput = audio;

    // 保存计时器对象引用
    timer = t;

    // 配置媒体播放器的音频输出
    // mediaPlayer->setAudioOutput(audioOutput);
}

/**
 * @brief 返回按钮的外接矩形
 *
 * 定义按钮在场景中的绘制范围和点击区域
 *
 * @return 按钮的外接矩形
 */
QRectF Button::boundingRect() const
{
    // 返回按钮的外接矩形，宽160像素，高40像素
    return QRectF(-80, -20, 160, 40);
}

/**
 * @brief 绘制按钮
 *
 * 绘制按钮背景图像，并根据计时器状态显示相应的文本：
 * - 计时器运行中：显示"PAUSE"
 * - 计时器停止：显示"CONTINUE"
 *
 * @param painter 绘图设备
 * @param option 样式选项（未使用）
 * @param widget 控件（未使用）
 */
void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 标记未使用的参数，避免编译警告
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 绘制按钮背景图像
    painter->drawPixmap(QRect(-80, -20, 160, 40), QPixmap(":/images/Button.png"));

    // 设置文本颜色为绿色
    painter->setPen(Qt::green);
    // 设置字体：Calibri，18点，粗体，斜体
    QFont font("Calibri", 18, QFont::Bold, true);
    painter->setFont(font);

    // 根据计时器状态显示不同的文本
    if (timer->isActive())
        // 计时器运行中，显示"PAUSE"（暂停）
        painter->drawText(boundingRect(), Qt::AlignCenter, "PAUSE");
    else
        // 计时器停止，显示"CONTINUE"（继续）
        painter->drawText(boundingRect(), Qt::AlignCenter, "CONTINUE");
}

/**
 * @brief 鼠标按下事件处理
 *
 * 处理左键点击事件，切换游戏状态：
 * - 如果游戏正在运行，暂停游戏并停止背景音乐
 * - 如果游戏已暂停，继续游戏并播放背景音乐
 * 使用Qt6的QMediaPlayer替代已弃用的QSound类
 *
 * @param event 鼠标按下事件
 */
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 检查是否为左键点击
    if (event->button() == Qt::LeftButton)
    {
        // 检查计时器是否正在运行
        if (timer->isActive())
        {
            // 游戏正在运行：暂停游戏
            // 停止背景音乐（使用QMediaPlayer）
            mediaPlayer->stop();
            // 停止游戏计时器
            timer->stop();
        }
        else
        {
            // 游戏已暂停：继续游戏
            // 播放背景音乐（使用QMediaPlayer）
            mediaPlayer->play();
            // 启动游戏计时器
            timer->start();
        }
    }
    // 更新按钮显示，切换文本内容
    update();
}
