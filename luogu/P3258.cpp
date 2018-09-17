#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <ctime>
#include <cctype>
#include <cfloat>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <bitset>

using namespace std;

#ifdef ONLINE_JUDGE
    #define debug
    #define log(message)
#else
    #define debug printf("passing [%s] in line %d\n", __FUNCTION__, __LINE__)
    #define log(message) puts(message)
#endif

#define INF 0x3f3f3f3f

#define INFLL 0x3f3f3f3f3f3f3f3fLL

void closeSync() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

template<class T> void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while(ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ '0'), ch = getchar();
    x = f ? -x : x;
}

typedef long long ll;

// to do

const int N = 600010;

int head[N], to[N], rest[N], tot;

void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}

int a[N], tag[N], fa[N][30], deep[N], n;

void dfs1(int u) {
    u[deep] = u[fa][0][deep] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != u[fa][0]) {
            v[fa][0] = u;
            for(int j = 1 ; j <= 20 ; ++ j) {
                v[fa][j] = v[fa][j - 1][fa][j - 1];
            }
            dfs1(v);
        }
    }
}

int lca(int u, int v) {
    if(u[deep] < v[deep]) swap(u, v);
    for(int i = 20 ; i >= 0 ; -- i) {
        if(u[fa][i][deep] >= v[deep]) {
            u = u[fa][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; i >= 0 ; -- i) {
        if(u[fa][i] != v[fa][i]) {
            u = u[fa][i];
            v = v[fa][i];
        }
    }
    return u[fa][0];
}

void dfs2(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != u[fa][0]) {
            dfs2(v);
            u[tag] += v[tag];
        }
    }
}

int main() {
    read(n);
    for(int i = 1 ; i <= n ; ++ i) {
        read(a[i]);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        read(u), read(v);
        add(u, v);
        add(v, u);
    }
    dfs1(1);
    for(int i = 1 ; i < n ; ++ i) {
        ++ a[i][tag];
        ++ a[i + 1][tag];
        int d = lca(a[i], a[i + 1]);
        -- d[tag];
        -- d[fa][0][tag];
    }
    dfs2(1);
    for(int i = 2 ; i <= n ; ++ i) {
        -- tag[a[i]];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", tag[i]);
    }
    return 0;
}
