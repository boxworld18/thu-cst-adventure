#include "Robot.h"
#include "Part.h"

Robot::Robot() {
    needParts = 0;
}

Robot::Robot(int num) {
    needParts = num;
    parts = new Part[num];
}

bool Robot::is_full() {
    return countParts >= needParts;
}

void Robot::add_part(Part part) {
    parts[countParts++] = part;
}

int Robot::run() {
    int tmp = 0;
    for (int i = 0; i < countParts; i++) tmp += parts[i].get();
    return tmp;
}

int& Robot::getNeedParts() {
    return needParts;
}

int& Robot::getCountParts() {
    return countParts;
}

int& Robot::getPartId(int index) {
    return parts[index].get();
}

std::ostream& operator<<(std::ostream& out, const Robot& src) {
    out << "Build robot " << src.type;
    return out;
}

Robot::~Robot() {
    delete[] parts;
}