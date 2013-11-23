#version 400

// Receive a point
layout (points) in;
// Emit vertices
layout (triangle_strip, max_vertices = 24) out;

// Deal with color
in vec4 vsColor[];
out vec4 gsColor;

// Projection matrix
uniform mat4 mvp;
uniform vec3 normal;

void main ()
{
    // Color
    float h = gl_in[0].gl_Position.y / 255.0;
    gsColor = vec4(h, h, h, 1.0);

    // Pre-compute transformations
    vec4 transVertices[8] = vec4[8]
    (
        mvp * (gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 1)),
        mvp * (gl_in[0].gl_Position + vec4(-0.5,  0.5, -0.5, 1)),
        mvp * (gl_in[0].gl_Position + vec4( 0.5, -0.5, -0.5, 1)),
        mvp * (gl_in[0].gl_Position + vec4( 0.5,  0.5, -0.5, 1)),
        mvp * (gl_in[0].gl_Position + vec4(-0.5, -0.5,  0.5, 1)),
        mvp * (gl_in[0].gl_Position + vec4(-0.5,  0.5,  0.5, 1)),
        mvp * (gl_in[0].gl_Position + vec4( 0.5, -0.5,  0.5, 1)),
        mvp * (gl_in[0].gl_Position + vec4( 0.5,  0.5,  0.5, 1))
    );

    // Front
    // (n.x * 0 + n.y * 0 + n.z * -1)
    if (normal.z >= 0)
    {
        gl_Position = transVertices[0];
        EmitVertex();
        gl_Position = transVertices[1];
        EmitVertex();
        gl_Position = transVertices[2];
        EmitVertex();
        gl_Position = transVertices[3];
        EmitVertex();
        EndPrimitive();
    }

    // Right
    // (n.x * 0 + n.y * 1 + n.z * 0)
    if (normal.x <= 0)
    {
        gl_Position = transVertices[7];
        EmitVertex();
        gl_Position = transVertices[6];
        EmitVertex();
        gl_Position = transVertices[3];
        EmitVertex();
        gl_Position = transVertices[2];
        EmitVertex();
        EndPrimitive();
    }

    // Back
    // (n.x * 0 + n.y * 0 + n.z * 1)
    if (normal.z <= 0)
    {
        gl_Position = transVertices[7];
        EmitVertex();
        gl_Position = transVertices[5];
        EmitVertex();
        gl_Position = transVertices[6];
        EmitVertex();
        gl_Position = transVertices[4];
        EmitVertex();
        EndPrimitive();
    }

    // Bottom
    // (n.x * 0 + n.y * -1 + n.z * 0)
    if (normal.y >= 0)
    {
        gl_Position = transVertices[4];
        EmitVertex();
        gl_Position = transVertices[0];
        EmitVertex();
        gl_Position = transVertices[6];
        EmitVertex();
        gl_Position = transVertices[2];
        EmitVertex();
        EndPrimitive();
    }

    // Left
    // (n.x * -1 + n.y * 0 + n.z * 0)
    if (normal.x >= 0)
    {
        gl_Position = transVertices[1];
        EmitVertex();
        gl_Position = transVertices[0];
        EmitVertex();
        gl_Position = transVertices[5];
        EmitVertex();
        gl_Position = transVertices[4];
        EmitVertex();
        EndPrimitive();
    }

    // Top
    // (n.x * 1 + n.y * 0 + n.z * 0)
    if (normal.y <= 0)
    {
        gl_Position = transVertices[3];
        EmitVertex();
        gl_Position = transVertices[1];
        EmitVertex();
        gl_Position = transVertices[7];
        EmitVertex();
        gl_Position = transVertices[5];
        EmitVertex();
        EndPrimitive();
    }
}
