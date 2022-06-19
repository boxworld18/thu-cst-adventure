#include <iostream>
using namespace std;

//public variables-------------------//
extern unsigned char ***pixel;
extern int OrigX, OrigY, Ratio, Width, Height;
extern double Rxx, Rxy, Ryx, Ryy, Rzx, Rzy;
double **pixel2;
//functions on this page-------------//
int checkXY(int, int);
void Color(int, int, int);
void newArray(double);
void deleteArray();
bool check(double, double, double, double, double, double);
void plotLine(double, double, double, double, int);
void plot2D(double (*)(double), double, double, int);
void plotPara(double (*)(double), double (*)(double), double, double, int);
void plot3D(double (*)(double, double), double, double, double, double);
//-----------------------------------//

int checkXY(int x, int y) {
    if (x < 0 || y < 0 || x >= Width || y >= Height) return 0;
    return 1;
}
void Color(int x, int y, int color) {
    if (!checkXY(x, y)) return;
    short colorR = color / (256 * 256);
    short colorG = (color / 256) % 256;
    short colorB = color % 256;
    pixel[x][y][0] = colorB;
    pixel[x][y][1] = colorG;
    pixel[x][y][2] = colorR;
}

void plotLine(double x1, double y1, double x2, double y2, int color) {
    double delta = 0.005;
    if (x1 == x2) {
        if (y1 > y2) {
            double temp;
            temp = y1; y1 = y2; y2 = temp;
        }
        for (double y = y1; y <= y2; y += delta) {
            int X = x1 * Ratio + OrigX;
            double y0 = y * Ratio + OrigY;
            int Y = (int)y0;
            if (y0 - Y >= 0.5) Y++;
            Color(X, Y, color);
        }
        return;
    }
    if (x1 > x2) {
        double temp;
        temp = x1; x1 = x2; x2 = temp;
        temp = y1; y1 = y2; y2 = temp;
    }

    int lastY;
    double k = (y2 - y1) / (x2 - x1);

    for (double x = x1; x <= x2; x += delta) {
        int X = x * Ratio + OrigX;
        double y = k * (x - x1) + y1;

        double y0 = y * Ratio + OrigY;
        int Y = (int)y0;

        if (y0 - Y >= 0.5) Y++;
        if (x == x1) lastY = Y;

        int minY = lastY, maxY = Y - 1;
        if (lastY > maxY) minY = Y + 1, maxY = lastY;
        for (int i = minY; i <= maxY; i++) Color(X - 1, i, color);
        Color(X, Y, color);
        lastY = Y;
    }
}

void plot2D(double (*func)(double), double minX, double maxX, int color) {
    int lastY;
    double delta = 0.005;
    for (double x = minX; x <= maxX + delta; x += delta) {
        double y = func(x) * Ratio + OrigY;

        int X = x * Ratio + OrigX;
        int Y = (int)y;

        if (y - Y >= 0.5) Y++;
        if (x == minX) lastY = Y;

        int minY = lastY, maxY = Y - 1;
        if (lastY > maxY) minY = Y + 1, maxY = lastY;
        for (int i = minY; i <= maxY; i++) Color(X - 1, i, color);
        Color(X, Y, color);
        lastY = Y;
    }
}

void plotPara(double (*func1)(double), double (*func2)(double), double minT, double maxT, int color) {
    double delta = 0.0005;
    for (double t = minT; t <= maxT; t += delta) {
        double x = func1(t), y = func2(t);
        int X = (int)(x * Ratio) + OrigX;
        int Y = (int)(y * Ratio) + OrigY;
        Color(int(X), int(Y), color);
    }
}

void newArray(double x) {
    pixel2 = new double *[Width];
    for (int i = 0; i < Width; i++) {
        pixel2[i] = new double [Height];
        for (int j = 0; j < Height; j++) pixel2[i][j] = x;
    }
}

void deleteArray() {
    for (int i = 0; i < Width; i++) delete[] pixel2[i];
    delete[] pixel2;
}

bool check(double x, double y, double x0, double y0, double unit, double delta) {
//    if (x == x0 || x == x0 + unit || y == y0 || y == y0 + unit) return 1;
    if (x0 - delta <= x && x <= x0 + delta) return 1;
    if (y0 - delta <= y && y <= y0 + delta) return 1;
    if (x0 - delta + unit <= x && x <= x0 + delta + unit) return 1;
    if (y0 - delta + unit <= y && y <= y0 + delta + unit) return 1;
    return 0;
}

void plot3D(double (*func)(double, double), double minX, double maxX, double minY, double maxY) {
    double unit = 0.500, delta = 0.0005;
    newArray(minX + minY);
    for (double y0 = maxY - unit; y0 >= minY - unit; y0 -= unit)
    for (double x0 = maxX - unit; x0 >= minX - unit; x0 -= unit) {

        for (double y = y0; y <= y0 + unit; y += delta)
        if (minY <= y && y <= maxY)
        for (double x = x0; x <= x0 + unit; x += delta)
        if (minX <= x && x <= maxX) {

            double z = func(x, y);
            double imgX = OrigX + x * Rxx + y * Ryx + z * Rzx;
            double imgY = OrigY + x * Rxy + y * Ryy + z * Rzy;
            int X = int(imgX);
            int Y = int(imgY);
            if (imgX - X >= 0.5) X++;
            if (imgY - Y >= 0.5) Y++;

            int Z = 0xffffff;
            if (check(x, y, x0, y0, unit, 0)) Z = int(z * 256 * 110 + 2200000);
            if (checkXY(X, Y) && x0 + y0 > pixel2[X][Y]) {
                Color(X, Y, Z);
                pixel2[X][Y] = x0 + y0;
            }
        }
    }
    deleteArray();
}