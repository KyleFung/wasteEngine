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

//Declare scene elements
LoadedMesh dragonMesh;
Entity dragon;
LoadedMesh potMesh;
Entity pot;
std::vector<Light::DirLight> dirLights;
std::vector<Light::PntLight> pntLights;

Camera* eye = NULL;
Technique tech = Technique("Assets/shader.vs", "Assets/shader.fs");
Technique solid = Technique("Assets/shader.vs", "Assets/solid.fs");
Pipeline pipeline;

void Render()
{
    //Set up
    glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render setup
    tech.updateLights(dirLights, pntLights);
    tech.renderEntity(&dragon);
    solid.renderEntity(&pot);

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
    solid.usePipeline(&pipeline);

    //Set up light vector
    Light::PntLight light;
    light.mPos = glm::vec3(1.0f, 0.0f, 0.0f);
    light.mCol = glm::vec3(1.0f, 0.0f, 0.0f);
    dirLights.resize(0);
    pntLights.resize(0);
    pntLights.push_back(light);

    //Load scene
    dragonMesh = LoadedMesh("Assets/Dragon/Dargon posing.obj");
    dragon = Entity(&dragonMesh);

    potMesh = LoadedMesh("Assets/teapot.obj");
    pot = Entity(&potMesh);
    pot.updateScale(glm::vec3(0.1f, 0.1f, 0.1f));

    //Start loop
    glutMainLoop();

    return 0;
}
