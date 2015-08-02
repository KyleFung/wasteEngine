#include <Mesh.h>

bool Mesh::SubMesh::init(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices)
{
    indexCount = indices.size();

    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    if(glGetError() != GL_NO_ERROR)
        return false;

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    if(glGetError() != GL_NO_ERROR)
        return false;

    return true;
}
