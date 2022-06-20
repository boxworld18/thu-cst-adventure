#include "School.h"
#include <iostream>
#include <cstring>

School::School(int n) {
    total = 0;
    Student s;
    s.changeInfo("Not Found", 0, "", "", "");
    add_member(s);
}

void School::add_member(Student s) {
    student[total] = new Student;
    *student[total] = s;
    total++;
}

School::~School() {
    for (int i = 0; i < total; i++) delete student[i];
}