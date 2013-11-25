#version 150 core

uniform mat4 mvp;
in vec3 position;
out vec4 vsColor;
flat out int visible;


void main()
{
    vsColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_Position = vec4(position, 1.0);

    /* create the bounding box of the object */
    vec4 BoundingBox[8];
    BoundingBox[0] = mvp * (gl_Position + vec4( 1.0, 1.0, 1.0, 1.0));
    BoundingBox[1] = mvp * (gl_Position + vec4(-1.0, 1.0, 1.0, 1.0));
    BoundingBox[2] = mvp * (gl_Position + vec4( 1.0,-1.0, 1.0, 1.0));
    BoundingBox[3] = mvp * (gl_Position + vec4(-1.0,-1.0, 1.0, 1.0));
    BoundingBox[4] = mvp * (gl_Position + vec4( 1.0, 1.0,-1.0, 1.0));
    BoundingBox[5] = mvp * (gl_Position + vec4(-1.0, 1.0,-1.0, 1.0));
    BoundingBox[6] = mvp * (gl_Position + vec4( 1.0,-1.0,-1.0, 1.0));
    BoundingBox[7] = mvp * (gl_Position + vec4(-1.0,-1.0,-1.0, 1.0));

    /* check how the bounding box resides regarding to the view frustum */   
    int outOfBounds[6] = int[6](0, 0, 0, 0, 0, 0);

    for (int i = 0; i < 8; ++i)
    {
        if (BoundingBox[i].x >  BoundingBox[i].w) ++outOfBounds[0];
        if (BoundingBox[i].x < -BoundingBox[i].w) ++outOfBounds[1];
        if (BoundingBox[i].y >  BoundingBox[i].w) ++outOfBounds[2];
        if (BoundingBox[i].y < -BoundingBox[i].w) ++outOfBounds[3];
        if (BoundingBox[i].z >  BoundingBox[i].w) ++outOfBounds[4];
        if (BoundingBox[i].z < -BoundingBox[i].w) ++outOfBounds[5];
    }

    bool inFrustum = true;

    for (int i = 0; i < 6; ++i)
    {
        if (outOfBounds[i] == 8)
        {
            inFrustum = false;
        }
    }

    visible = inFrustum ? 1 : 0;
}
