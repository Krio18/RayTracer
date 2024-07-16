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

#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <stdlib.h>

#include "3D.hpp"
#include "Parser.hpp"

class Scene {
    public:
        Scene(char *);
        ~Scene() = default;

        void pixelWriter(Math::Vector3D &color);
        Math::Vector3D phongLighting(Record& re, Math::Point3D lightSource, Raytracer::Camera cam);
        Math::Vector3D reflect(Math::Vector3D& incident, Math::Vector3D normal);
        void scene();
    private:
        Parser _parser;
};
