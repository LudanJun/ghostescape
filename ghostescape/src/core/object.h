#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
/// @brief  游戏所有对象物体的基类
class Object
{
    // 这更方便
    // 直接创建这个引用的时候, 就不需要每次都调用Game::GetInstance()了
protected:                             // protected: 只能在当前类和子类中访问
    Game &game_ = Game::GetInstance(); // 获取游戏实例

public:
    Object() = default;
    virtual ~Object() = default; // 所有的类,不在构造函数和析构函数里面做任何事情

    virtual void init() {}                         // 需要初始化的事物,在init函数里面做
    virtual void handleEvents(SDL_Event &event) {} // 需要处理的事件
    virtual void update(float dt) {}               // 需要更新的内容
    virtual void render() {}                       // 需要渲染的内容
    virtual void clean() {}                        // 需要清理的资源, 在clean函数里面做
};

#endif // OBJECT_H