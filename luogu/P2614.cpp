// 模拟

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

int n, T, st;

double ans;

string s;

int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> T;
    getline(cin, s);
    while(cin >> s) {
        st = 0;
        for(int i = 0 ; i < s.length() ; ++ i) {
            switch(s[i]) {
            case ' ' : case '\n' : case '\r' : break;
            case '(' :
                ++ st;
                break;
            case ')' :
                -- st;
                break;
            case '.' :
                ans += pow(0.5, st + 1);
                break;
            default :
                ans += pow(0.5, st);
            }
        }
    }
    cout << (int(60 * ans) / T) << endl;
}
