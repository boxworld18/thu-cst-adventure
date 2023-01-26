#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>

// TODO: Implement Shade function that computes Phong introduced in class.
class Material {
public:

    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, float s = 0) :
            diffuseColor(d_color), specularColor(s_color), shininess(s) {

    }

    virtual ~Material() = default;

    virtual Vector3f getDiffuseColor() const {
        return diffuseColor;
    }

    double clamp(Vector3f a, Vector3f b) {
        double ans = Vector3f::dot(a, b);
        if (ans < 0) ans = 0;
        return ans;
    }

    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor) {
        Vector3f shaded = Vector3f::ZERO;
        // 
        Vector3f N = hit.getNormal();
        Vector3f Li = dirToLight;
        Vector3f V = -ray.getDirection();
        Vector3f R = 2 * Vector3f::dot(N, Li) * N - Li; 
        shaded += diffuseColor * clamp(Li, N);
        shaded += specularColor * pow(clamp(V, R), shininess);
        return shaded * lightColor;
    }

protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
};


#endif // MATERIAL_H
