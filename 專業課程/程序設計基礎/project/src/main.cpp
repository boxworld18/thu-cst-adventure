#include <iostream>
#include <fstream>
#pragma pack(2)
using namespace std;

//public variables-------------------//
const double pi = 3.1415926535;
extern unsigned char ***pixel;
extern int OrigX, OrigY, Ratio, Width, Height;
short bits;
//public functions-------------------//
void createCanvas(int, int, int, int, int, bool);
void createCanvas3D(int, int, int, int, double, double, double, double, double, double);
void deleteCanvas();
void plotLine(double, double, double, double, int);
void plot2D(double (*)(double), double, double, int);
void plotPara(double (*)(double), double (*)(double), double, double, int);
void plot3D(double (*)(double, double), double, double, double, double);
double func1(double);
double func2(double);
double func31(double);
double func32(double);
double func41(double);
double func42(double);
double func51(double);
double func52(double);
double func511(double);
double func512(double);
double func521(double);
double func522(double);
double func6(double, double);
//functions on this page-------------//
void saveCanvas(const char*);
//-----------------------------------//

struct BmpFileHeader {
    short   bfTybe;
    int     bfSize;
    short   bfReserved1;
    short   bfReserved2;
    int     bfOffBits;
};

struct BmpInfoHeader {
    int     biSize;
    int     biWidth;
    int     biHeight;
    short   biPlanes;
    short   biBitCount;
    int     biCompression;
    int     biSizeImage;
    int     biXPelsPerMeter; // 72dpi=2835, 96dpi=3780
    int     biYPelsPerMeter; // 120dpi=4724, 300dpi=11811
    int     biClrUsed;
    int     biClrImportant;
};

void saveCanvas(const char* fileName) {

    BmpFileHeader bfh;
	bfh.bfTybe = 0x4d42,
    bfh.bfReserved1 = 0,
    bfh.bfReserved2 = 0,
    bfh.bfOffBits = 54;

    bfh.bfSize = bfh.bfOffBits + Width * Height * bits / 8;

    BmpInfoHeader bih;
	bih.biSize = 40,
    bih.biPlanes = 1,
    bih.biXPelsPerMeter = 0,
    bih.biYPelsPerMeter = 0,
    bih.biClrUsed = 0,
    bih.biClrImportant = 0,
    bih.biCompression = 0;


    bih.biWidth = Width;
    bih.biHeight = Height;
    bih.biBitCount = bits;
    bih.biSizeImage = Width * Height * bits / 8;

    ofstream fout(fileName, ios::binary);

    fout.write((char *)&bfh, sizeof(bfh));
    fout.write((char *)&bih, sizeof(bih));

    char pad[4] = {0, 0, 0, 0};
    int alig = ((Width * bits / 8) * 3) % 4;
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++)
        for (int k = 0; k < 3; k++)
            fout.write((char *) &pixel[j][i][k], 1);
        fout.write(pad, alig);
    }
    fout.close();

}

int main(int argc, char *argv[]) {
    int width = 750, height = 750;
    bits = 24;
    //Graph 1
    createCanvas(1500, 1500, 750, 750, 100, 1);
    plot2D(func1, -7.5, 7.5, 0x6b8d23);
    saveCanvas("func1.bmp");
    deleteCanvas();
    //Graph 2
    createCanvas(1500, 1500, 750, 200, 200, 1);
    plot2D(func2, -7.5, 7.5, 0x33a1c9);
    saveCanvas("func2.bmp");
    deleteCanvas();
    //Graph 3
    createCanvas(1500, 1500, 750, 850, 200, 0);
    plotPara(func31, func32, 0, 2 * 3.1416, 0x0000ff);
    saveCanvas("func3.bmp");
    deleteCanvas();
    //Graph 4
    createCanvas(1500, 1500, 750, 900, 200, 1);
    plot2D(func41, -2, 2, 0xb0171f);
    plot2D(func42, -2, 2, 0xff8000);
    saveCanvas("func4.bmp");
    deleteCanvas();
    //Graph 5
    createCanvas(1500, 1500, 750, 650, 100, 1);
    plot2D(func41, -2, 2, 0xb0171f);
    plot2D(func42, -2, 2, 0xff8000);
    plotPara(func511, func512, 0, 60, 0x000066);
    plotPara(func521, func522, 0, 60, 0x000066);
    saveCanvas("func5.bmp");
    deleteCanvas();
    //Graph 6
	double Ratio6 = 1;
    createCanvas3D(800 * Ratio6, 600 * Ratio6, 400 * Ratio6, 300 * Ratio6, -24.8438 * Ratio6, -5.375 * Ratio6, 16.175 * Ratio6, -5.3 * Ratio6, 0 * Ratio6, 145 * Ratio6);
    plot3D(func6, -8, 8, -8, 8);
    saveCanvas("func6.bmp");
    deleteCanvas();
}
