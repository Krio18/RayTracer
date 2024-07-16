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

namespace Raytracer {

    /**
     * @brief Construct a new Plane:: Plane object
     * @param point
     * @param length
     */
    Plane::Plane(const Math::Point3D &point, const Math::Vector3D &normal, Math::Vector3D color)
    {
        this->_point = point;
        this->_normal = normal;
        this->_color = color;
    }

    /**
     * @brief
     * @param ray
     * @param rayTmin
     * @param rayTmax
     * @param re
     * @return true
     * @return false
     */
    bool Plane::hits(Ray& ray, double rayTmin, double rayTmax, Record& re)
    {
        Math::Vector3D rayToPlane(this->_point.x - ray.getOrigin().x,
                                  this->_point.y - ray.getOrigin().y,
                                  this->_point.z - ray.getOrigin().z);
        double dotProduct = ray.getDirection().dot(ray.getDirection(), this->_normal);
        if (std::fabs(dotProduct) < 1e-6) {
            double dotPerpendicular = rayToPlane.dot(rayToPlane, this->_normal);
            return std::fabs(dotPerpendicular) < 1e-6;
        }
        double t = rayToPlane.dot(rayToPlane, this->_normal) / dotProduct;
        if (t < rayTmin || t > rayTmax)
            return false;
        re.setT(t);
        re.setPoint(ray.pointAt(re.getT()));

        re.setFaceNormal(ray, this->_normal);
        re.setColor(_color / 1000);

        return true;
    }
}
