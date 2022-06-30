#ifndef MESH_H
#define MESH_H

#include <vector>
#include "object3d.hpp"
#include "triangle.hpp"
#include "Vector2f.h"
#include "Vector3f.h"


class Mesh : public Object3D {

public:
    Mesh(const char *filename, Material *m);

    struct TriangleIndex {
        TriangleIndex() {
            x[0] = 0; x[1] = 0; x[2] = 0;
        }
        int &operator[](const int i) { return x[i]; }
        // By Computer Graphics convention, counterclockwise winding is front face
        int x[3]{};
    };

    std::vector<Vector3f> v;
    std::vector<TriangleIndex> t;
    std::vector<Vector3f> n;
    bool intersect(const Ray &r, Hit &h, float tmin) override;

    void drawGL() override {
        Object3D::drawGL();
        for (int triId = 0; triId < (int) t.size(); ++triId) {
            TriangleIndex& triIndex = t[triId];
            Triangle triangle(v[triIndex[0]],
                              v[triIndex[1]], v[triIndex[2]], material);
            triangle.normal = n[triId];
            triangle.drawGL();
        }
    }

private:

    // Normal can be used for light estimation
    void computeNormal();
};

#endif
