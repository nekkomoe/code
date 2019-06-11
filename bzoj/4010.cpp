#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

int n, m, deg[N];
vector<int> g[N];
void runprog() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        g[i].clear();
        deg[i] = 0;
    }
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
        ++ deg[u];
    }
    priority_queue<int> pq;
    stack<int> ans;
    for(int i = 1 ; i <= n ; ++ i) {
        if(deg[i] == 0) {
            pq.push(i);
        }
    }
    while(pq.size()) {
        int u = pq.top(); pq.pop();
        ans.push(u);
        for(int i = 0 ; i < g[u].size() ; ++ i) {
            int v = g[u][i];
            if(!-- deg[v]) {
                pq.push(v);
            }
        }
    }
    if(ans.size() != n) {
        puts("Impossible!");
    } else {
        while(ans.size()) {
            printf("%d ", ans.top());
            ans.pop();
        }
        puts("");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
