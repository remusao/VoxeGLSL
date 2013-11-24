
#include <cmath>
#include "frustum.hh"

#define ANG2RAD (3.14159265358979323846 / 180.0)

void Frustum::setCamInternals(float angle, float ratio, float nearD, float farD)
{
    // store the information
    ratio_ = ratio;
    nearD_ = nearD;
    farD_ = farD;

    // compute width and height of the near section
    tang_ = (float)tan(ANG2RAD * angle * 0.5) ;
    height_ = nearD_ * tang_;
    width_ = height_ * ratio_;
}


void Frustum::setCamDef(glm::vec3 p, glm::vec3 l, glm::vec3 u)
{
    cc_ = p;

    // compute the Z axis of the camera referential
    // this axis points in the same direction from
    // the looking direction
    Z_ = l - p;
    Z_ = glm::normalize(Z_);

    // X axis of camera with given "up" vector and Z axis
    X_ = Z_ * u;
    X_ = glm::normalize(X_);

    // the real "up" vector is the dot product of X and Z
    Y_ = X_ * Z_;
}

bool Frustum::culling(const glm::vec3 &p)
{
    float pcz, pcx, pcy, aux;

    // compute vector from camera position to p
    glm::vec3 v = p - cc_;

    // compute and test the Z coordinate
    pcz = glm::dot(v, -Z_);
    if (pcz > farD_ || pcz < nearD_)
        return false;

    // compute and test the Y coordinate
    pcy = glm::dot(v, Y_);
    aux = pcz * tang_;
    if (pcy > aux || pcy < -aux)
        return false;

    // compute and test the X coordinate
    pcx = glm::dot(v, X_);
    aux = aux * ratio_;
    if (pcx > aux || pcx < -aux)
        return false;

    return true;
}
