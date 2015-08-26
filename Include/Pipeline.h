#ifndef PIPELINE_H
#define PIPELINE_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Camera.h>

class Pipeline
{
    public:
       Pipeline();
       //Model space transformations
       void scale(float x, float y, float z);
       void translate(float x, float y, float z);
       void rotate(float x, float y, float z, float theta);
       void rotate(float x, float y, float z);

       //Projection space transformation
       void project(float fov);

       //View space transformation
       void updateCamMatrix();
       void setCamera(Camera* camera);

       const glm::mat4 getTrans();
    private:
       glm::mat4 scaleMatrix;
       glm::mat4 translationMatrix;
       glm::mat4 rotationMatrix;
       glm::mat4 perspectiveMatrix;
       glm::mat4 cameraMatrix;

       Camera* pCamera;
};

#endif
