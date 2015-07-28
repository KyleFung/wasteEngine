#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include <GL/glew.h>

#include <Shader.h>
#include <Pipeline.h>

class Technique
{
  private:
    Shader *mShader;
    Pipeline *mPipeline;

  public:
    void useShader(Shader *shader);
    void usePipeline(Pipeline *pipeline);
    void bind();
    void initShader();
    void setMvpUniform();
};

#endif
