#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

//Assimp dependencies
#include <Importer.hpp>
#include <scene.h>
#include <mesh.h>
#include <postprocess.h>

#include <Vertex.h>
#include <Texture.h>

class Mesh
{
  public:
    bool loadSceneFromFiles(std::string fileName);
    void render();

  private:
    bool initTextures(const aiScene *pScene, const std::string fileName);
    bool initSubMesh(const int index, const aiMesh *pMesh);
    bool initFromScene(const aiScene *pScene, const std::string fileName);

    struct SubMesh
    {
        GLuint VB;
        GLuint IB; 
        unsigned int indexCount;
        unsigned int material;

        bool init(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices);
    };

    std::vector<SubMesh> mMeshes;
    std::vector<Texture *> mTextures;
};

#endif
