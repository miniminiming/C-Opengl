//
// Created by dell on 2018/3/22.
//

#ifndef TESTOPENGL_SHADER_H
#define TESTOPENGL_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/detail/type_mat.hpp"
#include "glm/vec3.hpp"

class Shader {
public:
    //程序ID
    unsigned int ID;

    //构造器读取并构建着色器
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

    //使用程序
    void use();

    //工具函数
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setFloat(const std::string &name, float value1, float value2, float value3, float value4) const;

    void setVec3(const std::string &name, float d, float d1, float d2);

    void setMat4(const std::string &name, const glm::mat4 &mat);

    void setVec3(const std::string &name, glm::vec3 vec3) ;
};


#endif //TESTOPENGL_SHADER_H
