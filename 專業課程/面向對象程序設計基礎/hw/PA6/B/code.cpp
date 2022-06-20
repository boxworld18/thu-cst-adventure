#include<iostream>
#include<vector>
#include<cmath>
#include<functional>
#include"myqueriable.h"

using namespace std;

float fn(float x){return sqrt(x);}
function<float(float)> op = fn;

int main(){
    vector<float> vec = {2.0, 3.0, 4.0, 5.0};
    auto li = from(vec)
        .apply(op);
    for(int i = 0; i < li.size(); i++){
        cout << li[i] << endl;
    }
}