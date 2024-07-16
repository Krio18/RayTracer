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

#include "Raytracer.hpp"
#include <iostream>

namespace Raytracer
{
    /**
     * @brief Construct a new Camera:: Camera object
     * @param width
     * @param height
     */
    Camera::Camera(const int width, const int height)
    {
        _width = width;
        _height = height;
        _focal = 1.0;

        _viewHeight = 2.0;
        _viewWidth = _viewHeight * (double(_width) / _height);
        _viewU = Math::Vector3D(_viewWidth, 0, 0);
        _viewV = Math::Vector3D(0, -_viewHeight, 0);

        this->_deltaU = _viewU / _width;
        this->_deltaV = _viewV / _height;

        _viewUpLeft = origin - Math::Vector3D(0, 0, _focal) - _viewU / 2 - _viewV / 2;
        _originLoc = _viewUpLeft + 0.5 * (this->_deltaU + this->_deltaV);
        this->screen = Rectangle3D(_originLoc, _viewU, _viewV);
    }

    /**
     * @brief
     * @param u
     * @param v
     * @return Math::Vector3D
     */
    Math::Vector3D Camera::ray(Math::Vector3D u, Math::Vector3D v) const
    {
        Math::Vector3D screenPoint = this->screen.pointAt(u, v);
        return (Math::Vector3D(screenPoint - origin));
    }

    /**
     * @brief
     * @return Math::Vector3D
     */
    Math::Vector3D Camera::getDeltaU()
    {
        return this->_deltaU;
    }

    /**
     * @brief
     * @return Math::Vector3D
     */
    Math::Vector3D Camera::getDeltaV()
    {
        return this->_deltaV;
    }

    /**
     * @brief
     * @param p1
     * @param p2
     * @return Math::Vector3D
     */
    Math::Vector3D operator-(const Math::Point3D &p1, const Math::Point3D &p2)
    {
        return Math::Vector3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
    }
}
