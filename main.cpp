#include <QApplication>
#include "mainwindow.h"

/**
 * @brief 程序主入口函数
 *
 * 创建并启动植物大战僵尸游戏应用程序，主要流程包括：
 * 1. 创建QApplication实例，管理应用程序的控制流和主要设置
 * 2. 创建主窗口并设置固定大小和窗口标题
 * 3. 显示主窗口并进入应用程序的事件循环
 *
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return 应用程序的退出代码
 */
int main(int argc, char *argv[])
{
    /**
     * @brief 创建QApplication实例
     *
     * QApplication管理GUI应用程序的控制流和主要设置。
     * 处理命令行参数，初始化应用程序资源。
     *
     * @param argc 命令行参数个数
     * @param argv 命令行参数数组
     */
    QApplication a(argc, argv);

    /**
     * @brief 创建主窗口实例
     *
     * MainWindow是游戏的主窗口，包含游戏场景、视图和所有游戏元素。
     * 采用Graphics View框架构建游戏界面。
     */
    MainWindow w;

    /**
     * @brief 设置窗口固定大小
     *
     * 将窗口大小固定为900x600像素，确保游戏界面显示比例正确。
     * 用户无法调整窗口大小，保持游戏体验的一致性。
     */
    w.setFixedSize(900, 600);

    /**
     * @brief 设置窗口标题
     *
     * 在窗口标题栏显示"植物大战僵尸"，标识应用程序。
     */
    w.setWindowTitle("植物大战僵尸");

    /**
     * @brief 显示主窗口
     *
     * 将主窗口显示在屏幕上，使其对用户可见。
     * 窗口部件在创建时默认是不可见的，需要调用show()来显示。
     */
    w.show();

    /**
     * @brief 进入应用程序事件循环
     *
     * 启动应用程序的事件循环，等待并处理用户输入、定时器事件等。
     * 当应用程序退出时（如关闭主窗口），exec()返回相应的退出代码。
     *
     * @return 应用程序的退出代码
     */
    return a.exec();
}
