#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp> // 矢量计算库
#include <string>
// 如果没有识别保存 在CMakeLists.txt中保存一下就识别了

class Scene; // 声明一下 不去引入因为在Scene以及它的上层object里面需要引入game.h头文件的
class Game
{
    glm::vec2 screen_size_ = glm::vec2(0); // 屏幕大小
    bool is_running_ = true;               // 游戏是否运行
    Scene *current_scene_ = nullptr;       // 当前场景

    Uint64 FPS_ = 60;        // 每秒帧数
    Uint64 frame_delay_ = 0; // 每帧间隔时间 单位纳秒ns
    float dt_ = 0.0f;        // 上一帧到当前帧的时间间隔

    SDL_Window *window_ = nullptr;     // 窗口
    SDL_Renderer *renderer_ = nullptr; // 渲染器
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
    void run();                                          // 运行游戏, 执行游戏主循环
    void init(std::string title, int width, int height); // 初始化游戏
    void handleEvents();                                 // 处理事件
    void update(float dt);                               // 更新游戏状态
    void render();                                       // 渲染游戏画面
    void clean();                                        // 清理游戏资源

    // getters and setters
    glm::vec2 getScreenSize() const { return screen_size_; } // 获取屏幕大小

    // 工具函数
    void drawGrid(const glm::vec2 &top_left, glm::vec2 bottom_right, float grid_width, SDL_FColor fcolor); // 绘制网格
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right,float boundary_width, SDL_FColor fcolor);        // 绘制边界
};

#endif // GAME_H