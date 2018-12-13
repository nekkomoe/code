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
 
const int N = 2123456;
 
int head[N], rest[N], to[N], tot;
 
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
int n, T, vis[N], match[N];
 
bool dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v[vis] == T) continue;
        v[vis] = T;
        if(!v[match] || dfs(v[match])) {
            v[match] = u;
            return 1;
        }
    }
    return 0;
}
 
int main() {
    read(n);
    for(int i = 1, x, y ; i <= n ; ++ i) {
        read(x), read(y);
        add(x, i), add(y, i);
    }
    int i;
    for(i = 1 ; i <= 10000 ; ++ i) {
        ++ T;
        if(!dfs(i)) {
            break;
        }
    }
    printf("%d\n", i - 1);
    return 0;
}
