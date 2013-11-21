#version 150 core

in vec3 position;

uniform mat4 camera, m;

void main()
{
    gl_Position = camera * m * vec4(position, 1.0);
}
