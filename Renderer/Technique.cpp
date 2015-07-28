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

void Technique::setMvpUniform()
{
    mPipeline->project(60.0f);
    mShader->updateMVP(mPipeline->getTrans());
}
