#ifndef MESH_H
#define MESH_H

#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include <Vertex.h>
#include <Texture.h>

class Mesh
{
  public:
    virtual void render() = 0;

    struct SubMesh
    {
        GLuint VB;
        GLuint IB; 
        unsigned int indexCount;
        unsigned int material;

        bool init(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices);
    };

  protected:
    std::vector<SubMesh> mMeshes;
    std::vector<Texture *> mTextures;
};

#endif
