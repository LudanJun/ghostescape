#include "game.h"

void Game::run()
{
    while (is_running_)
    {
        handleEvents();
        update(0.0f);
        render();
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

    if (Mix_OpenAudio(0, NULL))
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
            break;
        }
    }
}

void Game::update(float dt)
{
}

void Game::render()
{
}

void Game::clean()
{
}
