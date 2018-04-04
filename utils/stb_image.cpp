//
// Created by dell on 2018/3/26.
//
//通过定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，让其只包含相关的函数定义源码，
// 等于是将这个头文件变为一个 .cpp 文件了。现在只需要在你的程序中包含stb_image.h并编译就可以了。
//看来又是C++的特性
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"