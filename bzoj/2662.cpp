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
 
template<class T> inline void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while(ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ '0'), ch = getchar();
    x = f ? -x : x;
}
 
typedef long long ll;
 
// to do
 
const int N = 210000;
 
int head[N], rest[N], to[N], w[N], tot;
 
struct nd {
    int u, use;
};
 
void add(int u, int v, int wi) {
    ++ tot;
    to[tot] = v;
    w[tot] = wi;
    rest[tot] = head[u];
    head[u] = tot;
}
 
int n, m, k, dis[N][60], inq[N][60], ans = INF;
 
queue<nd> q;
 
void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    q.push((nd) {1, 0});
    dis[1][0] = 0;
    inq[1][0] = 1;
    while(q.size()) {
        nd fr = q.front();
        q.pop();
        int u = fr.u, use = fr.use;
        inq[u][use] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v][use] > dis[u][use] + w[i]) {
                dis[v][use] = dis[u][use] + w[i];
                if(!inq[v][use]) {
                    q.push((nd) {v, use});
                    inq[v][use] = 1;
                }
            }
            if(use + 1 <= k && dis[v][use + 1] > dis[u][use] + w[i] / 2) {
                dis[v][use + 1] = dis[u][use] + w[i] / 2;
                if(!inq[v][use + 1]) {
                    q.push((nd) {v, use + 1});
                    inq[v][use + 1] = 1;
                }
            }
        }
    }
    for(int i = 0 ; i <= k ; ++ i) {
        ans = min(ans, dis[n][i]);
    }
}
 
int main() {
    read(n), read(m), read(k);
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        read(u), read(v), read(w);
        add(u, v, w);
        add(v, u, w);
    }
    spfa();
    printf("%d\n", ans);
    return 0;
}
