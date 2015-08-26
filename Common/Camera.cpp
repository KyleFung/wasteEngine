#include <Camera.h>

Camera::Camera(int windowWidth, int windowHeight)
{
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    mPos = glm::vec3(0.0f, 0.0f, 0.0f);
    mPitch = 0.0f;
    mYaw = 0.0f;

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
            mPos.x -= stepSize * sin(degToRad(mYaw));
            mPos.z -= stepSize * cos(degToRad(mYaw));
            ret = true;
        }
        break;

        case GLUT_KEY_DOWN:
        {
            mPos.x += stepSize * sin(degToRad(mYaw));
            mPos.z += stepSize * cos(degToRad(mYaw));
            ret = true;
        }
        break;

        case GLUT_KEY_LEFT:
        {
            mPos.x -= stepSize * sin(degToRad(mYaw + 90.0));
            mPos.z -= stepSize * cos(degToRad(mYaw + 90.0));
            ret = true;
        }
        break;

        case GLUT_KEY_RIGHT:
        {
            mPos.x -= stepSize * sin(degToRad(mYaw - 90.0));
            mPos.z -= stepSize * cos(degToRad(mYaw - 90.0));
            ret = true;
        }
        break;
    }

    return ret;
}

bool Camera::onMouse(int x, int y)
{
    //Increment the yaw of the camera
    int deltaX = mWinWidth / 2 - x;
    mMouseX = x;
    mYaw += deltaX * 0.002f;
    mYaw = fmod(mYaw, 360.0f);

    //Increment the pitch of the camera
    int deltaY = mWinHeight / 2 - y;
    mMouseY = y;
    mPitch += deltaY * 0.002f;
    mPitch = clamp(mPitch, -90.0f, 90.0f);

    return true;
}
