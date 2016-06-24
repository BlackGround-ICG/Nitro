#version 330

layout (location = 0) in vec3 Position;

void main()
{
    gl_Position = vec4(1.5 * Position.x, 1.5 * Position.y, Position.z, 1.0);
}