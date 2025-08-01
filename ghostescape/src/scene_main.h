#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class SceneMain : public Scene
{
    glm::vec2 world_size_ = glm::vec2(0); // 世界大小 设定为3倍屏幕区域大小

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override; 
    virtual void clean() override;

private:
    void renderBackground(); // 绘制背景图片
};

#endif // SCENE_MAIN_H