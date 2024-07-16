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

class Rectangle3D {
    public:
        Rectangle3D();
        Rectangle3D(const Math::Vector3D &origin, const Math::Vector3D &bottomSide, const Math::Vector3D &leftSide);
        ~Rectangle3D() = default;

        Math::Vector3D getOrigin();
        Math::Vector3D getBottomSide();
        Math::Vector3D getLeftSide();
        void setOrigin(Math::Vector3D);
        void setBottomSide(Math::Vector3D);
        void setLeftSide(Math::Vector3D);

        Math::Vector3D pointAt(Math::Vector3D u, Math::Vector3D v) const;

    private:
        Math::Vector3D _origin;
        Math::Vector3D _bottomSide;
        Math::Vector3D _leftSide;
};
