#include "other.h"

/**
 * @brief Other类的构造函数
 *
 * 空实现，因为基类不需要特殊的初始化操作
 * 具体的初始化将在派生类中完成
 */
Other::Other() {}

/**
 * @brief 返回图元类型
 *
 * 重写QGraphicsItem::type()方法，返回Other类的自定义类型值
 * 用于在场景中识别Other类型的对象
 *
 * @return 自定义图元类型值(UserType + 3)
 */
int Other::type() const
{
    return Type;
}
