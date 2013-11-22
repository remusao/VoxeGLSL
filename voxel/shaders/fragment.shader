#version 150 core

out vec4 color;
in vec4 gsColor;

void main()
{
    color = gsColor; //vec4(1.0, 1.0, 1.0, 1.0); // colorGS;
}
