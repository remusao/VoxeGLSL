#include <iostream>
#include "voxelEngine.hh"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << argv[0] << " heightmap.png" << std::endl;
        return -1;
    }

    VoxelEngine engine("Voxel", 1920, 1080);

    // Populate world
    engine.populate([argv](World& world)
    {
        sf::Image img;
        img.loadFromFile(argv[1]);
        sf::Vector2u size = img.getSize();

        auto lowest = [&img](unsigned i, unsigned j, unsigned z)
        {
            int neighbor[4][2] =
            {
                {1, 0},
                {0, 1},
                {-1, 0},
                {0, -1}
            };
            unsigned min = z;
            for (int n = 0; n < 4; ++n)
            {
                if (min > img.getPixel(i + neighbor[n][0], j + neighbor[n][1]).r)
                {
                    min = img.getPixel(i + neighbor[n][0], j + neighbor[n][1]).r;
                }
            }
            return min;
        };

        for (unsigned i = 1; i < (size.x - 1); ++i)
        {
            for (unsigned j = 1; j < (size.y - 1); ++j)
            {
                unsigned height = img.getPixel(i, j).r;
                unsigned low = lowest(i, j, height);
                for (unsigned z = low; z <= height; ++z)
                {
                    world.addVoxel(Voxel(i, z, j));
                }
            }
        }
    });


    // Modifies world if required
    // -> true: redraw world
    // -> false: keep previous world
    engine.loop([](World&) -> bool
    {
        return false;
    });

    return 0;
}
