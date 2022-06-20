#include "Student.h"
#include <iostream>

using namespace std;

Student::Student() {
    name = "";
    province = 0;
    grade = "";
    time = "";
    id = "";
}

istream& operator>>(istream& in, Student& dst) {

    string data;
    in >> data;

    int pos = data.find("-", 0);
    dst.name = data.substr(0, pos);
    
    dst.province = data[pos + 1];
    dst.grade = data.substr(pos + 3, 1);
    dst.time = data.substr(pos + 5, 4);
    dst.id = data.substr(pos + 10, 6);

    return in;
}

ostream& operator<<(ostream& out, const Student& src) {
    if (src.province == 0) out << src.name << endl;
    else out << src.name << "-" << src.time << "-" << src.grade << "-" << src.id << endl;
    return out;
}

string Student::getName() {
    return name;
}

void Student::changeInfo(string s, char prov, string gr, string ti, string idd) {
    name = s;
    province = prov;
    grade = gr;
    time = ti;
    id = idd;
}

char Student::getProvince() {
    return province;
}

string Student::getID() {
    return id;
}

Student::~Student() {
    
}