#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <utils.h>

class Camera
{
  public:
    Camera(int windowWidth, int windowHeight);
    bool onKey(int key);
    bool onMouse(int x, int y);

    glm::vec3 mPos;
    float mPitch;
    float mYaw;

    int mWinWidth;
    int mWinHeight;

  private:
    float stepSize;
    int mMouseX;
    int mMouseY;
};

#endif
