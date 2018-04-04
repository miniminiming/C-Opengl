#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils/Shader.h"
//图片工具库
#include "utils/stb_image.h"

//矩阵工具库
#include "utils/glm/glm.hpp"
#include "utils/glm/gtc/matrix_transform.hpp"
#include "utils/glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void loadTexture(unsigned int *texture, const char *path);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);//相机位置
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);//面对的方向,以这个为尺度更改观看的，其实就是单位速度
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);//头顶的方向

float deltaTime = 0.0f; //当前帧与上一帧的时间差
float lastFrameTime = 0.0f;//上一帧的时间

float lastX = 300;
float lastY = 300;

float yaw;
float pitch;

float fov = 45.0f;//视野比例

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
    //使窗口隐藏光标并且捕捉它
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //使用回调
    glfwSetCursorPosCallback(window, mouse_callback);


    unsigned int texture1, texture2;
    const char *path1 = "D:\\cl_workspace\\TestOpengl\\resource\\girl.jpg";
    const char *path2 = "D:\\cl_workspace\\TestOpengl\\resource\\awesomeface.jpg";
    //两个都要传递引用，这样函数更改的值才是上面的值
    loadTexture(&texture1, path1);
    loadTexture(&texture2, path2);

    glViewport(0, 0, 600, 600);//指定视口大小，跟java一样
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);



//    Shader shader("D:\\cl_workspace\\TestOpengl\\shader\\vertex_shader_two.glsl",
//                  "D:\\cl_workspace\\TestOpengl\\shader\\fragment_shader_two.glsl");
    Shader shader("D:\\cl_workspace\\TestOpengl\\shader\\vertex_shader_three.glsl",
                  "D:\\cl_workspace\\TestOpengl\\shader\\fragment_shader_three.glsl");

    /*//矩形
    float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 左上
    };*/

    //立方体
    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    //设置颜色属性指针
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
    //设置纹理属性指针，第一个参数2，其实是Location，第三个参数是offset
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //平移的例子
//    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
//    glm::mat4 trans;
//    trans = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
//    vec = trans * vec;

    //生成一个旋转并且缩放的矩阵
//    glm::mat4 trans;
//    //radians是把90度转化为弧度
//    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//沿某个向量转90度
//    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    //设置矩阵
    /*glm::mat4 model;
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;//创建投影矩阵，第二个值应该为宽高比
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    shader.use();//必须先激活
    //再次确认一下，设置值，必须在链接编译程序以后才能进行
//    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    //分别设置model,view,projection四个矩阵的值
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));*/

    //弄多个立方体
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };


    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
    shader.setInt("texture1", 0);//我记得这两个是等价的嘛，0对应GL_TEXTURE0
    shader.setInt("texture2", 1);
    //循环绘制
    while (!glfwWindowShouldClose(window)) {//判断界面是否关闭，没关闭就循环绘制
        processInput(window);

        //记录deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;


        //同java
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//如果开启了深度测试，这里就要把GL_DEPTH_BUFFER_BIT也清空

        //让纹理转起来
        //生成一个不断旋转并且平移的矩阵
//        glm::mat4 trans;
//        float val = float(glfwGetTime());
//        trans = glm::translate(trans, glm::vec3(val / (20.0f), val / (20.0f), 0.0));
//        trans = glm::rotate(trans, val, glm::vec3(0.0, 0.0, 1.0));//沿某个向量转90度
//        //将值设置下去
//        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        //开启深度测试
        glEnable(GL_DEPTH_TEST);

        float radius = 5.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        glm::mat4 view;
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        //所以说，这个lookat也就是创建一个视角矩阵，只是它更加形象
        //第一个参数为摄像机位置，第二个为看的点的位置，目前设置的原点，第三个为头顶方向
        //这样我们就是在旋转摄像机的位置，以自身旋转的方式来
//        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //相机始终看着自己面前一个单位距离的位置
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection;//创建投影矩阵，第二个值应该为宽高比
        projection = glm::perspective(glm::radians(fov), 1.0f, 0.1f, 100.0f);

        shader.use();
        int modelLoc = glGetUniformLocation(shader.ID, "model");
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);

//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        for (int i = 0; i < 10; i++) {//平移到不同的位置 ，绘制多个立方体
            //让立方体不断旋转
            //这里我让十个立方体都先自转再平移，就需要用两个矩阵，一个自转，一个平移
            //然后用平移的后乘旋转的矩阵，印证了之前书里的一个说法，不能用同一个矩阵先自转，再平移达到这个效果
            //因为前后影响，生成的结果必然是先平移，再沿某个向量旋转
            glm::mat4 model1;
            model1 = glm::rotate(model1, (float) glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            model = model * model1;
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
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
    //帧间隔长，就让它移动的多一些，这样能间接保证速度
    float cameraSpeed = 2.5f * deltaTime;
    //按下esc键的意思
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);//关闭窗户
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //glm::normalize(glm::cross(cameraFront, cameraUp))这个求的是标准化的右向量
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

//*代表引用传递，传参数时要用&符号，而取*里的值则需要*p
void loadTexture(unsigned int *texture, const char *path) {
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

bool firstMouse = true;

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
//
    std::cout << "xpos:" << xpos << "   ypos:" << ypos << std::endl;
    if (firstMouse) // 这个bool变量初始时是设定为true的
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
//        return;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;


    float sensitivity = 0.05f;//灵敏度
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    pitch = pitch > 89.0f ? 89.0f : pitch;
    pitch = pitch < -89.0f ? -89.0f : pitch;

    glm::vec3 front;
    //根据俯仰和偏航角度来算出此向量，也就是速度在三个维度的数值
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch))-1;
    cameraFront = glm::normalize(front);
}

//滚轮的回调
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f) {
        fov -= yoffset;
    }

    fov = fov <= 1.0f ? 1.0f : fov;
    fov = fov >= 45.0f ? 45.0f : fov;
}
