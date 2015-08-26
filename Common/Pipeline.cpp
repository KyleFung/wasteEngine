#include <Pipeline.h>

Pipeline::Pipeline()
{
    scaleMatrix = glm::mat4(1.0f); 
    translationMatrix = glm::mat4(1.0f); 
    rotationMatrix = glm::mat4(1.0f);
    perspectiveMatrix = glm::mat4(1.0f);
}

void Pipeline::scale(float x, float y, float z)
{
    scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Pipeline::translate(float x, float y, float z)
{
    translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Pipeline::rotate(float x, float y, float z, float theta)
{
    rotationMatrix = glm::rotate(glm::mat4(1.0f), theta/180.0f, glm::vec3(x, y, z));
}

void Pipeline::rotate(float x, float y, float z)
{
    rotationMatrix =   glm::rotate(glm::mat4(1.0f), 3.14f * z/180.0f, glm::vec3(0.0f, 0.0f, 1.0f))
                     * glm::rotate(glm::mat4(1.0f), 3.14f * y/180.0f, glm::vec3(0.0f, -1.0f, 0.0f))
                     * glm::rotate(glm::mat4(1.0f), 3.14f * x/180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Pipeline::project(float fov)
{
    float width = (float) pCamera->mWinWidth;
    float height = (float) pCamera->mWinHeight;
    float near = 1.f;
    float far = 1000.f;

    perspectiveMatrix = glm::perspectiveFov( 3.14f / 180.0f * fov, width, height, near, far);
    perspectiveMatrix[2][2] *= -1;
    perspectiveMatrix[2][3] *= -1;
}

void Pipeline::setCamera(Camera* camera)
{
    pCamera = camera;
}

void Pipeline::updateCamMatrix()
{
    glm::mat4 camTran = glm::mat4(1.0f);
    glm::mat4 camRotn = glm::mat4(1.0f);

    float yaw = pCamera->mYaw;
    float pitch = pCamera->mPitch;

    glm::vec3 initView = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 initUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 W = glm::normalize(glm::rotateY(glm::rotateX(initView, degToRad(pitch)), degToRad(yaw)));
    glm::vec3 V = glm::normalize(glm::rotateY(glm::rotateX(initUp, degToRad(pitch)), degToRad(yaw)));
    glm::vec3 U = glm::cross(W, V);

    //HARDCODED BUT FUNCTIONAL **CHANGE LATER**
    //Translate to camera space
    camTran[3][0] = - pCamera->mPos.x;
    camTran[3][1] = - pCamera->mPos.y;
    camTran[3][2] = - pCamera->mPos.z;

    //UVW transformation
    camRotn[0][0] = U.x;
    camRotn[0][1] = V.x;
    camRotn[0][2] = W.x;
    camRotn[0][3] = 0.0f;

    camRotn[1][0] = U.y;
    camRotn[1][1] = V.y;
    camRotn[1][2] = W.y;
    camRotn[1][3] = 0.0f;

    camRotn[2][0] = U.z;
    camRotn[2][1] = V.z;
    camRotn[2][2] = W.z;
    camRotn[2][3] = 0.0f;

    camRotn[3][0] = 0.0f;
    camRotn[3][1] = 0.0f;
    camRotn[3][2] = 0.0f;
    camRotn[3][3] = 1.0f;

    cameraMatrix = camRotn * camTran;
}

const glm::mat4 Pipeline::getTrans()
{
    updateCamMatrix();
    return perspectiveMatrix * cameraMatrix * translationMatrix * rotationMatrix * scaleMatrix;
}
