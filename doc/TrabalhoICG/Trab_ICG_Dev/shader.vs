#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

out vec2 TexCoord0;
void main()
{
    gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
    TexCoord0 = TexCoord;
}
