#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int head[N], rest[N], to[N], id[N], tot, n, m, q;
void add(int u, int v, int _id) {
    to[++ tot] = v, id[tot] = _id, rest[tot] = head[u], head[u] = tot;
}

ll tag[N], theval[N];
ll get() {
    return (ll) rand() * rand() % int(1e9);
}

int vis[N], dep[N];
void dfs(int u, int fr) {
    vis[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(id[i] == fr) continue;
        if(vis[v]) {
            if(dep[v] < dep[u]) {
                ll val = get();
                tag[v] ^= val;
                tag[u] ^= val;
                theval[id[i]] = val;
            }
        } else {
            dep[v] = dep[u] + 1;
            dfs(v, id[i]);
            tag[u] ^= tag[v];
            theval[id[i]] = tag[v];
        }
    }
}

ll a[N];

int main() {
    srand(4828193);
    // srand((unsigned long long) new char);
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v, i), add(v, u, i);
    }
    dep[1] = 0;
    dfs(1, 0);
    scanf("%d", &q);
    ll lastans = 0;
    while(q --) {
        int k; scanf("%d", &k);
        vector<int> rd;
        while(k --) {
            int x; scanf("%d", &x);
            x ^= lastans;
            rd.push_back(x);
        }
        sort(rd.begin(), rd.end());
        rd.erase(unique(rd.begin(), rd.end()), rd.end());
        for(int i = 0 ; i <= 60 ; ++ i) a[i] = 0;
        int val = 1;
        for(int i = 0 ; i < rd.size() ; ++ i) {
            ll x = theval[rd[i]];
            for(int j = 60 ; ~ j ; -- j) {
                if(x & (1ll << j)) {
                    if(!a[j]) {
                        a[j] = x;
                        break;
                    } else {
                        x ^= a[j];
                    }
                }
            }
            if(x == 0) {
                val = 0;
                break;
            }
        }
        lastans += val;
        puts(val ? "Connected" : "Disconnected");
    }
}
