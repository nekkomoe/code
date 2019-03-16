#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

string inp;

int main() {
    ios :: sync_with_stdio(0);
    int t; cin >> t;
    getline(cin, inp);
    while(t --) {
        getline(cin, inp);
        stringstream fs;
        fs.str(inp);
        string str;
        int flag = 0;
        while(fs >> str) {
            transform(str.begin(), str.end(), str.begin(), :: tolower);
            if(flag) str[0] = toupper(str[0]);
            else flag = 1;
            cout << str;
        }
        cout << endl;
    }
}
