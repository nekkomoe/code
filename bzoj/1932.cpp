//STL 这份代码只能在windows平台下使用
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <vector>
#include <stack>
#include <map>

using namespace std;

const int N = 2010;

typedef set<int> SET;

struct cmp {
    bool operator () (const SET &a, const SET &b) {
        SET :: iterator ita = a.begin(), itb = b.begin();
        if(a.size() != b.size()) return a.size() < b.size();
        while(ita != a.end() && *ita == *itb) {
            ++ ita;
            ++ itb;
        }
        return ita == a.end() ? 0 : *ita < *itb;
    }
};

map<SET, int, cmp> hs;

stack<int> s;

vector<SET> v;

int n;

char op[100];

int newSet(const SET &s) {
    if(!hs[s]) {
        v.push_back(s);
        hs[s] = v.size() - 1;
    }
    return hs[s];
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%s", op);
        if(*op == 'P') {
            s.push(newSet(SET()));
        } else if(*op == 'D') {
            s.push(s.top());
        } else {
            SET x1 = v[s.top()]; s.pop();
            SET x2 = v[s.top()]; s.pop();
            if(*op == 'U') {
                SET y;
                set_union(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(y, y.begin()));
                s.push(newSet(y));
            } else if(*op == 'I') {
                SET y;
                set_intersection(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(y, y.begin()));
                s.push(newSet(y));
            } else if(*op == 'A') {
                SET y = x2;
                y.insert(newSet(x1));
                s.push(newSet(y));
            }
        }
        printf("%d\n", v[s.top()].size());
    }
}
