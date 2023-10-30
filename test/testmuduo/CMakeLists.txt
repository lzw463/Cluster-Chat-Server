cmake_minimum_required(VERSION 3.0)
project(main)


# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置头文件搜索路径
# include_directories()
# 配置库文件搜索路径
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

#设置可执行文件最终存储的位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 把.指定路径下的所有文件名放入变量名
# aux_source_directory(. SRC_LIST)


#表示生成可执行文件server，由SRC)_LIST变量所定义的源文件生成而来
add_executable(server ${SRC_LIST})
#表示server目标文件需要链接这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)