#version 400
 
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

uniform mat4 cameraToClipMatrix;
uniform mat4 worldToCameraMatrix;
uniform mat4 modelToWorldMatrix;

const vec4 cubeVerts[8] = vec4[8](
    vec4(-0.5 , -0.5, -0.5,1),  //LB   0
    vec4(-0.5, 0.5, -0.5,1), //L T   1
    vec4(0.5, -0.5, -0.5,1), //R B    2
    vec4( 0.5, 0.5, -0.5,1),  //R T   3
    //back face
    vec4(-0.5, -0.5, 0.5,1), // LB  4
    vec4(-0.5, 0.5, 0.5,1), // LT  5
    vec4(0.5, -0.5, 0.5,1),  // RB  6
    vec4(0.5, 0.5, 0.5,1)  // RT  7
);

const int  cubeIndices[24]  = int [24]
(
 0,1,2,3, //front
 7,6,3,2, //right
 7,5,6,4,  //back or whatever
 4,0,6,2, //btm 
 1,0,5,4, //left
 3,1,7,5
 );   

void main ()
{
    // Bottom face
    // Top face
    // 
  for(int i = 0; i < gl_VerticesIn; i++)
  {
    // Initial point
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();

    // 
    gl_Position.y = gl_in[i].gl_Position.y + 5.0;
    EmitVertex();
    gl_Position.y = gl_in[i].gl_Position.y;
    gl_Position.x = gl_in[i].gl_Position.x - 2.0;
    EmitVertex();
    gl_Position.y = gl_in[i].gl_Position.y + 5.0;
    gl_Position.x = gl_in[i].gl_Position.x - 2.0;
    EmitVertex();
  }
}
