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
 * @brief Construct a new Math::Vector3D::Vector3D object
 */
Math::Vector3D::Vector3D()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

/**
 * @brief Construct a new Math::Vector3D::Vector3D object
 * @param x
 * @param y
 * @param z
 */
Math::Vector3D::Vector3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * @brief
 * @return double
 */
double Math::Vector3D::length()
{
    return std::sqrt(length_squared());
}

/**
 * @brief
 * @param v1
 * @param v2
 * @return double
 */
double Math::Vector3D::dot(Vector3D v1, Vector3D v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

/**
 * @brief
 * @return double
 */
double Math::Vector3D::length_squared() const
{
    return (x * x) + (y * y) + (z * z);
}

/**
 * @brief
 * @param v
 * @return Math::Vector3D
 */
Math::Vector3D Math::Vector3D::unitV(Vector3D v)
{
    return v / v.length();
}

/**
 * @brief
 */
void Math::Vector3D::normalize() {
    double length = std::sqrt(x * x + y * y + z * z);
    if (length != 0.0) {
        x /= length;
        y /= length;
        z /= length;
    }
}

#pragma region operator

/**
 * @brief
 * @param v
 * @return Math::Vector3D&
 */
Math::Vector3D &Math::Vector3D::operator+=(const Math::Vector3D &v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
}

/**
 * @brief
 * @param v
 * @return Math::Vector3D&
 */
Math::Vector3D &Math::Vector3D::operator-=(const Math::Vector3D &v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return *this;
}

/**
 * @brief
 * @param v
 * @return Math::Vector3D&
 */
Math::Vector3D &Math::Vector3D::operator*=(const Math::Vector3D &v)
{
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
    return *this;
}

/**
 * @brief
 * @param v
 * @return Math::Vector3D&
 */
Math::Vector3D &Math::Vector3D::operator/=(const Math::Vector3D &v)
{
    this->x /= v.x;
    this->y /= v.y;
    this->z /= v.z;
    return *this;
}

/**
 * @brief
 * @param scalar
 * @return Math::Vector3D&
 */
Math::Vector3D &Math::Vector3D::operator*=(double scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

/**
 * @brief
 * @param scalar
 * @return Math::Vector3D&
 */
Math::Vector3D &Math::Vector3D::operator/=(double scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

/**
 * @brief
 * @param v1
 * @param v2
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator+(Math::Vector3D v1, const Math::Vector3D &v2)
{
    v1 += v2;
    return v1;
}

/**
 * @brief
 * @param v1
 * @param v2
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator-(Math::Vector3D v1, const Math::Vector3D &v2)
{
    v1 -= v2;
    return v1;
}

/**
 * @brief
 * @param v1
 * @param v2
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator*(Math::Vector3D v1, const Math::Vector3D &v2)
{
    v1 *= v2;
    return v1;
}

/**
 * @brief
 * @param v1
 * @param v2
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator/(Math::Vector3D v1, const Math::Vector3D &v2)
{
    v1 /= v2;
    return v1;
}

/**
 * @brief
 * @param v1
 * @param v2
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator*(Math::Vector3D v1, double v2)
{
    v1 *= v2;
    return v1;
}

/**
 * @brief
 * @param v1
 * @param v2
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator/(Math::Vector3D v1, double v2)
{
    v1 /= v2;
    return v1;
}

/**
 * @brief
 * @param p
 * @param v
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator-(const Math::Point3D &p, const Math::Vector3D &v)
{
    return Math::Vector3D(p.x - v.x, p.y - v.y, p.z - v.z);
}

/**
 * @brief
 * @param d
 * @param v
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator*(const double &d, const Math::Vector3D &v)
{
    return Math::Vector3D(d * v.x, d * v.y, d * v.z);
}

/**
 * @brief
 * @param v
 * @param p
 * @return Math::Vector3D
 */
Math::Vector3D Math::operator-(const Math::Vector3D &v, const Math::Point3D &p)
{
    return Math::Vector3D(v.x - p.x, v.y - p.y, v.z - p.z);
}

#pragma endregion rejet

