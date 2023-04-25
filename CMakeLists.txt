# 设置版本号
cmake_minimum_required(VERSION 3.10)
#设置项目名称
project(fluid_engine_dev)
#可执行文件生成位置

# PROJECT_COURCE_DIR表示最外层目录，当前可表示在GAMES101_TO_OPENGL
# file 将所有后缀名为.cpp .h的文件都添加到srcs中
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/include/*.h)

# 可执行文件
add_executable(${PROJECT_NAME} ${srcs})

# 包含头文件目录
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
# 输出参数
message("PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")
# 设置语言标准
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

