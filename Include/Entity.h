#include <glm/glm.hpp>

#include <Mesh.h>

class Entity
{
    friend class Technique;

  private:
    Mesh *mMesh;
    glm::vec3 mRot;
    glm::vec3 mPos;
    glm::vec3 mScl;
  public:
    Entity();
    Entity(Mesh *mesh, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3 scl = glm::vec3(1.0f, 1.0f, 1.0f));

    void render();
    void updatePosition(glm::vec3 pos);
    void updateRotation(glm::vec3 rot);
    void updateScale(glm::vec3 scl);
};
