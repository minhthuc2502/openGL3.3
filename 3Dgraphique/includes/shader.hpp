#ifndef C_SHADER_HPP
#define C_SHADER_HPP
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

class Shader
{
private:
    unsigned int ID;
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    // Constructor for shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/active the shader
    void use();
    // set utilily uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif