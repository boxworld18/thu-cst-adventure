#include <iostream>
#include <cstring>
#include <map>
#include "Parser.h"
using namespace std;

Parser::Parser() {
    cnt = 0;

    string cmd = "--help";
    index[cmd] = 0;
    command[cnt] = cmd;
    name[cnt] = "";
    helpMessage[cnt] = "show this help message and exit";

    cnt++;
}

void Parser::add_argument(string cmd, int num, string help) {
    index[cmd] = cnt;
    command[cnt] = cmd;
    value[cnt] = num;
    helpMessage[cnt] = help;

    int len = cmd.length();
    name[cnt] = "";
    for (int i = 2; i < len; i++)
        name[cnt] += toupper(cmd[i]);

    cnt++;
}

void Parser::printUsage() {
    cout << "usage: ./main";
    for (int i = 0; i < cnt; i++) {
        cout << " [";
        cout << command[i];
        if (i != 0) {
            cout << " " << name[i];
        }
        cout << "]";
    }
    cout << endl;
}

void Parser::printArguments() {
    cout << "optional arguments:" << endl;
    for (int i = 0; i < cnt; i++) {
        cout << " " << command[i];
        if (i != 0) {
            cout << " " << name[i];
        }
        cout << "   " << helpMessage[i] << endl;
    }
}
void Parser::init(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++)
    if (strcmp(argv[i], "--help") == 0) {
        printUsage();
        cout << endl;
        printArguments();
        exit(0);
    }
    int isCmd = 0;
    for (int i = 1; i < argc; i++) 
    if (i % 2 == 1) {
        string cmd = argv[i];
        if (index.count(cmd) <= 0) {
            printUsage();
            cout << argv[0] << ": error: unrecognized arguments: " << cmd << endl;
            exit(0);
        }
        isCmd = 1;
    } else {
        int len = strlen(argv[i]);
        for (int k = 0; k < len; k++)
        if (!isdigit(argv[i][k])) {
            printUsage();
            cout << argv[0] << ": error: argument " << argv[i - 1] << ": invalid int value: '" << argv[i] << "' " << endl;
            exit(0);
        }
        
        string cmd = argv[i - 1];
        int idx = index[cmd];

        int val = atoi(argv[i]);
        value[idx] = val;

        isCmd = 0;
    }
    if (isCmd) {
        printUsage();
        cout << argv[0] << ": error: argument " << argv[argc - 1] << ": expected an argument" << endl;
        exit(0);
    }
}

int Parser::get_argument(string cmd) {
    int idx = index["--" + cmd];
    return value[idx];
}