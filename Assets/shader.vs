#version 330
//Uniform MVP
uniform mat4 gMVP;

//Input layout
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

//Output to FS
out vec3 pos;
out vec3 normal;
out vec2 tex;

void main()
{
    gl_Position = gMVP * vec4(Position, 1.0f);
    normal = Normal;
    tex = TexCoord;
    pos = Position;
}
