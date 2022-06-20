#pragma once
#include <string>
using namespace std;

class Student {
    string name;
    char province;
    string grade;
    string time;
    string id;
public:
    Student();
    Student(string name, char province = 0, string grade = "", string time = "", string id = "");
    void operator=(const Student& s) { 
        name = s.name;
        province = s.province;
        grade = s.grade;
        time = s.time;
        id = s.id;
    }
    bool operator<(const Student& s) {
        if (time < s.time) return true;
        if (time == s.time && id < s.id) return true;
        return false;
    }
    void changeInfo(string s, char prov, string gr, string ti, string idd);
    string getName();
    char getProvince();
    string getID();
    friend istream& operator>>(istream& in, Student& dst);
    friend ostream& operator<<(ostream& out, const Student& src);
    ~Student();
};
