#include <Entity.h>

Entity::Entity(Mesh *mesh, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
{
    mMesh = mesh;
    mPos = pos;
    mRot = rot;
    mScl = scl;
}

Entity::Entity()
{

}

void Entity::render()
{
    if (mMesh == NULL)
    {
        std::cout << "This entity has no mesh!\n";
        return;
    }
    mMesh->render();
}

void Entity::updatePosition(glm::vec3 pos)
{
    mPos = pos;
}

void Entity::updateRotation(glm::vec3 rot)
{
    mRot = rot;
}

void Entity::updateScale(glm::vec3 scl)
{
    mScl = scl;
}
