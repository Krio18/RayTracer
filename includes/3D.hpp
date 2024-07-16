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

#include <cmath>

namespace Math {
    class Vector3D {
        public:
            Vector3D();
            Vector3D(double x, double y, double z);
            ~Vector3D() = default;

            double length();
            double length_squared() const;
            double dot(Vector3D v1, Vector3D v2);
            Vector3D unitV(Vector3D v);
            void normalize();

            Vector3D &operator+=(const Vector3D &v);
            Vector3D &operator-=(const Vector3D &v);
            Vector3D &operator*=(const Vector3D &v);
            Vector3D &operator/=(const Vector3D &v);

            Vector3D &operator*=(double scalar);
            Vector3D &operator/=(double scalar);

            double x, y, z;

        private:
    };

    class Point3D {
        public:
            Point3D();
            Point3D(double x, double y, double z);
            ~Point3D() = default;

            Point3D operator+(const Vector3D &v) const;
            double x, y, z;
        private:
    };

    Vector3D operator+(Vector3D f, const Vector3D &s);
    Vector3D operator-(Vector3D f, const Vector3D &s);
    Vector3D operator*(Vector3D f, const Vector3D &s);
    Vector3D operator/(Vector3D f, const Vector3D &s);

    Vector3D operator*(Vector3D v, double scalar);
    Vector3D operator/(Vector3D v, double scalar);
    Vector3D operator-(const Math::Point3D &p, const Vector3D &v);
    Vector3D operator*(const double &d, const Vector3D &v);
    Vector3D operator-(const Vector3D &v, const Math::Point3D &p);
}
