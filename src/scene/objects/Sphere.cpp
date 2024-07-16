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

#include "../../../includes/Raytracer.hpp"

/**
 * @brief Construct a new Raytracer:: Sphere:: Sphere object
 */
Raytracer::Sphere::Sphere() : _center(0,0,0), _radius(0.5) {}

/**
 * @brief Construct a new Raytracer:: Sphere:: Sphere object
 * @param center
 * @param radius
 * @param color
 */
Raytracer::Sphere::Sphere(Math::Point3D center, double radius, Math::Vector3D color) : _center(center), _radius(radius), _color(color) {}

#pragma region get/set

/**
 * @brief
 * @return Math::Point3D
 */
Math::Point3D Raytracer::Sphere::getCenter()
{
    return _center;
}

/**
 * @brief
 * @return double
 */
double Raytracer::Sphere::getRadius()
{
    return _radius;
}

/**
 * @brief
 * @param p
 */
void Raytracer::Sphere::setCenter(Math::Point3D p)
{
    _center = p;
}

/**
 * @brief
 * @param d
 */
void Raytracer::Sphere::setRadius(double d)
{
    _radius = d;
}

#pragma endregion get/set

/**
 * @brief
 * @param ray
 * @param rayTmin
 * @param rayTmax
 * @param re
 * @return true
 * @return false
 */
bool Raytracer::Sphere::hits(Raytracer::Ray &ray, double rayTmin, double rayTmax, Record& re)
{
    Math::Vector3D origineCenter = (_center - ray.getOrigin());
    double a = ray.getDirection().length_squared();
    double b = ray.getDirection().dot(ray.getDirection(), origineCenter);
    double c = origineCenter.length_squared() - this->_radius * this->_radius;

    double discriminant = (b * b - a * c);

    if (discriminant < 0)
        return false;

    double sqrtD = std::sqrt(discriminant);

    double root = (b - sqrtD) / a;
    if (root <= rayTmin || rayTmax <= root) {
        root = (b + sqrtD) / a;
        if (root <= rayTmin || rayTmax <= root)
            return false;
    }

    re.setT(root);
    re.setPoint(ray.pointAt(re.getT()));
    Math::Vector3D outwardNormal = (re.getPoint() - this->_center) / this->_radius;
    re.setFaceNormal(ray, outwardNormal);
    re.setColor((_color * 2) / 1000);

    return true;
}
