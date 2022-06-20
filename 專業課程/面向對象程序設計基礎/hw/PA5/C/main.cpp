#include <cstring>
#include <iostream>

using namespace std;

#include "what.h"
#include "alien.h"

void doSpeak(WhatCanSpeak* obj) { 
  obj->speak();
  obj->stop();
  cout << "****\n";
}
void doMotion(WhatCanMotion* obj) {
  obj->motion();
  obj->stop();
  cout << "****\n";
}

int main()
{
  std::string name;
  std::cin >> name;
  Alien alien(name);
  doSpeak(&alien);
  cout << "----\n";
  doMotion(&alien);
  cout << "----\n";
  return 0;
}