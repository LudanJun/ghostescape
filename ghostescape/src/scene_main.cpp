#include "scene_main.h"

void SceneMain::init()
{
    world_size_ = game_.getScreenSize() * 3.0f;  // 设置世界大小为屏幕大小的3倍
    camera_position_ = glm::vec2(-100.0f, 0.0f); // 设置相机位置为(-100.0f, 0)
}

// 处理事件
void SceneMain::handleEvents(SDL_Event &event)
{
    // TODO: 处理事件
}

// 更新场景主函数
void SceneMain::update(float dt)
{
    // 将相机位置增加一个向量，向量为(10.0f, 10.0f)乘以时间间隔dt
    camera_position_ += glm::vec2(100.0f, 100.0f) * dt;
}

void SceneMain::render()
{
    // 渲染背景
    renderBackground(); //
}

// 清理场景
void SceneMain::clean()
{
    // 清理场景中的物体
}

// 渲染背景
void SceneMain::renderBackground()
{
    // TODO: 实现背景渲染
    // 渲染(窗口中的)坐标=世界坐标-摄像机坐标
    auto start = -camera_position_;            // 背景起始位置
    auto end = world_size_ - camera_position_; // 背景结束位置
    game_.drawGrid(start, end, 80.0f, {0.5, 0.5, 0.5, 1.0});

    game_.drawBoundary(start, end, 5.0f, {1.0, 1.0, 1.0, 1.0});
}
