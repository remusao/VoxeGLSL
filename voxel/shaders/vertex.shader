#version 150 core

in vec3 position;

uniform mat4 p, v, m;

void main()
{
    gl_Position = p * v * m * vec4(position, 1.0);
}
