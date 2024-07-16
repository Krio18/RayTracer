/*
-- Raytracer, 2024
--
-- Description:
-- This project is a ray tracing program.
--
-- Contributors:
-- - Killian Cottrelle
-- - Clement Barrier
-- - Sonny Fourmont
*/

#include "../includes/Scene.hpp"

/**
 * @brief
 */
void usage(void)
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
    exit(84);
}


/**
 * @brief
 *
 * @param ac
 * @param av
 * @return int
 */
int main(int ac, char **av)
{
    if ((ac == 1) || (strcmp(av[1], "--help") == 0) || (ac > 2))
        usage();

    Scene scene(av[1]);
    scene.scene();

    return 0;
}

