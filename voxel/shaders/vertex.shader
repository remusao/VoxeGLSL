#version 150 core

in vec3 position;
out vec4 vsColor;

void main()
{
    vsColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_Position = vec4(position, 1.0);
}
