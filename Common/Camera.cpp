#include <Camera.h>

Camera::Camera(int windowWidth, int windowHeight)
{
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    mPos = glm::vec3(0.0f, 0.0f, 0.0f);
    mDir = glm::vec3(0.0f, 0.0f, 1.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    mWinWidth = windowWidth;
    mWinHeight = windowHeight;

    mMouseX = centerX;
    mMouseY = centerY;

    stepSize = 0.1f;
    glutWarpPointer(centerX, centerY);
}

bool Camera::onKey(int key)
{
    bool ret = false;
    switch(key)
    {
        case GLUT_KEY_UP:
        {
            mPos += (mDir * stepSize);
            ret = true;
        }
        break;

        case GLUT_KEY_DOWN:
        {
            mPos -= (mDir * stepSize);
            ret = true;
        }
        break;

        case GLUT_KEY_LEFT:
        {
            glm::vec3 l = glm::normalize(glm::cross(mUp, mDir));
            l *= stepSize;
            mPos += l;
            ret = true;
        }
        break;

        case GLUT_KEY_RIGHT:
        {
            glm::vec3 r = glm::normalize(glm::cross(mDir, mUp));
            r *= stepSize;
            mPos += r;
            ret = true;
        }
        break;
    }

    return ret;
}

bool Camera::onMouse(int x, int y)
{
    //Spin the camera around the world up vector
    int deltaX = mWinWidth / 2 - x;
    deltaX *= 10;
    mMouseX = x;
    mDir = glm::normalize(glm::rotate(mDir, deltaX / 100000.f, glm::vec3(0.0f, 1.0f, 0.0f)));
    mUp = glm::normalize(glm::rotate(mUp, deltaX / 100000.f, glm::vec3(0.0f, 1.0f, 0.0f)));

    int deltaY = mWinHeight / 2 - y;
    deltaY *= 10;
    mMouseY = y;
    mDir = glm::normalize(glm::rotate(mDir, deltaY / 100000.f, glm::vec3(1.0f, 0.0f, 0.0f)));
    mUp = glm::normalize(glm::rotate(mUp, deltaY / 100000.f, glm::vec3(1.0f, 0.0f, 0.0f)));

    return true;
}
