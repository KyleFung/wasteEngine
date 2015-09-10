#version 330

//Variables from VS
in vec3 pos;
in vec3 normal;
in vec2 tex;

//Output of FS
out vec4 FragColor;

//Texture sampler
uniform sampler2D gSampler;

//Light input
struct DirLight
{
    vec3 dir;
    vec3 col;
};
struct PntLight
{
    vec3 pos;
    vec3 col;
};
uniform DirLight gDirLights[8];
uniform PntLight gPntLights[8];

void main()
{
    vec3 intensity = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < 8; i++)
    {
        //Calculate directional lighting
        intensity += gDirLights[i].col * dot(normal, gDirLights[i].dir);
        //Calculate point lighting
        intensity += gPntLights[i].col * dot(normal, gPntLights[i].pos - pos);
    }
    FragColor = texture2D(gSampler, tex.st) * vec4(intensity, 1.0f);
}
