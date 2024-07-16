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

#include "../../includes/Scene.hpp"

/**
 * @brief Construct a new Scene:: Scene object
 * @param file
 */
Scene::Scene(char *file) : _parser(file)
{
    if (_parser.openConfig() == 1)
        exit(84);
}

/**
 * @brief
 * @param color
 */
void Scene::pixelWriter(Math::Vector3D &color)
{
    int r = static_cast<int>(255.999 * color.x);
    int g = static_cast<int>(255.999 * color.y);
    int b = static_cast<int>(255.999 * color.z);
    std::cout << r << " " << g << " " << b << "\n";
}

/**
 * @brief
 */
void Scene::scene()
{
    const int width = _parser.getCameraWidth();
    const int height = _parser.getCameraHeight();

    Raytracer::Camera cam(width, height);

    std::vector<Raytracer::Sphere> sphereVector(_parser.getSpheres());
    std::vector<Raytracer::Plane> planeVector(_parser.getPlanes());
    std::vector<Light> lightVector(_parser.getLights(cam));

    objectList world;

    for (const auto &sphere : sphereVector)
        world.add(std::make_shared<Raytracer::Sphere>(sphere));
    for (const auto &plane : planeVector)
        world.add(std::make_shared<Raytracer::Plane>(plane));

    Math::Point3D lightSource(0, 2, 2);

    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (double j = 0; j < height; j++) {
        for (double i = 0; i < width; i++) {
            Math::Vector3D pixel_color;
            Math::Vector3D r_Direction = cam.ray((i * cam.getDeltaU()), (j * cam.getDeltaV()));
            Raytracer::Ray r(cam.origin, r_Direction);

            Record re;
            if (world.hits(r, 0, 2147483647, re)) {
                Math::Vector3D Light(lightSource.x - re.getPoint().x, lightSource.y - re.getPoint().y, lightSource.z - re.getPoint().z);
                Raytracer::Ray shadowRay(re.getPoint(), Light);

                Record shadowRe;
                if (world.hits(shadowRay, 0.001, std::numeric_limits<double>::infinity(), shadowRe))
                    pixel_color = re.getColor() * 0.1;
                else
                    for (long unsigned int i = 0; i < lightVector.size(); i++)
                        pixel_color = lightVector[i].phongLighting(re, lightSource);
            } else
                pixel_color = Math::Vector3D(0.4160, 0.5300, 0.9500);

            pixelWriter(pixel_color);
        }
    }
}
