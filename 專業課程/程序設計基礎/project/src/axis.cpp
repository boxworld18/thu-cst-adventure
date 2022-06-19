#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#pragma pack(2)
using namespace std;

//public variables-------------------//
unsigned char ***newPixel;
extern unsigned char ***pixel;
extern int OrigX, OrigY, Ratio, Width, Height;
//public functions-------------------//
void plotLine(double, double, double, double, int);

//functions on this page-------------//
void genNewPixel(int , int);
void readCanvas(const char*, int*, int*, short*);
int placeCount(string*, int);
void writeNumber(int, int, int);
void drawAxis();
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

void genNewPixel(int width, int height) {
    newPixel = new unsigned char **[width];
    for (int i = 0; i < width; i++) {
        newPixel[i] = new unsigned char *[height];
        for (int j = 0; j < height; j++) {
            newPixel[i][j] = new unsigned char [3];
            for (int k = 0; k < 3; k++) newPixel[i][j][k] = 255;
        }
    }
}

void readCanvas(const char* fileName, int* width, int* height, short* bits) {
    BmpFileHeader bfh;
    BmpInfoHeader bih;

    ifstream fin(fileName, ios::binary);
    fin.read((char*) &bfh, sizeof(bfh));
    fin.read((char*) &bih, sizeof(bih));

    *width = (int)(bih.biWidth);
    *height = bih.biHeight;
    *bits = bih.biBitCount;

    genNewPixel(*width, *height);
    int alig = (((int)(*width) * (int)(*bits) / 8) * 3) % 4;

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            fin.read((char *) &newPixel[j][i][0], 1);
            fin.read((char *) &newPixel[j][i][1], 1);
            fin.read((char *) &newPixel[j][i][2], 1);
        }
        for (int j = 0; j < alig; j++)
        {
            unsigned char null;
            fin.read((char *) &null, sizeof(null));
        }
    }
    fin.close();
}

int placeCount(string *a, int num) {
    if (num == 0) {
        *a = "0";
        return 1;
    }
    string tmp = "";
    int cnt = 0;
    if (num < 0) {
        cnt++;
        num *= -1;
        *a = "a";
    }
    while (num) {
        cnt++;
        tmp = char(num % 10 + 48) + tmp;
        num /= 10;
    }
    *a += tmp;
    return cnt;
}

void writeNumber(int num, int mid, int cmd) {
    const int width = 20, height = 30, dif = 7;
    string a;
    int cnt = placeCount(&a, num);
    int leftBotX, leftBotY;
    if (cmd == 0) {
        leftBotX = OrigX - width - dif;
        leftBotY = OrigY - height - dif;
    } else if (cmd == 1) {
        leftBotX = mid - width / 2 * cnt;
        leftBotY = OrigY - height - dif;
        if (mid + width / 2 * cnt > Width || mid - width / 2 * cnt < 0) return;
    } else if (cmd == 2) {
        leftBotX = OrigX - dif - width * cnt;
        leftBotY = mid - height / 2;
        if (mid + height / 2 > Height || mid - height / 2 < 0) return;
    }
    for (int k = 0; k < cnt; k++) {
        int width0, height0;
        short bits;

        char fileName[] = "Numbers_30x20/&.bmp";
        for (int i = 0; i < strlen(fileName); i++)
        if (fileName[i] == '&') fileName[i] = a[k];

        readCanvas(fileName, &width0, &height0, &bits);

        int X = leftBotX + width * k, Y = leftBotY;
        for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        for (int z = 0; z < 3; z++)
            pixel[X + x][Y + y][z] = newPixel[x][y][z];
    }
}

void drawAxis() {
    double left = - Height / Ratio;
    double right = Height / Ratio;
    double bottom = - Width / Ratio;
    double top = Width / Ratio;
    plotLine(left, 0, right, 0, 0x000000);
    plotLine(0, bottom, 0, top, 0x000000);
    double unit = 1;
    writeNumber(0, 0, 0);
    for (int k = unit; ; k += unit) {
        double i = OrigX + k * Ratio;
        if (i > Width) break;
        plotLine(k, - 5.0 / Ratio, k, 0, 0x000000);
        writeNumber(k, i, 1);
    }
    for (int k = -unit; ; k -= unit) {
        double i = OrigX + k * Ratio;
        if (i < 0) break;
        plotLine(k, - 5.0 / Ratio, k, 0, 0x000000);
        writeNumber(k, i, 1);
    }
    for (int k = unit; ; k += unit) {
        double i = OrigY + k * Ratio;
        if (i > Height) break;
        plotLine(- 5.0 / Ratio, k, 0, k, 0x000000);
        writeNumber(k, i, 2);
    }
    for (int k = -unit; ; k -= unit) {
        double i = OrigY + k * Ratio;
        if (i < 0) break;
        plotLine(- 5.0 / Ratio, k, 0, k, 0x000000);
        writeNumber(k, i, 2);
    }
}
