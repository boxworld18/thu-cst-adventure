#ifndef _COW_
#define _COW_
using namespace std;

class Cow {
public:
    std::string name;
    int l, u, m;
    int vol, stat;
    Cow(string, int, int, int);
    Cow();
};

#endif