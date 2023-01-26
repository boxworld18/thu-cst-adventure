#ifndef CURVE_HPP
#define CURVE_HPP

#include "object3d.hpp"
#include <vecmath.h>
#include <vector>
#include <utility>

#include <algorithm>

// TODO (PA2): Implement Bernstein class to compute spline basis function.
//       You may refer to the python-script for implementation.

// The CurvePoint object stores information about a point on a curve
// after it has been tesselated: the vertex (V) and the tangent (T)
// It is the responsiblility of functions that create these objects to fill in all the data.
struct CurvePoint {
    Vector3f V; // Vertex
    Vector3f T; // Tangent  (unit)
};

class Curve : public Object3D {
protected:
    std::vector<Vector3f> controls;
    std::vector<double> t;
    std::vector<double> tpad;
    double st, ed;
    int n, k;
public:
    explicit Curve(std::vector<Vector3f> points) : controls(std::move(points)) {}

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        return false;
    }

    std::vector<Vector3f> &getControls() {
        return controls;
    }

    virtual void discretize(int resolution, std::vector<CurvePoint>& data) = 0;

    void drawGL() override {
        Object3D::drawGL();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
        glBegin(GL_LINE_STRIP);
        for (auto & control : controls) { glVertex3fv(control); }
        glEnd();
        glPointSize(4);
        glBegin(GL_POINTS);
        for (auto & control : controls) { glVertex3fv(control); }
        glEnd();
        std::vector<CurvePoint> sampledPoints;
        discretize(30, sampledPoints);
        glColor3f(1, 1, 1);
        glBegin(GL_LINE_STRIP);
        for (auto & cp : sampledPoints) { glVertex3fv(cp.V); }
        glEnd();
        glPopAttrib();
    }

    void evaluate(double mu, std::vector<CurvePoint>&data) {

        int bpos = upper_bound(t.begin(), t.end(), mu) - t.begin() - 1;

        std::vector<double> s(k + 2, 0.0);
        std::vector<double> ds(k + 1, 1.0);
        s[k] = 1;

        for (int p = 1; p <= k; p++) {
            for (int ii = k - p; ii <= k; ii++) {
                int i = ii + bpos - k;
                double w1, w2, dw1, dw2;
                if (tpad[i + p] == tpad[i]) {
                    w1 = mu;
                    dw1 = 1.0;
                } else {
                    w1 = (mu - tpad[i]) / (tpad[i + p] - tpad[i]);
                    dw1 = 1.0 / (tpad[i + p] - tpad[i]);
                }
                if (tpad[i + p + 1] == tpad[i + 1]) {
                    w2 = 1 - mu;
                    dw2 = -1.0;
                } else {
                    w2 = (tpad[i + p + 1] - mu) / (tpad[i + p + 1] - tpad[i + 1]);
                    dw2 = - 1.0 / (tpad[i + p + 1] - tpad[i + 1]);
                }
                if (p == k) {
                    ds[ii] = (dw1 * s[ii] + dw2 * s[ii + 1]) * p;
                }
                s[ii] = w1 * s[ii] + w2 * s[ii + 1];
            }
        }

        s.pop_back();
        int lsk = bpos - k;
        int rsk = n - bpos - 1;

        if (lsk < 0) {
            int len = s.size();
            for (int i = -lsk; i < len; i++) {
                s[i + lsk] = s[i];
                ds[i + lsk] = ds[i];
            }
            s.resize(len + lsk);
            ds.resize(len + lsk);
            lsk = 0;
        }

        if (rsk < 0) {
            int len = s.size() + rsk;
            if (len < 0) len = 0;
            s.resize(len);
            ds.resize(len);
        }

        CurvePoint myPt = {Vector3f::ZERO, Vector3f::ZERO};
        for (int i = 0; i < s.size(); i++) {
            myPt.V += s[i] * controls[lsk + i];
            myPt.T += ds[i] * controls[lsk + i];
        }
        data.push_back(myPt);
    }
};

class BezierCurve : public Curve {
public:
    explicit BezierCurve(const std::vector<Vector3f> &points) : Curve(points) {
        if (points.size() < 4 || points.size() % 3 != 1) {
            printf("Number of control points of BezierCurve must be 3n+1!\n");
            exit(0);
        }
    }

    void discretize(int resolution, std::vector<CurvePoint>& data) override {
        data.clear();
        // TODO (PA2): fill in data vector
        n = controls.size();
        k = n - 1;

        int len = n + k + 1;
        t.resize(len, 0);
        for (int i = 0; i < n; i++) {
            t[i] = 0;
            t[n + i] = 1;
        }

        tpad.resize(len + k, 0);
        for (int i = 0; i < len; i++) tpad[i] = t[i];
        for (int i = len; i < len + k; i++) tpad[i] = t[len - 1];

        st = 0, ed = 1;
        
        resolution *= n;
        for (int i = 0; i < resolution; i++) {
            double mu = st + i * 1.0 * (ed - st) / resolution;
            evaluate(mu, data);
        }

    }

protected:

};

class BsplineCurve : public Curve {
public:
    BsplineCurve(const std::vector<Vector3f> &points) : Curve(points) {
        if (points.size() < 4) {
            printf("Number of control points of BspineCurve must be more than 4!\n");
            exit(0);
        }
    }

    void discretize(int resolution, std::vector<CurvePoint>& data) override {
        data.clear();
        // TODO (PA2): fill in data vector
        n = controls.size();
        k = 3;

        int len = n + k + 1;
        t.resize(len, 0);
        for (int i = 0; i < len; i++) {
            t[i] = i * 1.0 / (n + k);
        }

        tpad.resize(len + k, 0);
        for (int i = 0; i < len; i++) tpad[i] = t[i];
        for (int i = len; i < len + k; i++) tpad[i] = t[len - 1];

        st = t[k], ed = t[len - k - 1];

        resolution *= n;
        for (int i = 0; i < resolution; i++) {
            double mu = st + i * 1.0 * (ed - st) / resolution;
            evaluate(mu, data);
        }

    }

protected:

};

#endif // CURVE_HPP