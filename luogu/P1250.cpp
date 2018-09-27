// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500000 + 10;
int n, m;
struct E { int v, w; };
vector<E> g[N];
void add(int u, int v, int w) {
    g[u].push_back((E) { v, w });
}
int inq[N]; ll dis[N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        add(i - 1, i, 0);
        add(i, i - 1, -1);
    }
    for(int i = 1, l, r, c ; i <= m ; ++ i) {
        scanf("%d%d%d", &l, &r, &c);
        add(l - 1, r, c);
    }
    
    memset(dis, 0xcf, sizeof dis), dis[0] = 0;
    
    queue<int> q;
    q.push(0), inq[0] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        
        for(int i = 0 ; i < g[u].size() ; ++ i) {
            E e = g[u][i];
            int v = e.v, w = e.w;
            if(dis[v] < dis[u] + w) {
                dis[v] = dis[u] + w;
                if(!inq[v]) {
                    q.push(v), inq[v] = 1;
                }
            }
        }
    }
    ll ans = dis[n];
    printf("%lld\n", ans);
} 

