//
// Created by dell on 2018/3/22.
//

#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    //1.从文件路径中获取顶点/片段着色器
    //这四个是定义啊
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // 保证ifstream 对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        //读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //关闭
        vShaderFile.close();
        fShaderFile.close();
        //把数据流的字符放到String中
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::fILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    //最后取出来的着色器数据
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    //2.编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    //把着色器源码附加到着色器对象上，然后编译它
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    //检测是否编译成功
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::cOMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    //把着色器源码附加到着色器对象上，然后编译它
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    //检测是否编译成功
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::cOMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value1, float value2, float value3, float value4) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setVec3(const std::string &name, float d, float d1, float d2) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), d, d1, d2);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const std::string &name, glm::vec3 vec3) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec3.x, vec3.y, vec3.z);
}
