cmake_minimum_required(VERSION 3.0)
project(main)


# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置最终的可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

# 指定搜索CMakeLists的子目录
add_subdirectory(src)

#{"msgid":1,"id":2,"password":"123456"}
#msgid: id: name: to: msg:
#{"msgid":5,"id":1,"from":"lizhiwei","to":2,"msg":"hello!"}
#{"msgid":3,"name":"nihao","password":"123456"}