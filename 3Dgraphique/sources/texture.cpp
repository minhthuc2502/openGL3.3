#include "texture.hpp"

void texture::uploadData(const std::string path, window mwindow)
{
    int nrChannels;
    int width = (int)mwindow.getWidth();
    int height = (int)mwindow.getHeight();
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (path.compare(path.length() - 3, 3, "png") != 0)
    {
        if (data)
        {
            glTexImage2D(prefixGLTexture, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(prefixGLTexture);
        }
        else
        {
            throw std::runtime_error("Failed to load texture");
        }
    }
    else
    {
        if (data)
        {
            glTexImage2D(prefixGLTexture, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(prefixGLTexture);
        }
        else
        {
            throw std::runtime_error("Failed to load texture");
        }
    }
}

void texture::initialize(const std::string path, int size, window mwindow)
{
    if (size == 2)
    {
        prefixGLTexture = GL_TEXTURE_2D;
    }
    else if(size == 3)
    {   
        prefixGLTexture = GL_TEXTURE_3D;
        glTexParameteri(prefixGLTexture, GL_TEXTURE_WRAP_R, GL_REPEAT);
    }
    // Generate texture
    glGenTextures(1, &mtexture);
    glBindTexture(prefixGLTexture, mtexture);
    // Set the texture wrapping/ filtering options
    glTexParameteri(prefixGLTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(prefixGLTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(prefixGLTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(prefixGLTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // rotate load in data
    stbi_set_flip_vertically_on_load(true); 
    // upload data to build texture
    uploadData(path, mwindow);
    // free data
    freeData();
}

void texture::bind(GLenum unit)
{
    // Load image generate texture
    glActiveTexture(unit);
    glBindTexture(prefixGLTexture, mtexture);
}

void texture::freeData()
{
    // free data
    stbi_image_free(data);
}
