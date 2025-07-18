#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp> // 矢量计算库
// 如果没有识别保存 在CMakeLists.txt中保存一下就识别了

class Game
{
    // 私有构造函数
    Game() {}
    // 禁止拷贝构造函数与赋值运算符
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

public:
    static Game &GetInstance()
    {
        static Game instance;
        return instance;
    }
};