#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <glut.h>

// FINISH (PA2): Copy from PA1

class Sphere : public Object3D {
public:
    Sphere() {
        // unit ball at the center
        center = Vector3f(0.0f);
        radius = 1;
    }

    Sphere(const Vector3f &center, float radius, Material *material) : Object3D(material) {
        // 
        this->center = center;
        this->radius = radius;
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        //
        Vector3f Pc = center;
        Vector3f R0 = r.getOrigin();
        Vector3f l = Pc - R0;
        Vector3f Rd = r.getDirection().normalized();
        double l2 = l.squaredLength();
        double tp = Vector3f::dot(l, Rd);
        double d2 = l2 - tp * tp;
        double r2 = radius * radius;
        if (d2 > r2) return false;

        if (l2 < r2) {
            // inside
            double tpi = sqrt(r2 - d2);
            double t = tp + tpi;
            if (t < tmin || t > h.getT()) return false;
            Vector3f n = Rd * t - l;
            h.set(t, material, n.normalized());
            return true;

        } else if (l2 > r2) {
            // outside
            if (tp < 0) return false;           
            
            double tpi = sqrt(r2 - d2);
            double t = tp - tpi;
            if (t < tmin || t > h.getT()) return false;
            Vector3f n = Rd * t - l;
            h.set(t, material, n.normalized());
            return true;

        } else {
            if (tp < 0) return false;
            double t = tp;
            if (t < tmin || t > h.getT()) return false;
            Vector3f n = Rd * t - l;
            h.set(t, material, n.normalized());
            return true;
        }
        
        return false;
    }

    void drawGL() override {
        Object3D::drawGL();
        glMatrixMode(GL_MODELVIEW); glPushMatrix();
        glTranslatef(center.x(), center.y(), center.z());
        glutSolidSphere(radius, 80, 80);
        glPopMatrix();
    }

protected:
    Vector3f center;
    float radius;

};


#endif
