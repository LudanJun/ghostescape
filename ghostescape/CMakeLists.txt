# 标题
cmake_minimum_required(VERSION 3.10.0)
project(SDLShooter VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 自动查找头文件目录（修正版）
file(GLOB_RECURSE SDL3_MIXER_HEADER "/opt/homebrew/Cellar/sdl3_mixer/include/SDL_mixer.h")
if(NOT SDL3_MIXER_HEADER)
    message(FATAL_ERROR "SDL3_mixer 头文件未找到！请检查 SDL3_mixer 是否正确安装。")
endif()
get_filename_component(SDL3_MIXER_INCLUDE_DIR ${SDL3_MIXER_HEADER} DIRECTORY)

# 自动查找库文件目录
file(GLOB_RECURSE SDL3_MIXER_LIB_FILE "/opt/homebrew/Cellar/sdl3_mixer/lib/libSDL3_mixer.dylib")
if(NOT SDL3_MIXER_LIB_FILE)
    message(FATAL_ERROR "SDL3_mixer 库文件未找到！请检查 SDL3_mixer 是否正确安装。")
endif()
get_filename_component(SDL3_MIXER_LIB_DIR ${SDL3_MIXER_LIB_FILE} DIRECTORY)

# 打印找到的路径（用于调试）
message(STATUS "Found SDL3_mixer include dir: ${SDL3_MIXER_INCLUDE_DIR}")
message(STATUS "Found SDL3_mixer lib dir: ${SDL3_MIXER_LIB_DIR}")

# SDL3_mixer 库文件名
set(SDL3_MIXER_LIB "SDL3_mixer")

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
# find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm REQUIRED)

# 添加可执行文件
add_executable(${TARGET} src/main.cpp)
# 链接库（包含手动配置的 SDL3_mixer）
target_include_directories(${TARGET} PRIVATE ${SDL3_MIXER_INCLUDE_DIR})  # 添加头文件目录
target_link_directories(${TARGET} PRIVATE ${SDL3_MIXER_LIB_DIR})        # 添加库目录
# 链接库
target_link_libraries(${TARGET}
                        ${SDL3_LIBRARIES}
                        SDL3_image::SDL3_image
                        # SDL3_mixer::SDL3_mixer
                        ${SDL3_MIXER_LIB}           # SDL3_mixer 库（手动指定）
                        SDL3_ttf::SDL3_ttf
                        glm::glm
                        )