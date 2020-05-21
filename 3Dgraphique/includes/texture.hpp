#ifndef TEXTURE_3D_HPP
#define TEXTURE_3D_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include "stb_image.h"
#include "window.hpp"

class texture
{
private:
    unsigned int mtexture;
    unsigned char* data;
    int prefixGLTexture;
    void uploadData(const std::string path, window mwindow);
    void freeData();
public:    
    texture(): mtexture(0), data(NULL), prefixGLTexture(0) {};
    ~texture() {};
    void initialize(const std::string path, int size, const window mwindow);
    void bind(GLenum unit);
};

#endif