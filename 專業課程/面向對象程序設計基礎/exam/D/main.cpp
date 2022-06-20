#include <type_traits>
#include <iostream>
#include "Instruction.h"
#include "MagicArray.h"

using namespace std;

int main()
{

//    #ifdef SUBTASK1
    {
        //subtask1
        MagicArray arr(1);  // create a MagicArray with length=1
        for(int i = 0; i < 10;  i++){
            arr[0] += 1;
        }

        cout << "#### Test Case 1-1 ####" << endl;
        std::vector<int> vec1{0};
        arr.apply(vec1); //apply "vec1[0] += 1" for 10 times
        cout << vec1[0] << endl; // 10

        cout << "#### Test Case 1-2 ####" << endl;
        std::vector<int> vec2{5};
        arr.apply(vec2); //apply "vec2[0] += 1" for 10 times
        cout << vec2[0] << endl; // 15

        cout << "#### Test Case 1-3 ####" << endl;
        std::vector<double> vec3{1.5}; // You can even use vector<double>
        arr.apply(vec3); //apply "vec3[0] += 1" for 10 times
        cout << vec3[0] << endl; // 11.5
    }
//    #endif

    #ifdef SUBTASK2
    {
        //subtask2
        MagicArray arr(5);  // create a MagicArray with length=5
        for(int i = 0; i < 5;  i++){
            arr[i] += i;
        }

        cout << "#### TestCase 2: Output Instructions ####" << endl;
        static_assert(std::is_abstract<Instruction>(), "Instruction should be an abstract class");
        std::vector<Instruction*> &instructions = arr.getInstructions();
        for(auto ins : instructions) {
            ins -> output();
        }

        cout << "#### TestCase 2-1 ####" << endl;
        std::vector<int> vec1{0, 0, 0, 0, 0};
        arr.apply(vec1);
        for(auto x : vec1) cout << x << " "; // 0 1 2 3 4
        cout << endl;

        cout << "#### TestCase 2-2 ####" << endl;
        std::vector<double> vec2{5.5, 4.4, 3.3, 2.2, 1.1};
        arr.apply(vec2);
        for(auto x : vec2) cout << x << " "; // 5.5 5.4 5.3 5.2 5.1
        cout << endl;
    }
    #endif

    #ifdef SUBTASK3
    {
        //subtask3
        MagicArray arr(3);  // create a MagicArray with length=3
        for(int i = 0; i < 2;  i++){
            arr[i+1] += arr[i];
            arr[i] = arr[i+1];
            arr[i] += i + 1;
        }
        arr[2] += arr[2];

        cout << "#### TestCase 3: Output Instructions ####" << endl;
        static_assert(std::is_abstract<Instruction>(), "Instruction should be an abstract class");
        std::vector<Instruction*> instructions = arr.getInstructions();
        for(auto ins : instructions) {
            ins -> output();
        }

        cout << "#### TestCase 3-1 ####" << endl;
        std::vector<int> vec1{0, 0, 0};
        arr.apply(vec1);
        for(auto x : vec1) cout << x << " "; //1 2 0
        cout << endl;

        cout << "#### TestCase 3-2 ####" << endl;
        std::vector<double> vec2{0.3, 0.2, 0.1};
        arr.apply(vec2);
        for(auto x : vec2) cout << x << " "; //1.5 2.6 1.2
        cout << endl;
    }
    #endif

    #ifdef SUBTASK4
    {
        //subtask4
        MagicArray arr(3);  // create a MagicArray with length=3
        arr[2] += arr[2];
        for(int i = 0; i < 2;  i++){
            arr[i] += arr[i+1];
            cout << arr[i] << arr.endl();
            arr[i] += i + 1;
            arr[i+1] = arr[i];
        }

        cout << "#### TestCase 4: Output Instructions ####" << endl;
        static_assert(std::is_abstract<Instruction>(), "Instruction should be an abstract class");
        std::vector<Instruction*> instructions = arr.getInstructions();
        for(auto ins : instructions) {
            ins -> output();
        }

        cout << "#### TestCase 4-1 ####" << endl;
        std::vector<int> vec1{3, 2, 1};
        arr.apply(vec1);
        for(auto x : vec1) cout << x << " "; //6 10 10
        cout << endl;

        cout << "#### TestCase 4-2 ####" << endl;
        std::vector<double> vec2{0.3, 0.2, 0.1};
        arr.apply(vec2);
        for(auto x : vec2) cout << x << " "; //1.5 3.7 3.7
        cout << endl;
    }
    #endif

    return 0;
}