#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

#include <utils.h>
#include <Camera.h>
#include <Pipeline.h>
#include <Light.h>

class Shader
{
  public:
    bool mInited;

    Shader();

    void init();
    void bind();

    void updateMVP(glm::mat4 mvp);
    void updateLights(std::vector<Light> lights);

  private:
    void addShader(const char* pShaderText, GLenum ShaderType);
    bool initUniforms();

    Pipeline mPipeline;
    GLuint mProgram;

    GLuint gMVP;
    GLuint gSamplerLocation;
    GLuint gLightDirs[8];
    GLuint gLightCols[8];
};

#endif
