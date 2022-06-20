#include <iostream>
#include <stack>
using namespace std;
stack<string> q[10010];
stack<int> ids;
int main() {
    int n, m;
    cin >> n;
    while (n--) {
        int id;
        string s;
        cin >> id >> s;
        int x = s.find("/");
        while (x != -1) {
            q[id].push(s.substr(0, x));
            s = s.substr(x + 1);
            x = s.find("/");
        }
        q[id].push(s);
        ids.push(id);
    }
    cin >> m;
    while (m--) {
        int id;
        string s;
        cin >> id >> s;
        int x = s.find("/");
        while (x != -1) {
            q[id].push(s.substr(0, x));
            s = s.substr(x + 1);
            x = s.find("/");
        }
        q[id].push(s);
        ids.push(id);
    }
    while (!ids.empty()) {
        int id = ids.top();
        ids.pop();
        if (!q[id].empty()) {
            cout << id << endl;
            while (!q[id].empty()) {
                cout << q[id].top() << endl;
                q[id].pop();
            }
        }
    }
}