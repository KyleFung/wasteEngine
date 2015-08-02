#ifndef GENERATEDMESH_H
#define GENERATEDMESH_H

#include <string>
#include <iostream>

#include <Mesh.h>

class GeneratedMesh: public Mesh
{
  public:
    typedef float (*function3D)(float x, float y);

    bool loadMeshFromFunction(function3D functionPtr);
    bool generateMesh();

    bool loadTexture(std::string fileName);

    virtual void render();

  private:
    function3D mFunction;
};

#endif
