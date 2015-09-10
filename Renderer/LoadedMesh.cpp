#include <LoadedMesh.h>

LoadedMesh::LoadedMesh(const std::string fileName)
{
    loadSceneFromFiles(fileName);
}

bool LoadedMesh::loadSceneFromFiles(const std::string fileName)
{
    Assimp::Importer importer;

    const aiScene* pScene = importer.ReadFile(fileName, aiProcess_Triangulate
                                                        | aiProcess_GenSmoothNormals
                                                        | aiProcess_FlipUVs);
    if(pScene)
    {
        return initFromScene(pScene, fileName);
    }
    else
    {
        std::cout << "Could not open mesh " << fileName << "\n";
        return false;
    }
}

bool LoadedMesh::initFromScene(const aiScene *pScene, const std::string fileName)
{
    mMeshes.resize(pScene->mNumMeshes);
    mTextures.resize(pScene->mNumMaterials);

    for(int i = 0; i < mMeshes.size(); i++)
    {
        initSubMesh(i, pScene->mMeshes[i]);
    }
    initTextures(pScene, fileName);
}

bool LoadedMesh::initSubMesh(const int n, const aiMesh* pMesh)
{
    //Set the submesh's material index
    mMeshes[n].material = pMesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D zeroVector(0.0, 0.0, 0.0);

    //Collect all the vertices
    for(int i = 0; i < pMesh->mNumVertices; i++)
    {
        const aiVector3D *pPos = &(pMesh->mVertices[i]);
        const aiVector3D *pNor = pMesh->HasNormals() ? &(pMesh->mNormals[i]): &zeroVector;
        const aiVector3D *pTex = pMesh->HasTextureCoords(0) ? &(pMesh->mTextureCoords[0][i]): &zeroVector;

        Vertex iVert;
        iVert.pos = glm::vec3(pPos->x, pPos->y, pPos->z);
        iVert.nor = glm::vec3(pNor->x, pNor->y, pNor->z);
        iVert.tex = glm::vec3(pTex->x, pTex->y, pTex->z);
        vertices.push_back(iVert);
    }

    //Collect all the indices from faces
    for(int i = 0; i < pMesh->mNumFaces; i++)
    {
        const aiFace face = pMesh->mFaces[i];
        assert(face.mNumIndices == 3);
        indices.push_back(face.mIndices[0]); 
        indices.push_back(face.mIndices[1]); 
        indices.push_back(face.mIndices[2]); 
    }

    return mMeshes[n].init(vertices, indices);
}

bool LoadedMesh::initTextures(const aiScene *pScene, const std::string fileName)
{
    // Extract the directory part from the file name
    std::string::size_type slashIndex = fileName.find_last_of("/");
    std::string dir;
    bool ret = true;

    if (slashIndex == std::string::npos)
        dir = ".";
    else if (slashIndex == 0)
        dir = "/";
    else
        dir = fileName.substr(0, slashIndex);

    //Collect textures from all materials
    for(int i = 0; i < pScene->mNumMaterials; i++)
    {
        const aiMaterial *pMaterial = pScene->mMaterials[i]; 
        mTextures[i] = NULL;
        //Make sure this material has a diffuse map
        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
            {
                std::string fullPath = dir + "/" + path.data;
                mTextures[i] = new Texture(GL_TEXTURE_2D, fullPath);

                if(!mTextures[i]->load())
                {
                    std::cout << "Failed to load texture: " << fullPath << "\n"; 
                    delete mTextures[i];
                    mTextures[i] = NULL;
                    ret = false;
                }
            }
        }

        //Default to loading a tiled texture if fails
        if(!mTextures[i])
        {
            std::string defaultTex = "Assets/tile.png";
            mTextures[i] = new Texture(GL_TEXTURE_2D, defaultTex);
            if(!mTextures[i]->load())
            {
                std::cout << "Failed to load default texture.\n";
                delete mTextures[i];
                mTextures[i] = NULL;
                ret = false;
            }
        }
    }
    return ret;
}

void LoadedMesh::render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for(int i = 0; i < mMeshes.size(); i++)
    {
        //Set up vertex layout
        glBindBuffer(GL_ARRAY_BUFFER, mMeshes[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 12);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 24);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMeshes[i].IB);

        if(mTextures[mMeshes[i].material])
        {
            mTextures[mMeshes[i].material]->bind(GL_TEXTURE0);
        }
        glDrawElements(GL_TRIANGLES, mMeshes[i].indexCount, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
