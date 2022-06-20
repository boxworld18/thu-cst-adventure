#pragma once
class WhatCanSpeak {
public:
  virtual ~WhatCanSpeak() {cout << "obj cannot speak" << endl; }
  virtual void speak() = 0;  
  virtual void stop() = 0;  
};

class WhatCanMotion {
public:
  virtual ~WhatCanMotion() {cout << "obj cannot move" << endl; }
  virtual void motion() = 0;
  virtual void stop() = 0;  
};

