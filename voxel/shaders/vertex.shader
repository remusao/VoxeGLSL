#version 150 core

in vec3 position;

uniform mat4 pvm;

void main()
{
    gl_Position = pvm * vec4(position, 1.0);
}
