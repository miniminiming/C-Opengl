cmake_minimum_required(VERSION 3.6)
project(TestOpengl)

set(CMAKE_CXX_STANDARD 11)

set(Util_Dir utils/)
set(Shader_Dir shader/)

#TestOpengl_SOURCE_DIR 这个变量是在指定项目名称为TestOpengl后自动生成的变量
#set(INC_DIR ${TestOpengl_SOURCE_DIR}/include)
#set(LINK_DIR ${TestOpengl_SOURCE_DIR}/lib)
#
#include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
#link_libraries(glfw3)#名字要跟lib的名字一样


set(SOURCE_FILES
        ${Shader_Dir}
        opengl_multi_light.cpp
        #        opengl_color_light_picture.cpp
        #        opengl_color_light.cpp
        #        opengl_matrix.cpp
        #        opengl_texture.cpp
        #        opengl_shader_glsl.cpp
        #        opengl_triangle.cpp
        #        opengl_first.cpp
        #        test.cpp
        ${Util_Dir}/glm
        ${Util_Dir}/glad.c
        ${Util_Dir}/Shader.cpp
        ${Util_Dir}/Shader.h
        ${Util_Dir}/stb_image.h
        ${Util_Dir}/stb_image.cpp utils/Camera.h)
add_executable(TestOpengl ${SOURCE_FILES})
target_link_libraries(TestOpengl glfw3)#使用库

