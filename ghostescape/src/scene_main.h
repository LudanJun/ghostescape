#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class SceneMain : public Scene
{
public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;
};

#endif // SCENE_MAIN_H