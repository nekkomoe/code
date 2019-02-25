#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

void io(int &x) {
    x = 0;
    char c = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

const int N = 5e5 + 10, S = 2e5;

int n, x[N], y[N];
map<pair<int, int>, bool> ans;
set<int> g[N];

void dfs(int u) {
    if(g[u].empty()) return ;
    int v = *g[u].begin();
    g[u].erase(v);
    g[v].erase(u);
    dfs(v);
    ans[make_pair(u, v)] = 1;
}

int main() {
    io(n);
    for(int i = 1 ; i <= n ; ++ i) {
        io(x[i]), io(y[i]);
        g[x[i]].insert(S + y[i]);
        g[S + y[i]].insert(x[i]);
    }
    for(int i = 1 ; i <= 2 * S ; ++ i) {
        if(g[i].size() & 1) {
            dfs(i);
        }
    }
    for(int i = 1 ; i <= 2 * S ; ++ i) {
        while(g[i].size()) {
            dfs(i);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        putchar(ans[make_pair(x[i], S + y[i])] ? 'b' : 'r');
    }
}
