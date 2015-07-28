#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Mesh.h>
#include <Shader.h>
#include <Technique.h>

#include <math.h>
#include <unistd.h>

#define WINDOW_WIDTH  640 
#define WINDOW_HEIGHT 480

Mesh mesh;

Camera* eye = NULL;
Technique tech;
Pipeline pipeline;
Shader shader;

void Render()
{
    //Set up
    glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render setup
    shader.init();
    tech.useShader(&shader);
    tech.usePipeline(&pipeline);
    tech.bind();
    tech.setMvpUniform();

    //Render call
    mesh.render();
    glutSwapBuffers();

    //Reset controls
    glutWarpPointer(eye->mWinWidth/2, eye->mWinHeight/2);
}

static void keyHandler(int key, int x, int y)
{
    eye->onKey(key);
}

static void mouseHandler(int x, int y)
{
    eye->onMouse(x, y);
}

static void specialHandler(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'q':
           exit(0);
    }
}

int main(int argc, char **argv)
{
    //Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("GL Test");

    glutDisplayFunc(Render);
    glutIdleFunc(Render);
    glutSpecialFunc(keyHandler);
    glutKeyboardFunc(specialHandler);
    glutPassiveMotionFunc(mouseHandler);

    //Initialize glew
    GLenum res = glewInit();
    if(res != GLEW_OK)
        return 1;

    //Set up GL state
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    //Set up renderer
    eye = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
    eye->mPos = glm::vec3(3.0f, 0.0f, 0.0f);
    eye->mDir = glm::vec3(-1.0f, 0.0f, 0.0f);
    eye->mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    pipeline.setCamera(eye);

    //Load scene
    mesh = Mesh();
    mesh.loadSceneFromFiles("Assets/Dragon/Dargon posing.obj");

    //Start loop
    glutMainLoop();

    return 0;
}
