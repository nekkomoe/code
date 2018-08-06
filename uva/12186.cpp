//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <cctype>
#include <cfloat>
#include <bitset>
#include <cmath>

using namespace std;

const int N = 1e5 + 10;

int n, t;

vector<int> son[N];

int f(int u) {
    if(son[u].size() == 0) return 1;
    vector<int> ret;
    for(int i = 0 ; i < son[u].size() ; i ++) {
        ret.push_back(f(son[u][i]));
    }
    sort(ret.begin(), ret.end());
    int c = (son[u].size() * t - 1) / 100 + 1, ans = 0;
    for(int i = 0 ; i < c ; i ++) {
        ans += ret[i];
    }
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &t) == 2 && (n || t)) {
        for(int i = 0 ; i <= n ; i ++) {
            son[i].clear();
        }
        for(int i = 1, sn ; i <= n ; i ++) {
            scanf("%d", &sn);
            son[sn].push_back(i);
        }
        printf("%d\n", f(0));
    }
}
