#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

namespace Light
{
    struct DirLight
    {
        glm::vec3 mDir;
        glm::vec3 mCol;
    };

    struct PntLight
    {
        glm::vec3 mPos;
        glm::vec3 mCol;
    };
};

#endif
