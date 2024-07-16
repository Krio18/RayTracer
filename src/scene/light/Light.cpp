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

#include "Light.hpp"

/**
 * @brief Construct a new Light:: Light object
 * @param cam
 * @param lightSource
 * @param ambient
 * @param diffuse
 */
Light::Light(Raytracer::Camera cam, Math::Point3D lightSource, double ambient, double diffuse) : _cam(cam) , _lightSource(lightSource), _ambient(ambient) , _diffuse(diffuse) {}

/**
 * @brief
 * @param re
 * @param lightSource
 * @return Math::Vector3D
 */
Math::Vector3D Light::phongLighting(Record& re, Math::Point3D lightSource)
{
    double kspecular = 0.2;

    Math::Vector3D lightColor(-0.5, -0.5, -0.5);
    Math::Vector3D lightDir(lightSource.x - re.getPoint().x, lightSource.y - re.getPoint().y, lightSource.z - re.getPoint().z);

    double distanceToLight = lightDir.length();
    lightDir.normalize();

    double attenuation = 1.0 / (distanceToLight * distanceToLight);
    double diffuse = _diffuse * std::max(0.0, re.getNormal().dot(re.getNormal(), lightDir));
    Math::Vector3D reflection = reflect(lightDir, re.getNormal());
    Math::Vector3D viewDir(_cam.origin.x - re.getPoint().x, _cam.origin.y - re.getPoint().y, _cam.origin.z - re.getPoint().z);
    double specular = kspecular * std::pow(std::max(0.0, viewDir.dot(viewDir, reflection)), 8);

    lightColor *= attenuation;
    Math::Vector3D finalColor = re.getColor() * ( _ambient + diffuse) + lightColor * specular;

    return finalColor;
}

/**
 * @brief
 * @param incident
 * @param normal
 * @return Math::Vector3D
 */
Math::Vector3D Light::reflect(Math::Vector3D& incident, Math::Vector3D normal)
{
    return incident - 2 * incident.dot(incident, normal) * normal;
}

