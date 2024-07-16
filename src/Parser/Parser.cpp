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

#include "../../includes/Parser.hpp"

/**
 * @brief Construct a new Parser:: Parser object
 * @param path
 */
Parser::Parser(char *path)
{
    _path = path;
}

/**
 * @brief Config
 * @return int
 */
int Parser::openConfig()
{
    try {
        _cfg.readFile(_path);
    }
    catch(const libconfig::FileIOException &fileIOExcept) {
        std::cerr << "I/O error while reading file. File not found" << std::endl;
        return EXIT_FAILURE;
    }
    catch(const libconfig::ParseException &parseExcept) {
        std::cerr << "Parse error at " << parseExcept.getFile() << ":"
        << parseExcept.getLine() << " - " << parseExcept.getError() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Camera Height
 * @return double
 */
double Parser::getCameraHeight()
{
    int height = 10;

    if (_cfg.exists("camera"))
        if ((_cfg.exists("camera.resolution") && (_cfg.exists("camera.resolution.height")))) {
            _cfg.lookupValue("camera.resolution.height", height);
        } else
            return EXIT_FAILURE;
    else
        return EXIT_FAILURE;
    return height;
}

/**
 * @brief Camera Width
 * @return double
 */
double Parser::getCameraWidth()
{
    int width = 0;

    if (_cfg.exists("camera"))
        if ((_cfg.exists("camera.resolution") && (_cfg.exists("camera.resolution.width")))) {
            _cfg.lookupValue("camera.resolution.width", width);
        } else
            return EXIT_FAILURE;
    else
        return EXIT_FAILURE;
    return width;
}

/**
 * @brief Camera Position
 * @return Math::Point3D
 */
Math::Point3D Parser::getCameraPosition()
{
    Math::Point3D point;

    if (_cfg.exists("camera"))
        if ((_cfg.exists("camera.position")) && (_cfg.exists("camera.position.x"))
        && (_cfg.exists("camera.position.y")) && (_cfg.exists("camera.position.z"))) {
            _cfg.lookupValue("camera.position.x", point.x);
            _cfg.lookupValue("camera.position.y", point.y);
            _cfg.lookupValue("camera.position.z", point.z);
        }
    return point;
}

/**
 * @brief Camera Rotation
 * @return Math::Vector3D
 */
Math::Vector3D Parser::getCameraRotation()
{
    Math::Vector3D vector;

    if (_cfg.exists("camera"))
        if ((_cfg.exists("camera.rotation")) && (_cfg.exists("camera.rotation.x"))
        && (_cfg.exists("camera.rotation.y")) && (_cfg.exists("camera.rotation.z"))) {
            _cfg.lookupValue("camera.rotation.x", vector.x);
            _cfg.lookupValue("camera.rotation.y", vector.y);
            _cfg.lookupValue("camera.rotation.z", vector.z);
        }
    return vector;

}

/**
 * @brief Camera FOV
 * @return double
 */
double Parser::getCameraFOV()
{
    double FOV = 0;

    if (_cfg.exists("camera"))
        if (_cfg.exists("camera.fieldOfView")) {
            _cfg.lookupValue("camera.fieldOfView", FOV);
        } else
            return EXIT_FAILURE;
    else
        return EXIT_FAILURE;
    return FOV;

}

/**
 * @brief Get the Sphere Infos object
 * @param sphere
 * @param i
 * @return Raytracer::Sphere
 */
static Raytracer::Sphere getSphereInfos(libconfig::Setting &sphere, int i)
{
    Math::Point3D pos;
    double radius = 0;
    Math::Vector3D color;

    if ((sphere[i].exists("x")) && (sphere[i].exists("y")) && (sphere[i].exists("z"))) {
        sphere[i].lookupValue("x", pos.x);
        sphere[i].lookupValue("y", pos.y);
        sphere[i].lookupValue("z", pos.z);
    } if (sphere[i].exists("r")) {
        sphere[i].lookupValue("r", radius);
    } if ((sphere[i].exists("color")) && (sphere[i].exists("color.r"))
    && (sphere[i].exists("color.g")) && (sphere[i].exists("color.b"))) {
        color.x = sphere[i].lookup("color.r");
        color.y = sphere[i].lookup("color.g");
        color.z = sphere[i].lookup("color.b");
    }
    return Raytracer::Sphere(pos, radius, color);
}

/**
 * @brief
 * @return std::vector<Raytracer::Sphere>
 */
std::vector<Raytracer::Sphere> Parser::getSpheres()
{
    std::vector<Raytracer::Sphere> spheresVector;
    libconfig::Setting& root = _cfg.getRoot();

    if (_cfg.exists("primitives")) {
        if (_cfg.exists("primitives.spheres")) {
            libconfig::Setting &spheres = root["primitives"]["spheres"];
            for (int i = 0; i != spheres.getLength(); i++)
                spheresVector.push_back(getSphereInfos(spheres, i));
        }
    }
    return spheresVector;
}

/**
 * @brief Get the Planes Infos object
 * @param planes
 * @param i
 * @return Raytracer::Plane
 */
static Raytracer::Plane getPlanesInfos(libconfig::Setting &planes, int i)
{
    Math::Point3D pos;
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D color;
    std::string axis;

    if (planes[i].exists("axis")) {
        planes[i].lookupValue("axis", axis);
        if ((axis == "x" || axis == "X") && (planes[i].exists("position"))) {
            planes[i].lookupValue("position", pos.x);
        } else if ((axis == "y" || axis == "Y") && (planes[i].exists("position"))) {
            planes[i].lookupValue("position", pos.z);
        } else if ((axis == "z" || axis == "Z") && (planes[i].exists("position"))) {
            planes[i].lookupValue("position", pos.y);
        }
    }  if ((planes[i].exists("color")) && (planes[i].exists("color.r"))
    && (planes[i].exists("color.g")) && (planes[i].exists("color.b"))) {
        color.x = planes[i].lookup("color.r");
        color.y = planes[i].lookup("color.g");
        color.z = planes[i].lookup("color.b");
    }

    return Raytracer::Plane(pos, normal, color);
}

/**
 * @brief
 * @return std::vector<Raytracer::Plane>
 */
std::vector<Raytracer::Plane> Parser::getPlanes()
{
    std::vector<Raytracer::Plane> planesVector;
    libconfig::Setting& root = _cfg.getRoot();

    if (_cfg.exists("primitives")) {
        if (_cfg.exists("primitives.planes")) {
            libconfig::Setting &planes = root["primitives"]["planes"];
            for (int i = 0; i != planes.getLength(); i++)
                planesVector.push_back(getPlanesInfos(planes, i));
        }
    }
    return planesVector;
}

/**
 * @brief
 * @return double
 */
double Parser::getAmbientLights()
{
    double ambientLights = 0;

    if (_cfg.exists("lights")) {
        if (_cfg.exists("lights.ambient")) {
            _cfg.lookupValue("lights.ambient", ambientLights);
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
    return ambientLights;
}

/**
 * @brief
 * @return double
 */
double Parser::getDiffuseLights()
{
    double diffuseLights = 0;

    if (_cfg.exists("lights")) {
        if (_cfg.exists("lights.diffuse")) {
            _cfg.lookupValue("lights.diffuse", diffuseLights);
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
    return diffuseLights;
}

/**
 * @brief Get the Lights Points Infos object
 * @param points
 * @param i
 * @return Math::Point3D
 */
Math::Point3D getLightsPointsInfos(libconfig::Setting &points, int i)
{
    Math::Point3D pos;

    if ((points[i].exists("x")) && (points[i].exists("y")) && (points[i].exists("z"))) {
        points[i].lookupValue("x", pos.x);
        points[i].lookupValue("y", pos.y);
        points[i].lookupValue("z", pos.z);
    }
    return pos;
}

/**
 * @brief
 * @return std::vector<Math::Point3D>
 */
std::vector<Math::Point3D> Parser::getLightsPoints()
{
    std::vector<Math::Point3D> point3DVector;
    libconfig::Setting& root = _cfg.getRoot();

    if (_cfg.exists("lights")) {
        if (_cfg.exists("lights.point")) {
            libconfig::Setting &points = root["lights"]["point"];
            for (int i = 0; i != points.getLength(); i++)
                point3DVector.push_back(getLightsPointsInfos(points, i));
        }
    }
    return point3DVector;
}

/**
 * @brief Get the Directional Lights Infos object
 * @param points
 * @param i
 * @return Math::Vector3D
 */
Math::Vector3D getDirectionalLightsInfos(libconfig::Setting &points, int i)
{
    Math::Vector3D pos;

    if ((points[i].exists("x")) && (points[i].exists("y")) && (points[i].exists("z"))) {
        points[i].lookupValue("x", pos.x);
        points[i].lookupValue("y", pos.y);
        points[i].lookupValue("z", pos.z);
    }
    return pos;
}

/**
 * @brief
 * @return std::vector<Math::Vector3D>
 */
std::vector<Math::Vector3D> Parser::getDirectionalLights()
{
    std::vector<Math::Vector3D> vector3DVector;
    libconfig::Setting& root = _cfg.getRoot();

    if (_cfg.exists("lights")) {
        if (_cfg.exists("lights.directional")) {
            libconfig::Setting &points = root["lights"]["directional"];
            for (int i = 0; i != points.getLength(); i++)
                vector3DVector.push_back(getDirectionalLightsInfos(points, i));
        }
    }
    return vector3DVector;
}

/**
 * @brief
 * @param cam
 * @param lights
 * @param i
 * @return Light
 */
Light Parser::getLightsInfos(Raytracer::Camera cam, libconfig::Setting &lights, int i)
{
    Math::Point3D pos;

    if ((lights[i].exists("x")) && (lights[i].exists("y")) && (lights[i].exists("z"))) {
        lights[i].lookupValue("x", pos.x);
        lights[i].lookupValue("y", pos.y);
        lights[i].lookupValue("z", pos.z);
    }
    return Light(cam, pos, getAmbientLights(), getDiffuseLights());
}

/**
 * @brief
 * @param cam
 * @return std::vector<Light>
 */
std::vector<Light> Parser::getLights(Raytracer::Camera cam)
{
    std::vector<Light> lightsVector;
    libconfig::Setting& root = _cfg.getRoot();

    if (_cfg.exists("lights")) {
        if (_cfg.exists("lights.point")) {
            libconfig::Setting &lights = root["lights"]["point"];
            for (int i = 0; i != lights.getLength(); i++)
                lightsVector.push_back(getLightsInfos(cam, lights, i));
        }
    }

    return lightsVector;
}
