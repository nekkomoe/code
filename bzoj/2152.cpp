#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
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
 
const int N = 50000;
 
int head[N], rest[N], to[N], w[N], ban[N], deep[N], maxSize[N] = {0x3f3f3f3f}, root, sz[N], size, ans, n;
 
void add(int u, int v, int wi) {
    static int tot = 0;
    ++ tot;
    to[tot] = v;
    w[tot] = wi;
    rest[tot] = head[u];
    head[u] = tot;
}
 
void getRoot(int u, int fa) {
    u[sz] = 1;
    u[maxSize] = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa && !v[ban]) {
            getRoot(v, u);
            u[sz] += v[sz];
            u[maxSize] = max(u[maxSize], v[sz]);
        }
    }
    u[maxSize] = max(u[maxSize], size - u[sz]);
    if(u[maxSize] < root[maxSize]) {
        root = u;
    }
}
 
int t[3];
 
void getDeep(int u, int fa, int dep) {
    ++ t[dep];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa && !v[ban]) {
            getDeep(v, u, (dep + w[i]) % 3);
        }
    }
}
 
ll calc(int u, int dep) {
    t[0] = t[1] = t[2] = 0;
    getDeep(u, 0, dep % 3);
    return t[0] * t[0] + t[1] * t[2] * 2;
}
 
void dfs(int u) {
    ans += calc(u, 0);
    u[ban] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!v[ban]) {
            ans -= calc(v, w[i]);
            root = 0;
            size = v[sz];
            getRoot(v, 0);
            dfs(root);
        }
    }
}
 
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
 
int main() {
    read(n);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        read(u), read(v), read(w);
        add(u, v, w % 3);
        add(v, u, w % 3);
    }
    size = n;
    getRoot(1, 0);
    dfs(root);
    int d = gcd(ans, n * n);
    printf("%d/%d\n", ans / d, n * n / d);
    return 0;
}
