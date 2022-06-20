#include <string>
#include "Farm.h"
#include "Cow.h"
using namespace std;

Farm::Farm(int n) {
    cnt = 0;
    number = n;
    totalMilk = 0;
}

void Farm::addCow(Cow cow1) {
    cow[cnt] = cow1;
    cnt++;
}

void Farm::supply(string name, int a) {
    for (int i = 0; i < number; i++)
    if (cow[i].name == name) {
        cow[i].vol += a;
        break;
    }
}

void Farm::startMeal() {
    for (int i = 0; i < number; i++) {
        if (cow[i].vol == 0) {
            cow[i].stat = 0;
        } else if (cow[i].vol < cow[i].l) {
            cow[i].stat = 1;
        } else {
            cow[i].stat = 2;
        }

        if (cow[i].vol > cow[i].u) {
            cow[i].vol -= cow[i].u;
        }else {
            cow[i].vol = 0;
        }
    }
}

void Farm::produceMilk() {
    for (int i = 0; i < number; i++) {
        switch (cow[i].stat) {
            case 1: 
                totalMilk += cow[i].m * 0.5;
                break;
            case 2:
                totalMilk += cow[i].m;
                break;
        }
    }
}

double Farm::getMilkProduction() {
    return totalMilk;
}