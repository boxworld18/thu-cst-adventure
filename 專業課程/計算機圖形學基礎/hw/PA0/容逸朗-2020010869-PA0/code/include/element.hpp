#pragma once

#include <image.hpp>
#include <algorithm>
#include <queue>
#include <cstdio>
#include "image.hpp"

class Element {
public:
    int width, height;
    virtual void draw(Image &img) = 0;
    virtual ~Element() = default;
    bool check(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) return 0;
        return 1;
    }
};

class Line : public Element {

public:
    int xA, yA;
    int xB, yB;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Implement Bresenham Algorithm
        width = img.Width();
        height = img.Height();

        if (xA == xB) { 
            // k not exist
            if (yA > yB) std::swap(yA, yB);
            for (int y = yA; y <= yB; y++) 
            if (check(xA, y)) img.SetPixel(xA, y, color);
            return;
        }

        int x, y, dx = xB - xA, dy = yB - yA, e;
        double slope = dy * 1.0 / dx;
        int flag = slope < 0 ? -1 : 1;

        if ((abs(slope) <= 1 && xA > xB) || (abs(slope) > 1 && yA > yB)) {
            std::swap(xA, xB);
            std::swap(yA, yB);
            dx *= -1;
            dy *= -1;
        }

        x = xA, y = yA;

        if (abs(slope) <= 1) {
            // |slope| <= 1
            e = -dx * flag;
            for (int i = 0; i <= dx; i++) {
                if (check(x, y)) img.SetPixel(x, y, color);
                x++;
                e += 2 * dy;
                if (e * flag >= 0) {
                    y += flag;
                    e += -2 * dx * flag;
                }
            }
        } else {
            // |slope| > 1
            e = -dy * flag;
            for (int i = 0; i <= dy; i++) {
                if (check(x, y)) img.SetPixel(x, y, color);
                y++;
                e += 2 * dx;
                if (e * flag >= 0) {
                    x += flag;
                    e += -2 * dy * flag;
                }
            }
        }
            
        printf("Draw a line from (%d, %d) to (%d, %d) using color (%f, %f, %f)\n", xA, yA, xB, yB,
                color.x(), color.y(), color.z());
    }
};

class Circle : public Element {

public:
    int cx, cy;
    int radius;
    Vector3f color;

    void translation(int cx, int cy, int x, int y, Vector3f color, Image &img) {
        int dx[4] = {-1, -1, 1, 1}, dy[4] = {-1, 1, -1, 1};
        for (int i = 0; i < 4; i++) {
            int x1 = cx + x * dx[i], y1 = cy + y * dy[i];
            int x2 = cx + y * dx[i], y2 = cy + x * dy[i];
            if (check(x1, y1)) img.SetPixel(x1, y1, color);
            if (check(x2, y2)) img.SetPixel(x2, y2, color);
        }
    }
    
    void draw(Image &img) override {
        // TODO: Implement Algorithm to draw a Circle

        // calculate the circle with center (0, 0)
        // then translate it with center(cx, cy)
        width = img.Width();
        height = img.Height();

        int x = 0, y = radius, d = 5 - 4 * radius;
        translation(cx, cy, x, y, color, img);
        
        while (x <= y) {
            if (d < 0) {
                d += 8 * x + 12;
            } else {
                d += 8 * (x - y) + 20;
                y--;
            }
            x++;
            translation(cx, cy, x, y, color, img);
        }

        printf("Draw a circle with center (%d, %d) and radius %d using color (%f, %f, %f)\n", cx, cy, radius,
               color.x(), color.y(), color.z());
    }
};

class Fill : public Element {

public:
    int cx, cy;
    Vector3f color;

    void draw(Image &img) override {
        // TODO: Flood fill
        width = img.Width();
        height = img.Height();

        int xl, xr, i;
        bool flag;
        if (!check(cx, cy)) return;
        Vector3f oldColor = img.GetPixel(cx, cy);
        
        std::pair<int, int> seed = std::make_pair(cx, cy);
        std::queue<std::pair<int, int>> myQue;
        myQue.push(seed);

        while (!myQue.empty()) {
            auto np = myQue.front(); myQue.pop();
            int x = np.first, y = np.second;

            while (check(x, y) && img.GetPixel(x, y) == oldColor) {
                img.SetPixel(x, y, color);
                x++;
                if (!check(x, y)) break;
            }
            xr = x - 1;
            x = np.first - 1;
            while (check(x, y) && img.GetPixel(x, y) == oldColor) {
                img.SetPixel(x, y, color);
                x--;
                if (!check(x, y)) break;
            }
            xl = x + 1;

            for (int i = 1; i >= -2; i -= 3) {
                x = xl;
                y = y + i;
                if (!check(x, y)) continue;

                while (x <= xr) {
                    flag = false;
                    while (img.GetPixel(x, y) == oldColor) {
                        flag = true;
                        x++;
                        if (!check(x, y)) break;
                    }
                    if (flag) {
                        np.first = x - 1;
                        np.second = y;
                        myQue.push(np);
                        flag = false;
                    }
                    while (check(x, y) && img.GetPixel(x, y) != oldColor && x <= xr) x++;
                }
            }
        }

        printf("Flood fill source point = (%d, %d) using color (%f, %f, %f)\n", cx, cy,
                color.x(), color.y(), color.z());
    }
};