#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include <GL/glew.h>

#include <vector>
#include <string>

#include <Shader.h>
#include <Pipeline.h>
#include <Entity.h>
#include <Light.h>

class Technique
{
  private:
    Shader mShader;
    Pipeline *mPipeline;

  public:
    Technique(std::string vs, std::string fs);
    void usePipeline(Pipeline *pipeline);
    void bind();
    void renderEntity(Entity *entity);
    void updateLights(std::vector<Light::DirLight> dirLights);

  private:
    void setMvpUniform();
};

#endif
