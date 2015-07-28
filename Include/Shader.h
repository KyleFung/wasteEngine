#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <string>
#include <iostream>
#include <cstdio>

#include <utils.h>
#include <Camera.h>
#include <Pipeline.h>

class Shader
{
  public:
    bool mInited;

    Shader();

    void init();
    void bind();

    void updateMVP(glm::mat4 mvp);

  private:
    void addShader(const char* pShaderText, GLenum ShaderType);
    bool initUniforms();

    Pipeline mPipeline;
    GLuint mProgram;

    GLuint gMVP;
    GLuint gSamplerLocation;
};

#endif
