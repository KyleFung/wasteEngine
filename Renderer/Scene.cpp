#include <Scene.h>

std::vector<Entity> *Scene::getEntities()
{
    return &mEntities;
}

std::vector<Light::DirLight> *Scene::getDirLights()
{
    return &mDirLights;
}

std::vector<Light::PntLight> *Scene::getPntLights()
{
    return &mPntLights;
}

void Scene::addEntity(Entity entity)
{
    mEntities.push_back(entity);
}

void Scene::addLight(Light::DirLight light)
{
    mDirLights.push_back(light);
}

void Scene::addLight(Light::PntLight light)
{
    mPntLights.push_back(light);
}
