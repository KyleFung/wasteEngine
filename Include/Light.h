#include <glm/glm.hpp>

struct Light
{
    enum type
    {
        point,
        directional
    };
    type mType;
    glm::vec3 mDir;
    glm::vec3 mCol;
};
