#include <iostream>
#include "Test.h" 
 
using namespace std;
Test&& F(Test &a){
      Test b = a;
      return std::move(b);
 }
  int main(){
      Test A = F(Test(1));
      return 0;
  }