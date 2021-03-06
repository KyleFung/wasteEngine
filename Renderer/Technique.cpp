#include <Technique.h>

Technique::Technique(std::string vs, std::string fs)
{
    mShader = Shader(vs, fs);
}

void Technique::usePipeline(Pipeline *pipeline)
{
    mPipeline = pipeline;
}

void Technique::bind()
{
    if(mShader.mInited != true)
        mShader.init();
    mShader.bind();
}

void Technique::renderScene(Scene *scene)
{
    updateLights(*scene->getDirLights(), *scene->getPntLights());

    std::vector<Entity> &entities = *scene->getEntities();
    for(int i = 0;  i < entities.size(); i++)
    {
        renderEntity(&entities[i]);
    }
}

void Technique::renderEntity(Entity *entity)
{
    bind();
    mPipeline->translate(entity->mPos.x, entity->mPos.y, entity->mPos.z);
    mPipeline->rotate(entity->mRot.x, entity->mRot.y, entity->mRot.z);
    mPipeline->scale(entity->mScl.x, entity->mScl.y, entity->mScl.z);
    setMvpUniform();

    //Render
    entity->render();
}

void Technique::setMvpUniform()
{
    mPipeline->project(60.0f);
    mShader.updateMVP(mPipeline->getTrans());
}

void Technique::updateLights(std::vector<Light::DirLight> dirLights,
                             std::vector<Light::PntLight> pntLights)
{
    mShader.updateLights(dirLights, pntLights);
}
