#include "game.h"
#include "../scene_main.h"

void Game::run()
{
    while (is_running_)
    {
        // auto start = SDL_GetTicks();//精度是毫秒
        auto start = SDL_GetTicksNS(); // 精度是纳秒
        handleEvents();
        update(dt_);
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start; // elapsed流逝值
        if (elapsed < frame_delay_)
        {
            SDL_DelayNS(frame_delay_ - elapsed);
            dt_ = frame_delay_ / 1.0e9;
        }
        else
        {
            dt_ = elapsed / 1.0e9;
            SDL_Log("帧率太低，卡顿了");
        }
        // SDL_Log("FPS: %f", 1.0 / dt_);
    }
}

void Game::init(std::string title, int width, int height)
{
    screen_size_ = {width, height};
    // SDL3初始化
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_初始化失败: %s\n", SDL_GetError());
    }
    // 不需要进行SDL_image初始化
    // SDL3_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }

    if (!Mix_OpenAudio(0, NULL))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer打开音频失败: %s\n", SDL_GetError());
    }
    Mix_AllocateChannels(16);            // 分配16个音频通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);  // 设置 音效音量

    /// SDL3_TTF初始化
    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF初始化失败: %s\n", SDL_GetError());
    }

    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "创建窗口与渲染器失败: %s\n", SDL_GetError());
    }
    // SDL3设置窗口逻辑分辨率 内部也能相应的放大缩小
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 计算帧延迟 1000000000 = 1.0e9 科学计数法
    frame_delay_ = 1.0e9 / FPS_; // 1秒 = 1000000000纳秒，FPS为60，则帧延迟为16.666666666666668纳秒

    // 创建场景 要记得在clean中清理
    current_scene_ = new SceneMain();
    current_scene_->init(); // 初始化场景
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) // 根据事件类型进行判断
        {
        case SDL_EVENT_QUIT:     // 退出事件
            is_running_ = false; // 设置为false退出循环
            break;
        default:
            current_scene_->handleEvents(event); // 处理事件
        }
    }
}

void Game::update(float dt)
{
    current_scene_->update(dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // 设置渲染器颜色
    SDL_RenderClear(renderer_);                      // 清空渲染器
    current_scene_->render();                        // 渲染场景
    SDL_RenderPresent(renderer_);                    // 显示渲染器
}

void Game::clean()
{
    if (current_scene_)
    {
        current_scene_->clean();
        delete current_scene_;
    }
    /// 释放渲染器和窗口
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
    }
    // 退出Mix
    Mix_CloseAudio();
    Mix_Quit();
    // 退出TTF
    TTF_Quit();
    // 退出SDL
    SDL_Quit();
}
