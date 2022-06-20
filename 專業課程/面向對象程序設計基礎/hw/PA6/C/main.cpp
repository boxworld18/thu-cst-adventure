#include <iostream>
#include <vector>
#include <string>

#include "CustomClass.h"
#include "Object.h"

std::map<std::string, int> CustomClass::cnt;

int main()
{
    {
        //subtask 1
        Object x;
        x = 1;
        std::cout << x << std::endl; //1
        x = std::string("text");
        std::cout << x << std::endl; //text
        x = CustomClass("obj1"); //a user-defined class
    }
    CustomClass::detect_leak();

    {
        //subtask 2
        Object x, y, z;
        x = 1;
        y = x; // y point to the same value of x
        z = CustomClass("obj2");
        std::cout << x << " " << y << std::endl; //1 1

        x += 1;
        std::cout << x << " " << y << std::endl; //2 2

        x = std::string("text"); // x points to "text", but y still points to 2
        std::cout << x << " " << y << std::endl; //text 2

        y = x;
        x += std::string("1");
        std::cout << x << " " << y << std::endl; //text1 text1
        x = z;
    }
    CustomClass::detect_leak();

    {
        //subtask 3
        std::vector<Object> arr;
        arr.push_back(Object(1));
        arr.push_back(Object("text"));
        arr.push_back(Object(CustomClass("obj3")));
        std::cout << arr[0] << " " << arr[1] << std::endl; //1 text
        arr[0] = arr[1];
        std::cout << arr[0] << " " << arr[1] << std::endl; //text text
        arr[1] += std::string("1");
        std::cout << arr[0] << " " << arr[1] << std::endl; //text1 text1
        arr[0] = arr[2];
        std::cout << arr[1] << std::endl; //text1
    }
    CustomClass::detect_leak();

    {
        //subtask 4
        std::vector<Object> inner_arr1 = {Object(1), Object("text1"), CustomClass("obj4")};
        std::vector<Object> inner_arr2 = {Object(2), Object("text2")};
        std::vector<Object> arr = {Object(inner_arr1), Object(inner_arr2), CustomClass("obj5")};

        std::cout << arr[0][0] << " " << arr[0][1] << std::endl; // 1 text1
        std::cout << arr[1][0] << " " << arr[1][1] << std::endl; // 2 text2

        arr[1] = arr[0];
        std::cout << arr[1][0] << " " << arr[1][1] << std::endl; // 1 text1

        arr[0][0] += 2;
        std::cout << arr[0][0] << " " << arr[1][0] << std::endl; // 3 3

        arr[0][1] = arr[1][0]; // arr[1][1] and arr[0][1] is the same Object
        std::cout << arr[0][1] << " " << arr[1][1] << std::endl; // 3 3

        arr[0][0] = arr[2];
    }
    CustomClass::detect_leak();

    return 0;
}
