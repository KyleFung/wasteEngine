#ifndef LOADEDMESH_H
#define LOADEDMESH_H

#include <string>
#include <iostream>

//Assimp dependencies
#include <Importer.hpp>
#include <scene.h>
#include <mesh.h>
#include <postprocess.h>

#include <Mesh.h>

class LoadedMesh: public Mesh
{
  public:
    bool loadSceneFromFiles(std::string fileName);
    virtual void render();

  private:
    bool initTextures(const aiScene *pScene, const std::string fileName);
    bool initSubMesh(const int index, const aiMesh *pMesh);
    bool initFromScene(const aiScene *pScene, const std::string fileName);
};

#endif
