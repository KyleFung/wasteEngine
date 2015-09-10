#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include <GL/glew.h>

#include <vector>
#include <string>

#include <Entity.h>
#include <Light.h>
#include <Pipeline.h>
#include <Scene.h>
#include <Shader.h>

class Technique
{
  private:
    Shader mShader;
    Pipeline *mPipeline;

  public:
    Technique(std::string vs, std::string fs);
    void usePipeline(Pipeline *pipeline);
    void renderScene(Scene *scene);
    void renderEntity(Entity *entity);
    void updateLights(std::vector<Light::DirLight> dirLights,
                      std::vector<Light::PntLight> pntLights);
  private:
    void setMvpUniform();
    void bind();
};

#endif
