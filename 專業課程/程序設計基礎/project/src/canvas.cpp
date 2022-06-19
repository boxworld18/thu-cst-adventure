#include <iostream>
using namespace std;

//public variables-------------------//
unsigned char ***pixel;
int OrigX, OrigY, Ratio, Width, Height;
double Rxx, Rxy, Ryx, Ryy, Rzx, Rzy;
//public functions-------------------//
void plotLine(double, double, double, double, int);
void plot2D(double (*)(double), double, double, int);
void drawAxis();
//functions on this page-------------//
void newCanvas(int, int);
void createCanvas(int, int, int, int, int, bool);
void createCanvas3D(int, int, int, int, double, double, double, double, double, double);
void deleteCanvas();
//-----------------------------------//

void newCanvas(int width, int height) {
    pixel = new unsigned char **[width];
    for (int i = 0; i < width; i++) {
        pixel[i] = new unsigned char *[height];
        for (int j = 0; j < height; j++) {
            pixel[i][j] = new unsigned char [3];
            for (int k = 0; k < 3; k++) pixel[i][j][k] = 255;
        }
    }
}

void createCanvas(int width, int height, int origX, int origY, int ratio, bool axis) {
    OrigX = origX;
    OrigY = origY;
    Ratio = ratio;
    Width = width;
    Height = height;
    newCanvas(width, height);
    if (axis == true) drawAxis();
}

void createCanvas3D(int width, int height, int origX, int origY, double rxx, double rxy, double ryx, double ryy, double rzx, double rzy) {
    OrigX = origX;
    OrigY = origY;
    Rxx = rxx;
    Rxy = rxy;
    Ryx = ryx;
    Ryy = ryy;
    Rzx = rzx;
    Rzy = rzy;
    Width = width;
    Height = height;
    newCanvas(width, height);
}

void deleteCanvas() {
    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) delete[] pixel[i][j];
        delete[] pixel[i];
    }
    delete[] pixel;
}