#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Mesh.h>
#include <LoadedMesh.h>
#include <GeneratedMesh.h>
#include <Shader.h>
#include <Technique.h>

#include <math.h>
#include <unistd.h>

#define WINDOW_WIDTH  640 
#define WINDOW_HEIGHT 480

LoadedMesh dragonMesh;
Entity dragon;
std::vector<Light::DirLight> dirLights;

Camera* eye = NULL;
Technique tech = Technique("Assets/shader.vs", "Assets/shader.fs");
Pipeline pipeline;

void Render()
{
    //Set up
    glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render setup
    tech.updateLights(dirLights);
    tech.renderEntity(&dragon);

    //Render call
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
    eye->mPos = glm::vec3(0.0f, 0.0f, 3.0f);
    pipeline.setCamera(eye);

    //Set up the technique
    tech.usePipeline(&pipeline);
    tech.bind();

    //Set up light vector
    Light::DirLight dirLight;
    dirLight.mDir = glm::vec3(1.0f, 1.0f, 1.0f);
    dirLight.mCol = glm::vec3(1.0f, 1.0f, 1.0f);
    dirLights.resize(0);
    dirLights.push_back(dirLight);

    //Load scene
    dragonMesh = LoadedMesh();
    dragonMesh.loadSceneFromFiles("Assets/Dragon/Dargon posing.obj");
    dragon = Entity(&dragonMesh);

    //Start loop
    glutMainLoop();

    return 0;
}
