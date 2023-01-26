#ifndef PLANE_H
#define PLANE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement Plane representing an infinite plane
// function: ax+by+cz=d
// choose your representation , add more fields and fill in the functions

class Plane : public Object3D {
public:
    Plane() {
        this->d = 0;
        this->normal = Vector3f(1, 0, 0);
    }

    Plane(const Vector3f &normal, float d, Material *m) : Object3D(m) {
        this->normal = normal;
        this->d = d;
    }

    ~Plane() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        float t1 = -d + Vector3f::dot(normal, r.getOrigin());
        float t2 = Vector3f::dot(normal, r.getDirection());
        if (t2 == 0) return false;
        float t = - t1 / t2;
        if (t <= 0) return false;
        if (t < tmin || t > h.getT()) return false;
        float flag = -1;
        if (t2 < 0) flag = 1;
        h.set(t, material, normal * flag);
        return true;
    }


protected:
    Vector3f normal;
    float d;
};

#endif //PLANE_H
		

