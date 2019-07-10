#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
int head[N], rest[N], to[N], tot;
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

// vector<int> sig[int(3e5) + 10];

int vis[int(3e5) + 10];

void init(int n) {
    for(int i = 2 ; i <= n ; ++ i) {
        for(int j = i ; j <= n ; j += i) {
            add(j, i);
        }
    }
}

void runprog() {
    int n, m; scanf("%d%d", &n, &m);
    
    assert(1 <= n && n <= m && m <= int(3e5));
    
//    assert(1 <= min(n, m) && max(n, m) <= 100); // 20%
//    assert(1 <= min(n, m) && max(n, m) <= 1000); // 20%

    for(int i = 2 ; i <= m ; ++ i) {
        vis[i] = 0;
    }
    
    set<int> s;
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        s.emplace(x);
        assert(2 <= x && x <= m);
        vis[x] = 1;
    }
    assert(s.size() == n);
    int ans = 0;
    for(int i = 2 ; i <= m ; ++ i) {
        if(!vis[i]) {
            if(!rest[head[i]]) {
                // pass
            } else {
                vis[i] = 1;
                for(int t = head[i] ; t ; t = rest[t]) {
                    int j = to[t];
                    if(!vis[j]) {
                        vis[i] = 0;
                        break;
                    }
                }
            }
        }

        // printf("%d: ", i);
        // for(int t = head[i] ; t ; t = rest[t]) {
        //     int j = to[t];
        //     printf("%d ", j);
        // } puts("");

        ans += vis[i];
    }
    printf("%d\n", ans);
}

int main() {
    init(int(3e5));
    int t; scanf("%d", &t);
    assert(1 <= t && t <= 5);
    while(t --) {
        runprog();
    }
}
