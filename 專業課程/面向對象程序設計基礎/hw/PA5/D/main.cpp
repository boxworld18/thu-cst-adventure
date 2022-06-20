#include <iostream>
#include <vector>
#include <string>

#include "animal.h"
#include "action.h"

using namespace std;

int main()
{
    Animal* buffer[100];
    vector<Dog> dogzone;
    vector<Bird> birdzone;

    int n;
    cin >> n;

    // step 1: store all animals in buffer
    for(int i = 1; i <= n; i++){
        string type, name;
        cin >> type >> name;
        if(type == "dog")
            buffer[i] = new Dog(name);
        else if(type == "bird")
            buffer[i] = new Bird(name);
    }

    // step2: move animal to the corresponding zone
    for(int i = 1; i <= n; i++){
        action(buffer[i], dogzone, birdzone);
        delete buffer[i];
    }

    // output animals' name and type
    for(auto &dog : dogzone){
        cout << dog << endl;
    }
    for(auto &bird : birdzone){
        cout << bird << endl;
    }

    return 0;
}