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

#pragma once

#include "3D.hpp"
#include "Raytracer.hpp"

class Light {
    public:
        Light(Raytracer::Camera cam, Math::Point3D lightSource, double ambient, double diffuse);
        ~Light() = default;

        Math::Vector3D phongLighting(Record& re, Math::Point3D lightSource);
        Math::Vector3D reflect(Math::Vector3D& incident, Math::Vector3D normal);

    private:
        Raytracer::Camera _cam;
        Math::Point3D _lightSource;
        double _ambient;
        double _diffuse;
};
