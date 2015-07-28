class Renderer
{
  public:
    Renderer();
    ~Renderer();

    bool init();
    void renderScene();

    void createVB();
    void createIB();

  private:
    GLuint mVBO;
    GLuint mIBO;

    Shader mShader;

    Camera mCamera;
};

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 tex;
    Vertex(glm::vec3 position, glm::vec2 texture)
    {
        pos = position;
        tex = texture;
    }
};
