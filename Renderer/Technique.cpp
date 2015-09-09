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

void Technique::renderEntity(Entity *entity)
{
    //Set up MVP
    mPipeline->translate(entity->mPos.x, entity->mPos.y, entity->mPos.z);
    mPipeline->rotate(entity->mRot.x, entity->mRot.y, entity->mRot.z);
    setMvpUniform();

    //Render
    entity->render();
}

void Technique::setMvpUniform()
{
    mPipeline->project(60.0f);
    mShader.updateMVP(mPipeline->getTrans());
}

void Technique::updateLights(std::vector<Light::DirLight> dirLights)
{
    mShader.updateLights(dirLights);
}
