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

namespace Raytracer {
    class Ray;
}
class Record;

class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        virtual bool hits(Raytracer::Ray &ray, double rayTmin, double rayTmax, Record& rec) = 0;
    private:
};
