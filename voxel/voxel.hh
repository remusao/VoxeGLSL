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
        glm::vec3 pos() const { return pos_; }

        // Setters
        void pos(const glm::vec3& pos) { pos_ = pos; }

    private:
        glm::vec3 pos_;
};

#endif /* !VOXEL_HH_ */
