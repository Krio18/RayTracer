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

#include "../../../includes/Raytracer.hpp"

#pragma region record

#pragma region get/set

/**
 * @brief
 * @param p
 */
void Record::setPoint(Math::Point3D p)
{
    _point = p;
}

/**
 * @brief
 * @param v
 */
void Record::setNormal(Math::Vector3D v)
{
    _normal = v;
}

/**
 * @brief
 * @param d
 */
void Record::setT(double d)
{
    _t = d;
}

/**
 * @brief
 * @param b
 */
void Record::setFrontFace(bool b)
{
    _frontFace = b;
}

/**
 * @brief
 * @return Math::Point3D
 */
Math::Point3D Record::getPoint()
{
    return _point;
}

/**
 * @brief
 * @return Math::Vector3D
 */
Math::Vector3D Record::getNormal()
{
    return _normal;
}

/**
 * @brief
 * @return double
 */
double Record::getT()
{
    return _t;
}

/**
 * @brief
 * @return true
 * @return false
 */
bool Record::getFrontFace()
{
    return _frontFace;
}

#pragma endregion get/set

/**
 * @brief
 * @param r
 * @param outward_normal
 */
void Record::setFaceNormal(Raytracer::Ray& r, Math::Vector3D& outward_normal)
{
    _frontFace = false;
    _normal = outward_normal * -1.0;

    if (outward_normal.dot(r.getDirection(), outward_normal) < 0)
        _frontFace = true;
    if (_frontFace == true)
        _normal = outward_normal;
}

#pragma endregion record

#pragma region list

/**
 * @brief Construct a new object List::object List object
 */
objectList::objectList() {}

/**
 * @brief Destroy the object List::object List object
 */
objectList::~objectList() {_objects.clear();}

#pragma region get/set

/**
 * @brief
 * @return std::vector<std::shared_ptr<IPrimitive>>
 */
std::vector<std::shared_ptr<IPrimitive>> objectList::getObject()
{
    return _objects;
}

#pragma endregion get/set

/**
 * @brief
 * @param object
 */
void objectList::add(std::shared_ptr<IPrimitive> object)
{
    _objects.push_back(object);
}

/**
 * @brief
 * @param ray
 * @param rayTmin
 * @param rayTmax
 * @param rec
 * @return true
 * @return false
 */
bool objectList::hits(Raytracer::Ray &ray, double rayTmin, double rayTmax, Record& rec)
{
    Record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = rayTmax;

    for (const auto& object : _objects) {
        if (object->hits(ray, rayTmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.getT();
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#pragma endregion list