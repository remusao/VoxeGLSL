#ifndef FRUSTUM_HH_
# define FRUSTUM_HH_

# include <glm/glm.hpp>

class Frustum
{
    public:
        Frustum() = default;
        ~Frustum() = default;

        void setCamInternals(float angle, float ratio, float nearD, float farD);
        void setCamDef(glm::vec3 p, glm::vec3 l, glm::vec3 u);
        bool culling(const glm::vec3 &p);
    private:
        glm::vec3 cc_; // camera position
        glm::vec3 X_, Y_, Z_; // the camera referential
        float ratio_, nearD_, farD_, width_, height_, tang_;
};

#endif /* !FRUSTUM_HH_ */
