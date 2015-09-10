#include <Shader.h>

Shader::Shader(std::string vs, std::string fs)
{
    mInited = false;
    mVs = vs;
    mFs = fs;
}

Shader::Shader()
{
    mInited = false;
    mVs = "";
    mFs = "";
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
    if (!ReadFile(mVs.c_str(), vs))
        exit(1);

    if (!ReadFile(mFs.c_str(), fs))
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

    //Get light locations
    for(int i = 0; i < 8; i++)
    {
        std::string index = numToStr(i);
        gDrLtDirs[i] = glGetUniformLocation(mProgram,
                                             ("gDirLights[" + index + "].dir").c_str());
        gDrLtCols[i] = glGetUniformLocation(mProgram,
                                             ("gDirLights[" + index + "].col").c_str());
        gPtLtDirs[i] = glGetUniformLocation(mProgram,
                                             ("gPntLights[" + index + "].pos").c_str());
        gPtLtCols[i] = glGetUniformLocation(mProgram,
                                             ("gPntLights[" + index + "].col").c_str());
    }
    return true;
}

void Shader::updateMVP(glm::mat4 mvp)
{
    glUseProgram(mProgram);
    glUniformMatrix4fv(gMVP, 1, false, &mvp[0][0]);
}

void Shader::updateLights(std::vector<Light::DirLight> dirLights,
                          std::vector<Light::PntLight> pntLights)
{
    glUseProgram(mProgram);
    for(int i = 0; i < std::min((int)dirLights.size(), 8); i++)
    {
        glUniform3fv(gDrLtDirs[i], 1, &dirLights[i].mDir[0]);
        glUniform3fv(gDrLtCols[i], 1, &dirLights[i].mCol[0]);
    }
    for(int i = 0; i < std::min((int)pntLights.size(), 8); i++)
    {
        glUniform3fv(gPtLtDirs[i], 1, &pntLights[i].mPos[0]);
        glUniform3fv(gPtLtCols[i], 1, &pntLights[i].mCol[0]);
    }
}
