#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_OPENGL_CORE_PROFILE);

    //第三个参数是标题
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Fail to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //奇特的写法，本应是个函数，写出来却像个变量，连参数都不需要传了
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "File to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);//指定视口大小，跟java一样
    //设置窗口尺寸改变的回调，C++原来是直接把一个函数作为回调传进去
    //原来它们的函数名是可以直接使用的，也解释了上面的现象
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //循环绘制
    while (!glfwWindowShouldClose(window)) {//判断界面是否关闭，没关闭就循环绘制
        processInput(window);

        //双缓冲机制，前缓冲保存着最终输出的图像，后缓冲则进行绘制，绘制完成以后与前缓冲交换，就会立即显示
        //单缓冲会存在闪烁问题
        glfwSwapBuffers(window);//交换颜色缓冲
        glfwPollEvents();//检查有没有什么触发事件，鼠标键盘等，并调用相关的回调

        //同java
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();//绘制
    return 0;
}

//窗口尺寸改变的回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    //按下esc键的意思
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);//关闭窗户
    }
}