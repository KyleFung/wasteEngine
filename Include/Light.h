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
};

#endif
