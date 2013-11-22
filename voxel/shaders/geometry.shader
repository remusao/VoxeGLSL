#version 400

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

uniform mat4 camera, m;

void main ()
{
    mat4 pvm = camera * m;

    // Front
    gl_Position = pvm * gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.0, 0.0, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.0, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.0, 0.0));
    EmitVertex();
    EndPrimitive();

    // Left
    gl_Position = pvm * gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.0, 0.5, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.0, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.5, 0.0));
    EmitVertex();
    EndPrimitive();

    // Right
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.0, 0.0, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.0, 0.5, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.0, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0));
    EmitVertex();
    EndPrimitive();

    // Top
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.0, 0.0));;
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.0, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.5, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0));
    EmitVertex();
    EndPrimitive();

    // Back
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.0, 0.5, 0.0));;
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.0, 0.5, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.5, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0));
    EmitVertex();
    EndPrimitive();

    // Bottom
    gl_Position = pvm * gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.0, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.0, 0.5, 0.0));
    EmitVertex();
    gl_Position = pvm * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.5, 0.0));
    EmitVertex();
    EndPrimitive();
}
