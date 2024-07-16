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

#include "../../../includes/Rectangle3D.hpp"

/**
 * @brief Construct a new Rectangle 3D::Rectangle3D object
 */
Rectangle3D::Rectangle3D() : _origin(0,0,0), _bottomSide(1,0,0), _leftSide(0,1,0) {}

/**
 * @brief Construct a new Rectangle 3D::Rectangle3D object
 * @param origin
 * @param bottomSide
 * @param leftSide
 */
Rectangle3D::Rectangle3D(const Math::Vector3D &origin, const Math::Vector3D &bottomSide, const Math::Vector3D &leftSide)
: _origin(origin), _bottomSide(bottomSide), _leftSide(leftSide) {}

#pragma region get/set

/**
 * @brief
 * @return Math::Vector3D
 */
Math::Vector3D Rectangle3D::getOrigin()
{
    return _origin;
}

/**
 * @brief
 * @return Math::Vector3D
 */
Math::Vector3D Rectangle3D::getBottomSide()
{
    return _bottomSide;
}

/**
 * @brief
 * @return Math::Vector3D
 */
Math::Vector3D Rectangle3D::getLeftSide()
{
    return _leftSide;
}

/**
 * @brief
 * @param v
 */
void Rectangle3D::setOrigin(Math::Vector3D v)
{
    _origin = v;
}

/**
 * @brief
 * @param v
 */
void Rectangle3D::setBottomSide(Math::Vector3D v)
{
    _bottomSide = v;
}

/**
 * @brief
 * @param v
 */
void Rectangle3D::setLeftSide(Math::Vector3D v)
{
    _leftSide = v;
}

#pragma endregion get/set

/**
 * @brief
 * @param u
 * @param v
 * @return Math::Vector3D
 */
Math::Vector3D Rectangle3D::pointAt(Math::Vector3D u, Math::Vector3D v) const
{
    return this->_origin + v + u;
}
