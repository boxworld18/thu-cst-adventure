#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

#include <cassert>
#include <vecmath.h>

class Camera;
class Light;
class Material;
class Object3D;
class Group;
class Sphere;
class Plane;
class Triangle;
class Transform;
class Mesh;

#define MAX_PARSER_TOKEN_LENGTH 1024

class SceneParser {
public:

    SceneParser() = delete;
    SceneParser(const char *filename);

    ~SceneParser();

    Camera *getCamera() const {
        return camera;
    }

    Vector3f getBackgroundColor() const {
        return background_color;
    }

    int getNumLights() const {
        return num_lights;
    }

    Light *getLight(int i) const {
        assert(i >= 0 && i < num_lights);
        return lights[i];
    }

    int getNumMaterials() const {
        return num_materials;
    }

    Material *getMaterial(int i) const {
        assert(i >= 0 && i < num_materials);
        return materials[i];
    }

    Group *getGroup() const {
        return group;
    }

private:

    void parseFile();
    void parsePerspectiveCamera();
    void parseBackground();
    void parseLights();
    Light *parsePointLight();
    Light *parseDirectionalLight();
    void parseMaterials();
    Material *parseMaterial();
    Object3D *parseObject(char token[MAX_PARSER_TOKEN_LENGTH]);
    Group *parseGroup();
    Sphere *parseSphere();
    Plane *parsePlane();
    Triangle *parseTriangle();
    Mesh *parseTriangleMesh();
    Transform *parseTransform();

    int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);

    Vector3f readVector3f();

    float readFloat();
    int readInt();

    FILE *file;
    Camera *camera;
    Vector3f background_color;
    int num_lights;
    Light **lights;
    int num_materials;
    Material **materials;
    Material *current_material;
    Group *group;
};

#endif // SCENE_PARSER_H
