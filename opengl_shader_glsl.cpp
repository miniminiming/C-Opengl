#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils/Shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);


/**
 * 顶点数组对象：Vertex Array Object，VAO
 * 顶点缓冲对象：Vertex Buffer Object，VBO
 * 索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO
 * @return
 */
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

    //以此方式创建新对象？
    //这里要注意，当程序运行的时候，它是去它运行的目录下去找这个文件的，shit
    //怪不得一直报错,
//    Shader shader("shader/vertex_shader_one.glsl", "shader/fragment_shader_one.glsl");
    Shader shader("D:\\cl_workspace\\TestOpengl\\shader\\vertex_shader_one.glsl",
                  "D:\\cl_workspace\\TestOpengl\\shader\\fragment_shader_one.glsl");

    //矩形
    float vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = { // 注意索引从0开始!
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
    };


    unsigned int VBO;//顶点缓冲对象
    glGenBuffers(1, &VBO);//&符号应该是传引用对象的意思，不然会传值进去

    //设置索引数据
    unsigned int EBO;//索引缓冲对象
    glGenBuffers(1, &EBO);


    //创建一个VAO，看起来像是对上面的固定过程的封装，毕竟链接着色器程序，指定数据，都是一些固定操作
    //且VAO是必须的
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    //初始化代码，一般只运行一次
    //1.绑定VAP
    glBindVertexArray(VAO);
    //2.把顶点数组复制到缓冲中供OpenGl使用,GL_ARRAY_BUFFER这个是个特殊的东西
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //2.5  把索引数组复制到一个索引缓冲中，供opengl使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //3.设置顶点属性指针，第一个参数0，其实是Location
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    //循环绘制
    while (!glfwWindowShouldClose(window)) {//判断界面是否关闭，没关闭就循环绘制
        processInput(window);

        //同java
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();//必须先激活
        // 更新uniform颜色
        float timeValue = (float) glfwGetTime();
        float greenValue = (float) (sin(timeValue) / 2.0f + 0.5f);
        shader.setFloat("ourColor",0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAO);

//        glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        //双缓冲机制，前缓冲保存着最终输出的图像，后缓冲则进行绘制，绘制完成以后与前缓冲交换，就会立即显示
        //单缓冲会存在闪烁问题
        glfwSwapBuffers(window);//交换颜色缓冲
        glfwPollEvents();//检查有没有什么触发事件，鼠标键盘等，并调用相关的回调
    }

    //回收数据
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();//结束绘制
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