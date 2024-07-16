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

#include <libconfig.h++>
#include <ostream>
#include <iostream>
#include <vector>
#include "3D.hpp"
#include "Raytracer.hpp"
#include "Light.hpp"

class Parser {
    public:
        Parser(char *path);
        ~Parser() = default;

        int openConfig();
        double getCameraFOV();
        double getCameraHeight();
        double getCameraWidth();
        Math::Point3D getCameraPosition();
        Math::Vector3D getCameraRotation();
        std::vector<Raytracer::Sphere> getSpheres();
        std::vector<Raytracer::Plane> getPlanes();
        double getAmbientLights();
        double getDiffuseLights();
        std::vector<Math::Point3D> getLightsPoints();
        std::vector<Math::Vector3D> getDirectionalLights();
        std::vector<Light> getLights(Raytracer::Camera cam);
        Light getLightsInfos(Raytracer::Camera cam, libconfig::Setting &lights, int i);

    private:
        const char *_path;
        libconfig::Config _cfg;
};
