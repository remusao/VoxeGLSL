#version 400

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

in vec4 vsColor[];
out vec4 gsColor;

uniform mat4 camera, m;

void main ()
{
    mat4 pvm = camera * m;
    float y = (m * gl_in[0].gl_Position).y;
    if (y < 2)
    {
        gsColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
    else if (y < 50)
    {
        gsColor = vec4(0.0, y / 100.0, 0.0, 1.0);
    }
    else if (y < 100)
    {
        gsColor = vec4(y / 255.0, y / 255.0, y / 255.0, 1.0);
    }
    else
    {
        gsColor = vec4(1, 1, 1, 1);
    }

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
