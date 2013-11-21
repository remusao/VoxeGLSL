#ifndef WORLD_HH_
# define WORLD_HH_

# include <vector>
# include "voxel.hh"

class World
{
    public:
        World() = default;
        ~World() = default;

        void draw()const
        {
            for (const Voxel& v: voxels_)
            {
                drawVoxel(v);
            }
        }

        void addVoxel(const Voxel& vox)
        {
            voxels_.push_back(vox);
        }

    private:

        void drawVoxel(const Voxel&) const
        {
        }

        std::vector<Voxel> voxels_;
};

#endif /* !WORLD_HH_ */
