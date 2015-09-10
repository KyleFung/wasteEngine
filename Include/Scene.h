#ifndef SCENE_H
#define SCENE_H

#include <Entity.h>
#include <Light.h>

class Scene
{
  public:
    void addEntity(Entity entity);
    void addLight(Light::DirLight light);
    void addLight(Light::PntLight light);

    std::vector<Entity> *getEntities();
    std::vector<Light::DirLight> *getDirLights();
    std::vector<Light::PntLight> *getPntLights();

  private:
    //Objects to be rendered in scene
    std::vector<Entity> mEntities;

    //Lighting setup
    std::vector<Light::DirLight> mDirLights;
    std::vector<Light::PntLight> mPntLights;
};

#endif
