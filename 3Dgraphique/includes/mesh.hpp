#ifndef MESH_3D_HPP
#define MESH_3D_HPP
#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "shader.hpp"

using namespace std;
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    string type;        // material
    string path;        // store the path of the texture to compare with other textures. Don't reload teexture multiple times
};

class Mesh
{
private:
    unsigned int VBO, VAO, EBO;
    
    void setupMesh();
public:
    vector<Vertex> vertices;
    vector<Texture> textures;
    vector<unsigned int> indices;

    Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<unsigned int> indices);
    void draw(Shader shader);
};
#endif