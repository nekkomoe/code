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
 
const int N = 600000;
 
int n, m;
 
int head1[N], rest1[N], to1[N], tot1;
 
int head2[N], rest2[N], to2[N], tot2;
 
stack<int> s;
 
int instack[N], dfn[N], low[N], clk, cnt, scc[N];
 
int val[N], sval[N];
 
int S, P;
 
int ans;
 
int dis[N], inq[N];
 
queue<int> q;
 
void add1(int u, int v) {
    ++ tot1;
    to1[tot1] = v;
    rest1[tot1] = head1[u];
    head1[u] = tot1;
}
 
void add2(int u, int v) {
    ++ tot2;
    to2[tot2] = v;
    rest2[tot2] = head2[u];
    head2[u] = tot2;
}
 
void tarjan(int u) {
    u[dfn] = u[low] = ++ clk;
    s.push(u);
    u[instack] = 1;
    for(int i = head1[u] ; i ; i = rest1[i]) {
        int v = to1[i];
        if(!v[dfn]) {
            tarjan(v);
            u[low] = min(u[low], v[low]);
        } else if(v[instack]) {
            u[low] = min(u[low], v[dfn]);
        }
    }
    if(u[dfn] == u[low]) {
        int v;
        ++ cnt;
        do {
            v = s.top();
            s.pop();
            v[instack] = 0;
            v[scc] = cnt;
            cnt[sval] += v[val];
        } while(u != v);
    }
}
 
void spfa() {
    S[scc][inq] = 1;
    S[scc][dis] = S[scc][sval];
    q.push(S[scc]);
    while(q.size()) {
        int u = q.front();
        q.pop();
        u[inq] = 0;
        for(int i = head2[u] ; i ; i = rest2[i]) {
            int v = to2[i];
            if(dis[v] < dis[u] + v[sval]) {
                dis[v] = dis[u] + v[sval];
                if(!v[inq]) {
                    q.push(v);
                    v[inq]= 1;
                }
            }
        }
    }
}
 
int main() {
    read(n), read(m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        read(u), read(v);
        add1(u, v);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        read(val[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(!dfn[i]) {
            tarjan(i);
        }
    }
    for(int u = 1 ; u <= n ; ++ u) {
        for(int j = head1[u] ; j ; j = rest1[j]) {
            int v = to1[j];
            if(u[scc] != v[scc]) {
                add2(u[scc], v[scc]);
            }
        }
    }
    read(S), read(P);
    spfa();
    for(int i = 1, x ; i <= P ; ++ i) {
        read(x);
        ans = max(ans, dis[x[scc]]);
    }
    printf("%d\n", ans);
    return 0;
}
