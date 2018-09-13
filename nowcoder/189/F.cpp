#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <string>
  
using namespace std;
  
const int N = 2100000;
  
string s1, s2, s;
  
int nxt[N];
  
vector<int> pos;
  
int main() {
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s1;
    s2 = "suqingnianloveskirito";
    s = "#" + s2 + "." + s1;
    for(int i = 2, j = 0 ; i <= s.length() ; ++ i) {
        while(j && s[j + 1] != s[i]) j = nxt[j];
        if(s[j + 1] == s[i]) ++ j;
        nxt[i] = j;
        if(i > s2.length() && nxt[i] == s2.length()) {
            pos.push_back(i - s2.length() - 1 - s2.length() + 1);
        }
    }
    if(pos.size()) {
        if(pos.size() >= 3) {
            cout << "No" << endl;
        } else if(pos.size() == 1) {
            cout << "Yes" << endl;
            int x = pos[0];
            cout << x << ' ' << (x + 1) << endl;
        } else {
            int n = s2.length();
            int x = pos[0], y = pos[1];
            cout << "Yes" << endl;
            cout << x << ' ' << (y + 1) << endl;
        }
    } else {
        int n = s1.length();
        cout << "Yes" << endl;
        cout << (rand() % n + 1) << ' ' << (rand() % n + 1) << endl;
    }
}
