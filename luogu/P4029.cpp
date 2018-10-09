#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
int n, m;
 
string s;
 
string left_expr, right_expr;
 
int left_pak[300], right_pak[300], pak[300];
 
vector<string> left_vec, right_vec;
 
void sol() {
 
    for(int i = 0 ; i < s.length() ; ++ i) {
        if(s[i] != '=' && !isupper(s[i]) && !isdigit(s[i]) && s[i] != '?' && s[i] != '+') {
            cout << "No Solution" << endl;
            return; 
        }
    }
 
    int eq_pos = s.find("=");
    if(eq_pos == s.npos) {
        cout << "No Solution" << endl;
        return;
    }
    left_expr = s.substr(0, eq_pos);
    right_expr = s.substr(eq_pos + 1, s.length() - eq_pos);
 
    left_vec.clear(), right_vec.clear();
 
    memset(left_pak, 0, sizeof left_pak);
    memset(right_pak, 0, sizeof right_pak);
 
    bool is_in_left = false;            // 问号是否在左侧
 
    left_expr += "+";
 
    for(int i = 0, lastpos = 0 ; i < left_expr.length() ; ++ i) {
        if(left_expr[i] == '+') {
            if(i - lastpos > 0) left_vec.push_back(left_expr.substr(lastpos, i - lastpos));
            lastpos = i + 1;
        } else if(left_expr[i] == '?') {
            is_in_left = true;
            lastpos = i + 1;
        }
    }
 
    right_expr += "+";
 
    for(int i = 0, lastpos = 0 ; i < right_expr.length() ; ++ i) {
        if(right_expr[i] == '+') {
            if(i - lastpos > 0) right_vec.push_back(right_expr.substr(lastpos, i - lastpos));
            lastpos = i + 1;
        } else if(right_expr[i] == '?') {
            is_in_left = false;
            lastpos = i + 1;
        }
    }
 
    for(int i = 0 ; i < left_vec.size() ; ++ i) {
        for(int j = 0 ; j < left_vec[i].length() ; ++ j) {
            if(!isupper(left_vec[i][j])) {
                continue;
            }
            if(j + 1 < left_vec[i].length() && isdigit(left_vec[i][j + 1])) {
                left_pak[left_vec[i][j]] += left_vec[i][j + 1] - '0';
            } else {
                left_pak[left_vec[i][j]] += 1;
            }
        }
    }
    for(int i = 0 ; i < right_vec.size() ; ++ i) {
        for(int j = 0 ; j < right_vec[i].length() ; ++ j) {
            if(!isupper(right_vec[i][j])) {
                continue;
            }
            if(j + 1 < right_vec[i].length() && isdigit(right_vec[i][j + 1])) {
                right_pak[right_vec[i][j]] += right_vec[i][j + 1] - '0';
            } else {
                right_pak[right_vec[i][j]] += 1;
            }
        }
    }
    bool flag = false;
    if(is_in_left) {
        for(int i = 0 ; i < 300 ; ++ i) {
            pak[i] = right_pak[i] - left_pak[i];
            if(pak[i] < 0 || pak[i] > 9) {
                cout << "No Solution" << endl;
                return;
            }
        }
        for(int i = 0 ; i < 300 ; ++ i) {
            if(pak[i]) {
                cout << (char)i;
                if(pak[i] > 1) {
                    cout << pak[i];
                }
                flag = true;
            }
        }
        if(flag) cout << endl;
    } else {
        for(int i = 0 ; i < 300 ; ++ i) {
            pak[i] = left_pak[i] - right_pak[i];
            if(pak[i] < 0 || pak[i] > 9) {
                cout << "No Solution" << endl;
                return; 
            }
        }
        for(int i = 0 ; i < 300 ; ++ i) {
            if(pak[i]) {
                cout << (char)i;
                if(pak[i] > 1) {
                    cout << pak[i];
                }
                flag = true;
            }
        }
        if(flag) cout << endl;
    }
    if(!flag) {
        cout << "No Solution" << endl;
        return; 
    }
}
 
int main() {
    // freopen("in", "r", stdin);
    ios :: sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    while(n --) {
        cin >> s;
        sol();
    }
}