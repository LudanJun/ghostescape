#include "core/game.h"

// #include <SDL3/SDL.h>
// #include <SDL3_image/SDL_image.h>
// #include <SDL_mixer.h>
// #include <SDL3_ttf/SDL_ttf.h>
// #include <glm/glm.hpp> // 矢量计算库
int main(int, char **)
{
    auto &game = Game::GetInstance(); // 获取游戏实例
    game.init("幽灵逃生", 1280, 720); // 初始化游戏
    game.run();                       // 游戏主循环
    return 0;
}