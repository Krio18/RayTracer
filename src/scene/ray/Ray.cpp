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
 * @brief Construct a new Raytracer:: Ray:: Ray object
 */
Raytracer::Ray::Ray() : _origin(0,0,0), _direction(0,0,0) {}

/**
 * @brief Construct a new Raytracer:: Ray:: Ray object
 * @param origin
 * @param direction
 */
Raytracer::Ray::Ray(Math::Point3D origin, Math::Vector3D direction) : _origin(origin), _direction(direction) {}

#pragma region get/set

/**
 * @brief
 * @return Math::Point3D
 */
Math::Point3D Raytracer::Ray::getOrigin()
{
    return _origin;
}

/**
 * @brief
 * @return Math::Vector3D
 */
Math::Vector3D Raytracer::Ray::getDirection()
{
    return _direction;
}

/**
 * @brief
 * @param p
 */
void Raytracer::Ray::setOrigin(Math::Point3D p)
{
    _origin = p;
}

/**
 * @brief
 * @param v
 */
void Raytracer::Ray::setDirection(Math::Vector3D v)
{
    _direction = v;
}

#pragma endregion get/set

/**
 * @brief
 * @param t
 * @return Math::Point3D
 */
Math::Point3D Raytracer::Ray::pointAt(double t)
{
    return _origin + t * _direction;
}