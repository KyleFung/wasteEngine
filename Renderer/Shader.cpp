#include <Shader.h>

Shader::Shader()
{
    mInited = false;
}

//Helper function to compile and link shader programs
void Shader::init()
{
    //Initialize the shader program
    mProgram = glCreateProgram();
    if (mProgram == 0)
    {
        std::printf("Error creating shader program\n");
        exit(1);
    }

    //Load shaders as strings
    std::string vs;
    std::string fs;
    if (!ReadFile("Assets/shader.vs", vs))
        exit(1);

    if (!ReadFile("Assets/shader.fs", fs))
        exit(1);

    //Compile shaders and add them to the program
    addShader(vs.c_str(), GL_VERTEX_SHADER);
    addShader(fs.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    //Link the shader program together
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (success == 0)
    {
        glGetProgramInfoLog(mProgram, sizeof(errorLog), NULL, errorLog);
        std::fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
        exit(1);
    }

    glValidateProgram(mProgram);
    glGetProgramiv(mProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mProgram, sizeof(errorLog), NULL, errorLog);
        std::fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
        exit(1);
    }

    initUniforms();

    mInited = true;
}

void Shader::addShader(const char* pShaderText, GLenum shaderType)
{
    //Initialize the shader program
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0)
    {
        std::printf("Error creating shader type %d\n", shaderType);
        exit(1);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint lengths[1];
    lengths[0]= strlen(pShaderText);

    //Load source into shader object and compile
    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, infoLog);
        exit(1);
    }

    //Attach completed shader object to input shader program
    glAttachShader(mProgram, shader);
}

void Shader::bind()
{
    //Set the program as the shader in use
    glUseProgram(mProgram);
}

bool Shader::initUniforms()
{
    //Set up shader uniform locations from program
    gMVP = glGetUniformLocation(mProgram, "gMVP");
    gSamplerLocation = glGetUniformLocation(mProgram, "gSampler");

    return true;
}

void Shader::updateMVP(glm::mat4 mvp)
{
    glUniformMatrix4fv(gMVP, 1, false, &mvp[0][0]);
}
