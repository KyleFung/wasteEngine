#include <Technique.h>

void Technique::useShader(Shader *shader)
{
    mShader = shader;
}

void Technique::usePipeline(Pipeline *pipeline)
{
    mPipeline = pipeline;
}

void Technique::bind()
{
    mShader->bind();
}

void Technique::initShader()
{
    if(!mShader->mInited)
    {
        mShader->init();
    }
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
    mShader->updateMVP(mPipeline->getTrans());
}
