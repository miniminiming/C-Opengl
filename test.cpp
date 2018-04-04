#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//矩阵工具库
#include "utils/glm/glm.hpp"
#include "utils/glm/gtc/matrix_transform.hpp"
#include "utils/glm/gtc/type_ptr.hpp"


int main() {
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
    return 0;
}
