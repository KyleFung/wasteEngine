#include <Entity.h>

Entity::Entity(Mesh *mesh, glm::vec3 pos, glm::vec3 rot)
{
    mMesh = mesh;
    mPos = pos;
    mRot = rot;
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
