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

#include "../../../includes/3D.hpp"

/**
 * @brief Construct a new Math::Point3D::Point3D object
 */
Math::Point3D::Point3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

/**
 * @brief Construct a new Math::Point3D::Point3D object
 * @param x
 * @param y
 * @param z
 */
Math::Point3D::Point3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * @brief
 * @param v
 * @return Math::Point3D
 */
Math::Point3D Math::Point3D::operator+(const Math::Vector3D &v) const {
    return Point3D(x + v.x, y + v.y, z + v.z);
}