#ifndef MODEL_3D_HPP
#define MODEL_3D_HPP
#include "mesh.hpp"
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/scene.h>       // Output data structure
#include <string>

class Model {
private:
  vector<Texture> textures_loaded;
  vector<Mesh> meshes;
  string directory;

  void loadModel(string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                       string typeName);
  Material loadMaterial(aiMaterial *mat);

public:
  Model(char *path) { loadModel(path); }
  void draw(Shader shader);
};
#endif