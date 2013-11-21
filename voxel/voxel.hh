#ifndef VOXEL_HH_
# define VOXEL_HH_

# include <glm/glm.hpp>

class Voxel
{
    public:
        Voxel(const glm::vec3& pos)
            : pos_(pos)
        {
        }

        Voxel(float x, float y, float z)
            : pos_(glm::vec3(x, y, z))
        {
        }

        ~Voxel() = default;

        // Getters
        glm::vec3 getPos() const { return pos_; }
        float getx() const { return pos_.x; }
        float gety() const { return pos_.y; }
        float getz() const { return pos_.z; }

        // Setters
        void setPos(const glm::vec3& pos) { pos_ = pos; }

    private:
        glm::vec3 pos_;
};

#endif /* !VOXEL_HH_ */
