bool Renderer::init()
{
    return true;
}

void Renderer::renderScene(void)
{
    //Update scaling factor **SHOULD NOT BE HERE**
    static float scale = 0.0f;
    scale += 0.1f;

    Pipeline p;
    p.setCamera(eye);
    p.translate(0.0f, 0.0f, 5.0f);
    p.rotate(0.0f, scale, 0.0f);
    p.project(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1000.0f);
    glm::mat4 m = p.getTrans();

    glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, glm::value_ptr(p.getTrans()));
    glUniform1i(gSamplerLocation, 0);

    //Black background
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Enable position data
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    //Vertex layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 12);
    pTexture->bind(GL_TEXTURE0);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    //Disable position data
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //Swap buffer chain
    // HACK VSYNC ***IMPLEMENT FPS COUNTER LATER***
    usleep(16660);
    glutSwapBuffers();

    glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

//Initialize vertex buffers
void Renderer::createVB()
{
    //Load tetrahedron vertices
    Vertex Vertices[4] = 
    {
        Vertex(glm::vec3(-1.0f, -1.0f, 0.5773f) ,glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.0f, -1.0f, -1.15475f),glm::vec2(0.5f, 0.0f)),
        Vertex(glm::vec3(1.0f, -1.0f, 0.5773f)  ,glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(0.0f, 1.0f, 0.0f)      ,glm::vec2(0.5f, 1.0f))
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void Renderer::createIB()
{
    //Load tetrahedron indices
    unsigned int Indices[] =
    {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}
