//dfs + xor

%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 200010;

int head[N], rest[N], w[N], to[N], tot;

void add(int u, int v, int wi) {
    tot ++;
    to[tot] = v;
    w[tot] = wi;
    rest[tot] = head[u];
    head[u] = tot;
}

int val[N];

void dfs(int u, int f = 0) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != f) {
            val[v] = val[u] ^ w[i];
            dfs(v, u);
        }
    }
}

int n, m;

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v, w ; i < n ; i ++) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1);
    scanf("%d", &m);
    for(int i = 1, u, v ; i <= m ; i ++) {
        scanf("%d%d", &u, &v);
        printf("%d\n", val[u] ^ val[v]);
    }
}
