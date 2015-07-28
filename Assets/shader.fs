#version 330

//List out variables from VS
in vec3 normal;
in vec2 tex;

//Output of FS
out vec4 FragColor;

//Get the sampler
uniform sampler2D gSampler;

void main()
{
    FragColor = texture2D(gSampler, tex.st) * dot(normal, vec3(1, 1, 1));
}
