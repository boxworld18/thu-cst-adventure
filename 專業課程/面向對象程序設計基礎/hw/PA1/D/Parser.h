#ifndef __PARSER__
#define __PARSER__
#include <string>
#include <map>
using namespace std;

const int N = 10010;

class Parser {
    map <string, int> index;
    int value[N];
    string command[N];
    string name[N];
    string helpMessage[N];
    int cnt;
public:
    Parser();
    void add_argument(string, int, string);
    void init(int, char**);
    void printUsage();
    void printArguments();
    int get_argument(string);
};

#endif