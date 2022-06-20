#pragma once
#include "Student.h"
using namespace std;

class School {
    Student* student[100010];
    int total;
public:
    School() {};
    School(int n);
    void add_member(Student s);
    Student& operator[](string str) {
        int ok = 0;
        for (int i = 1; i < total; i++)
        if (str == (*student[i]).getName()) {
            if (ok == 0) ok = i;
            else if (*student[ok] < *student[i]) ok = i;
        }
        return *student[ok];
    };
    Student& operator[](char chr) {
        int ok = 0;
        for (int i = 1; i < total; i++)
        if (chr == (*student[i]).getProvince()) {
            if (ok == 0) ok = i;
            else if (*student[ok] < *student[i]) ok = i;
        }
        return *student[ok];
    }
    Student& operator[](int id) {
        int ok = 0;
        for (int i = 1; i < total; i++)
        if (id == atoi((*student[i]).getID().c_str())) {
            if (ok == 0) ok = i;
            else if (*student[ok] < *student[i]) ok = i;
        }
        return *student[ok];
    }
    ~School();
};