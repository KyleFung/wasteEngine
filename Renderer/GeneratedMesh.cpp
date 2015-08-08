#include <GeneratedMesh.h>

bool GeneratedMesh::loadMeshFromFunction(function3D functionPtr)
{
    if(functionPtr == NULL)
        return false;

    mFunction = functionPtr;
    return generateMesh();
}

bool GeneratedMesh::generateMesh()
{
    std::vector<Vertex> heightMap;
    std::vector<unsigned int> indices;

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            Vertex vert;

            float x = j * 0.01f;
            float y = mFunction(x, y);
            float z = i * 0.01f;

            vert.pos = glm::vec3(x, y, z);
            vert.nor = glm::vec3(0.0f, 1.0f, 0.0f);
            vert.tex = glm::vec3(x, z, 0.0f);
            heightMap.push_back(vert);

            //Push the square to the top right of the vertex
            if (j != 99 && i != 99 && i != 0 && j != 0)
            {
                unsigned int vertIndex = i * 100 + j;
                indices.push_back(vertIndex + 101);
                indices.push_back(vertIndex + 1);
                indices.push_back(vertIndex);
                indices.push_back(vertIndex + 100);
                indices.push_back(vertIndex + 101);
                indices.push_back(vertIndex);
            }
        }
    }

    mMeshes.resize(1);
    mMeshes[0].init(heightMap, indices);
    mMeshes[0].material = 0;
    return true;
}

bool GeneratedMesh::loadTexture(std::string fileName)
{
    Texture *tex = new Texture(GL_TEXTURE_2D, fileName);
    if (!tex->load())
    {
        std::cout << "Failed to load texture!\n";
        return false;
    }

    mTextures.resize(1);
    mTextures[0] = tex;

    return true;
}

void GeneratedMesh::render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //Set up vertex layout
    glBindBuffer(GL_ARRAY_BUFFER, mMeshes[0].VB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 12);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 24);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMeshes[0].IB);

    mTextures[mMeshes[0].material]->bind(GL_TEXTURE0);

    glDrawElements(GL_TRIANGLES, mMeshes[0].indexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
