<<<<<<< HEAD
# 植物大战僵尸（Qt/C++ 版）

一个使用 Qt Graphics View 框架实现的简化版《植物大战僵尸》示例项目，展示了 C++ 面向对象设计、图形项动画、拖放交互与碰撞检测等核心能力。

## 功能概览

- 植物系统：
  - `SunFlower`（向日葵）：产生阳光资源。
  - `Peashooter`（豌豆射手）：发射豌豆子弹。
  - `SnowPea`（寒冰射手）：发射减速子弹。
  - `Repeater`（双发射手）：一次发射两枚子弹。
  - `WallNut`（坚果墙）：高耐久防御单位。
  - `PotatoMine`（土豆雷）：延迟就绪后触发爆炸。
  - `CherryBomb`（樱桃炸弹）：范围爆炸伤害。
- 僵尸系统：
  - `BasicZombie`、`ConeZombie`、`BucketZombie`、`ScreenZombie`、`FootballZombie` 等，具有行走、攻击、死亡等状态机和不同耐久/速度。
- 其他元素：
  - `Shop`（商店）+ `Card`（卡牌）：拖放种植，卡牌具备冷却显示（变黑遮罩）。
  - `Shovel`（铲子）：拖放到地块以铲除植物。
  - `Map`（地图）：网格化坐标与拖放落点吸附。
  - `Mower`（割草机）：左侧防线的最后保护（示意）。
  - `Sun`（阳光资源）：资源单位。
- 交互与控制：
  - 将卡牌或铲子拖拽到地图地块完成种植/铲除。
  - 右上角 `Button`：暂停/继续游戏（同时控制背景音乐与计时器）。
- 动画与效果：
  - 使用 `QMovie` 播放 GIF 帧作为动画（植物、僵尸、爆炸、燃烧、僵尸头部等）。
  - `collidesWithItem` 与 `advance` 驱动的碰撞、伤害与状态切换。

## 界面预览

界面仿照原版布局：顶部商店与铲子、右上角暂停按钮、中部地图、左侧割草机。

![UI 预览](images/ui.png)

## 架构与技术要点

- Graphics View 架构：
  - `QGraphicsScene` 管理场景与图形项；`QGraphicsView` 负责可视化与事件转发。
  - 自定义项均继承 `QGraphicsItem`，重写 `boundingRect` 与 `paint` 完成绘制。
- 面向对象设计：
  - 基类：`Plant`、`Zombie`、`Other`，派生类按职能扩展行为。
  - 典型行为：`advance(int)` 作为帧驱动逻辑入口进行计时、移动、攻击、状态转换。
- 碰撞/逻辑：
  - 通过 `collidesWithItem` 与 `scene()->collidingItems()` 检测同一路线僵尸/植物交互。
  - `Peashooter` 根据装弹冷却与是否探测到僵尸决定发射 `Pea` 子弹。
  - `CherryBomb` 分两段动画：准备→爆炸，爆炸后对范围内僵尸造成伤害与燃烧动画。
- 资源管理：
  - 静态/动态图像、音频由 `resources.qrc`/`images.qrc` 统一打包；图标 `PVZ.ico`，音乐 `Grazy Dave.mp3`。
  - 多语言文件 `PVZ_zh_CN.ts`（可用于 Qt Linguist 翻译）。

## 项目结构

- 入口与主窗体：`main.cpp`、`mainwindow.h/.cpp`
- 植物：`plant.*`、`sunflower.*`、`peashooter.*`、`snowpea.*`、`repeater.*`、`wallnut.*`、`potatomine.*`、`cherrybomb.*`
- 子弹与资源：`pea.*`、`sun.*`
- 僵尸：`zombie.*`、`basiczombie.*`、`conezombie.*`、`bucketzombie.*`、`screenzombie.*`、`footballzombie.*`
- 地图与交互：`map.*`、`shop.*`、`card.*`、`shovel.*`、`mower.*`、`button.*`
- 其他：`other.*`、`images/`（图像资源）、`*.qrc`（资源）、`PVZ.ico`、`Grazy Dave.mp3`

## 构建与运行

本项目使用 CMake 管理，依赖 Qt（建议 Qt 5.15+ 或 Qt 6.x）。

- 环境准备：

  - 安装 Qt（含 `Qt Widgets` 模块与对应编译工具链）。
  - 安装 CMake 3.16+。
  - Windows 建议使用 Qt Creator 或 MSVC/MinGW 对应工具链。
- 使用 Qt Creator：

  - 打开 `CMakeLists.txt`，选择合适的 Kit（MSVC 或 MinGW）。
  - 配置、生成并构建，直接在 IDE 中运行。
- 使用命令行（示例）：

  ```bash
  # 替换为你的 Qt 安装路径（例如 Qt6: C:\\Qt\\6.6.0\\msvc2019_64\\lib\\cmake\\Qt6）
  cmake -S . -B build -D CMAKE_PREFIX_PATH="<Qt 安装路径>"
  cmake --build build --config Release
  # 可执行文件位于构建输出目录
  ```
- 资源打包：

  - 通过 `resources.qrc`/`images.qrc` 引用 `:/images/...` 路径，确保构建后资源可用。

## 操作说明

- 种植：从商店拖动植物卡牌到地图地块。
- 铲除：拖动铲子到地图地块移除植物。
- 暂停/继续：点击右上角按钮切换。

## 扩展指南

- 新增植物：
  - 继承 `Plant`，实现绘制与 `advance` 行为，必要时重写碰撞判定。
  - 在 `Shop`/`Card` 注册卡牌与冷却，并在地图坐标系内放置实例。
- 新增僵尸：
  - 继承 `Zombie`，定义状态机（行走/攻击/死亡等）、速度与动画资源。
  - 在僵尸生成逻辑中加入新类型生成策略。
- 新增资源/动画：
  - 将图片/GIF/音频加入 `images/` 或对应路径，并在 `*.qrc` 中注册。

## 已知注意事项

- 坐标换算：拖放到地图时需进行网格对齐（见 `Map::dropEvent`）。
- 动画性能：大量 GIF 动画可能影响性能，可按需优化帧率或切换精灵图。
- 构建 Kit：请确保 CMake 使用的 Qt 前缀路径与编译器匹配。

## 许可

GPL-3.0（GNU General Public License version 3.0）
=======
# PVZ-
面向对象程序设计C++报告
>>>>>>> fbead5ebecc56144020b6ba8b6fa79badb31ce85
