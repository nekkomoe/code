// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

int dis[N], vis[N];
struct T { int u, w; };
bool operator < (T a, T b) { return a.w > b.w; }
priority_queue<T> pq;

struct E { int v, w; };
vector<E> g[N];

int main() {
    int n, m, c; scanf("%d%d%d", &n, &m, &c);
    for(int i = 1, u, v, w ; i <= m ; ++ i)
        scanf("%d%d%d", &u, &v, &w),
        g[u].push_back((E) { v, w });
    int A, B; scanf("%d%d", &A, &B);
    for(int i = 0 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n && (i ^ j) <= n ; j <<= 1)   
            g[i ^ j].push_back((E) { i, j * c }),
            g[i].push_back((E) { i ^ j, j * c });
    memset(dis, 0x3f, sizeof dis);
    dis[A] = 0; pq.push((T) { A, 0 });
    while(pq.size()) {
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(E e: g[u]) {
            int v = e.v, w = e.w;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push((T) { v, dis[v] });
            }
        }
    }
    printf("%d\n", dis[B]);
}
