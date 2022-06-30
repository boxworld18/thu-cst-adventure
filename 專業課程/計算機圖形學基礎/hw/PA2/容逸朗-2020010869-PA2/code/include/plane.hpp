#ifndef PLANE_H
#define PLANE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// FINISH (PA2): Copy from PA1

class Plane : public Object3D {
public:
    Plane() {
        this->d = 0;
        this->norm = Vector3f(1, 0, 0);
    }

    Plane(const Vector3f &normal, float d, Material *m) : Object3D(m) {
        this->norm = normal;
        this->d = d;
    }

    ~Plane() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        float t1 = -d + Vector3f::dot(norm, r.getOrigin());
        float t2 = Vector3f::dot(norm, r.getDirection());
        if (t2 == 0) return false;
        float t = - t1 / t2;
        if (t <= 0) return false;
        if (t < tmin || t > h.getT()) return false;
        float flag = -1;
        if (t2 < 0) flag = 1;
        h.set(t, material, norm * flag);
        return true;
    }

    void drawGL() override {
        Object3D::drawGL();
        Vector3f xAxis = Vector3f::RIGHT;
        Vector3f yAxis = Vector3f::cross(norm, xAxis);
        xAxis = Vector3f::cross(yAxis, norm);
        const float planeSize = 10.0;
        glBegin(GL_TRIANGLES);
        glNormal3fv(norm);
        glVertex3fv(d * norm + planeSize * xAxis + planeSize * yAxis);
        glVertex3fv(d * norm - planeSize * xAxis - planeSize * yAxis);
        glVertex3fv(d * norm + planeSize * xAxis - planeSize * yAxis);
        glNormal3fv(norm);
        glVertex3fv(d * norm + planeSize * xAxis + planeSize * yAxis);
        glVertex3fv(d * norm - planeSize * xAxis + planeSize * yAxis);
        glVertex3fv(d * norm - planeSize * xAxis - planeSize * yAxis);
        glEnd();
    }

protected:
    Vector3f norm;
    float d;

};

#endif //PLANE_H
		

