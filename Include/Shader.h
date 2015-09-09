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

    Shader(std::string vs, std::string fs);
    Shader();

    void init();
    void bind();

    void updateMVP(glm::mat4 mvp);
    void updateLights(std::vector<Light::DirLight> dirLights);

  private:
    void addShader(const char* pShaderText, GLenum ShaderType);
    bool initUniforms();

    Pipeline mPipeline;
    std::string mVs;
    std::string mFs;
    GLuint mProgram;

    GLuint gMVP;
    GLuint gSamplerLocation;
    GLuint gDrLtDirs[8];
    GLuint gDrLtCols[8];
};

#endif
