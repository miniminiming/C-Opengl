#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils/Shader.h"
#include "utils/stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void loadTexture(unsigned int * texture,const char * path);

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
    GLFWwindow *window = glfwCreateWindow(600, 600, "LearnOpengl", NULL, NULL);
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

    unsigned int texture1, texture2;
    const char *path1 = "D:\\cl_workspace\\TestOpengl\\resource\\girl.jpg";
    const char *path2 = "D:\\cl_workspace\\TestOpengl\\resource\\awesomeface.jpg";
    //两个都要传递引用，这样函数更改的值才是上面的值
    loadTexture(&texture1,path1);
    loadTexture(&texture2,path2);

   /* glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);//GL_TEXTURE_2D同样，它也是一个目标
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载纹理，第三个参数是颜色通道的个数
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    //图片
    unsigned char *data = stbi_load(path1, &width,
                                    &height, &nrChannels, 0);

    //第二个参数为多级渐远纹理的级别，0为基本级别，第三个参数为指定纹理存储为何种格式
    //第六个总是设置为0，第七第八定义源图的格式和数据类型
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    //释放图像内存
    stbi_image_free(data);*/

    //加载texture2
   /* glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);//GL_TEXTURE_2D同样，它也是一个目标
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //图片
    data = stbi_load(path2, &width,
                     &height, &nrChannels, 0);

    //第二个参数为多级渐远纹理的级别，0为基本级别，第三个参数为指定纹理存储为何种格式
    //第六个总是设置为0，第七第八定义源图的格式和数据类型
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    //释放图像内存
    stbi_image_free(data);*/


    glViewport(0, 0, 600, 600);//指定视口大小，跟java一样
    //设置窗口尺寸改变的回调，C++原来是直接把一个函数作为回调传进去
    //原来它们的函数名是可以直接使用的，也解释了上面的现象
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader("D:\\cl_workspace\\TestOpengl\\shader\\vertex_shader_two.glsl",
                  "D:\\cl_workspace\\TestOpengl\\shader\\fragment_shader_two.glsl");

    //矩形
    float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 左上
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

    //设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    //设置颜色属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //设置纹理属性指针，第一个参数2，其实是Location，第三个参数是offset
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader.use();//必须先激活
    //关键的一步，把纹理单元设置进去，因为是uniform格式的，所以可以直接这么设置进去
//    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
    shader.setInt("texture1", 0);//我记得这两个是等价的嘛，0对应GL_TEXTURE0
    shader.setInt("texture2", 1);
    //循环绘制
    while (!glfwWindowShouldClose(window)) {//判断界面是否关闭，没关闭就循环绘制
        processInput(window);

        //同java
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);

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
//*代表引用传递，传参数时要用&符号，而取*里的值则需要*p
void loadTexture(unsigned int* texture,const char* path){
    glGenTextures(1, texture);
//    对*p赋值，从而改变p所指的地址上说保存的值
    //*textrue就能表示这个内存地址上表示的值
    glBindTexture(GL_TEXTURE_2D, *texture);//GL_TEXTURE_2D同样，它也是一个目标
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载纹理，第三个参数是颜色通道的个数
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    //图片
    unsigned char *data = stbi_load(path, &width,
                                    &height, &nrChannels, 0);

    //第二个参数为多级渐远纹理的级别，0为基本级别，第三个参数为指定纹理存储为何种格式
    //第六个总是设置为0，第七第八定义源图的格式和数据类型
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    //释放图像内存
    stbi_image_free(data);
}