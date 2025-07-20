#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp> // 矢量计算库
#include <string>
// 如果没有识别保存 在CMakeLists.txt中保存一下就识别了

class Game
{
    glm::vec2 screen_size_ = glm::vec2(0); // 屏幕大小
    bool is_running_ = true;             // 游戏是否运行
    SDL_Window *window_ = nullptr;         // 窗口
    SDL_Renderer *renderer_ = nullptr;     // 渲染器
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
};