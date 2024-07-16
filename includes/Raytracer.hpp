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

#include <Rectangle3D.hpp>
#include <IPrimitive.hpp>

#include <libconfig.h++>
#include <vector>
#include <memory>

namespace Raytracer {
    class Ray {
        public:
            Ray();
            Ray(Math::Point3D origin, Math::Vector3D direction);
            ~Ray() = default;

            Math::Point3D getOrigin();
            Math::Vector3D getDirection();
            void setOrigin(Math::Point3D);
            void setDirection(Math::Vector3D);

            Math::Point3D pointAt(double t);
        private:
            Math::Point3D _origin;
            Math::Vector3D _direction;
    };

    class Sphere : public IPrimitive {
        public:
            Sphere();
            Sphere(Math::Point3D center, double radius, Math::Vector3D color);
            ~Sphere() = default;

            Math::Point3D getCenter();
            double getRadius();
            void setCenter(Math::Point3D);
            void setRadius(double);

            bool hits(Ray &ray, double rayTmin, double rayTmax, Record& rec) override;

        private:
            Math::Point3D _center;
            double _radius;
            Math::Vector3D _color;
    };

    class Plane : public IPrimitive {
        public:
            Plane(const Math::Point3D &point, const Math::Vector3D &normal, Math::Vector3D color);
            ~Plane() = default;

            bool hits(Ray &ray, double rayTmin, double rayTmax, Record &reg) override;

        private:
            Math::Point3D _point;
            Math::Vector3D _normal;
            Math::Vector3D _color;
    };

    class Camera {
        public:
            Camera(const int, const int);
            ~Camera() = default;

            Math::Vector3D ray(Math::Vector3D u, Math::Vector3D v) const;

            Math::Vector3D getDeltaU();
            Math::Vector3D getDeltaV();

            Math::Point3D origin;
            Rectangle3D screen;

        private:
            double _width;
            double _height;
            double _focal;
            double _viewHeight;
            double _viewWidth;
            Math::Vector3D _viewU;
            Math::Vector3D _viewV;
            Math::Vector3D _deltaU;
            Math::Vector3D _deltaV;
            Math::Vector3D _viewUpLeft;
            Math::Vector3D _originLoc;
    };

    Math::Vector3D operator-(const Math::Point3D &f, const Math::Point3D &s);
}

class Record {
    public:
        ~Record() = default;

        void setPoint(Math::Point3D p);
        void setNormal(Math::Vector3D v);
        void setT(double d);
        void setFrontFace(bool b);
        void setColor(Math::Vector3D c) {_color = c;}

        Math::Point3D getPoint();
        Math::Vector3D getNormal();
        double getT();
        bool getFrontFace();
        Math::Vector3D getColor() {return _color;}

        void setFaceNormal(Raytracer::Ray& r, Math::Vector3D& outward_normal);
    private:
        Math::Point3D _point;
        Math::Vector3D _normal;
        double _t;
        bool _frontFace;
        Math::Vector3D _color = {1, 1, 1};
};

class objectList : public IPrimitive {
    public:
        objectList();
        ~objectList();

        void add(std::shared_ptr<IPrimitive> object);
        bool hits(Raytracer::Ray &ray, double rayTmin, double rayTmax, Record& rec) override;

        std::vector<std::shared_ptr<IPrimitive>> getObject();
    private:
        std::vector<std::shared_ptr<IPrimitive>> _objects;

};

