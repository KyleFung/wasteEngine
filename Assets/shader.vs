#version 330
//List out uniforms variables
uniform mat4 gMVP;

//List out layout variables
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

//List out output variables
out vec3 normal;
out vec2 tex;

void main()
{
    gl_Position = gMVP * vec4(Position, 1.0f);
    normal = Normal;
    tex = TexCoord;
}
