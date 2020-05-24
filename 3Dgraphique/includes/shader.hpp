#ifndef C_SHADER_HPP
#define C_SHADER_HPP
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void set4MatrixFloat(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    unsigned int getId();
};

#endif