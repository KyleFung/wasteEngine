#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
  public:
    Camera(int windowWidth, int windowHeight);
    bool onKey(int key);
    bool onMouse(int x, int y);

    glm::vec3 mPos;
    glm::vec3 mDir;
    glm::vec3 mUp;

    int mWinWidth;
    int mWinHeight;

  private:
    float stepSize;
    int mMouseX;
    int mMouseY;
};

#endif
