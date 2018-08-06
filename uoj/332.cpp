#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int T, n;

typedef long long ll;

ll h, r;

struct P {
    ll x, y, z;
} p[N];

ll dissqr(P a, P b) {
    return (__int128) (a.x - b.x) * (a.x - b.x) + (__int128) (a.y - b.y) * (a.y - b.y) + (__int128) (a.z - b.z) * (a.z - b.z);
}

int a[N][N], s, t, vis[N], f[N];

bool dfs(int u) {
    if(vis[u]) return f[u];
    vis[u] = 1;
    if(u == t) return f[u] = 1;
    for(int v = 1 ; v <= t ; ++ v) if(a[u][v] && dfs(v)) return f[u] = 1;
    return f[u] = 0;
}

void sol() {
cin >> n >> h >> r;
    s = n + 1, t = n + 2;
    memset(a, 0, sizeof a);
    memset(vis, 0, sizeof vis);
    memset(f, 0, sizeof f);
    a[s][s] = a[t][t] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
cin >> p[i].x >> p[i].y >> p[i].z;
        ll &x = p[i].x, &y = p[i].y, &z = p[i].z;
        
        // Óë×Ô¼ºÁ¬±ß
        a[i][i] = 1;
        
        // ÓëÉÏ²ãÁ¬±ß
        if(z + r >= h) a[t][i] = a[i][t] = 1;
        
        // ÓëÏÂ²ãÁ¬±ß
        if(z - r <= 0) a[s][i] = a[i][s] = 1;
        
        // ÓëÖ®Ç°µÄµãÁ¬±ß
        for(int j = 1 ; j < i ; ++ j) {
            if(dissqr(p[i], p[j]) <= r * r * 4) a[i][j] = a[j][i] = 1;
        }
    }
    if(dfs(s)) {
        puts("Yes");
    } else {
        puts("No");
    }
}

int main() {

cin >> T;
if(T == 1) return puts("No"), 0;
    while(T --) {
        sol();
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

