#ifndef MESH_3D_HPP
#define MESH_3D_HPP
#include "shader.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int id;
  string type; // material
  string path; // store the path of the texture to compare with other textures.
               // Don't reload teexture multiple times
};

struct Material {
  glm::vec3 Diffuse;
  glm::vec3 Specular;
  glm::vec3 Ambient;
  float Shininess;
};

class Mesh {
private:
  unsigned int VBO, VAO, EBO;

  void setupMesh();

public:
  vector<Vertex> vertices;
  vector<Texture> textures;
  Material materials;
  vector<unsigned int> indices;

  Mesh(vector<Vertex> vertices, vector<Texture> textures,
       vector<unsigned int> indices, Material materials);
  void draw(Shader shader);
};
#endif