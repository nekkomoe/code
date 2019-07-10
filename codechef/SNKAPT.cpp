#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    // ---------------------------------------DECLARE--------------------------------------
    const int mod = 1e9 + 7;

    auto pw = [&] (ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod) {
            if(b & 1) {
                r = r * a % mod;
            }
        }
        return r;
    };

    auto getinv = [&] (ll n) {
        return pw(n, mod - 2);
    };

    auto upd = [&] (ll &a, ll b) {
        a = (a + b) % mod;
    };

    // ----------------------------------------BEGIN---------------------------------------
    
    int n, m, z, t;
    scanf("%d%d%d%d", &n, &m, &z, &t);
    char str[n + 10][m + 10];
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str[i] + 1);
    }
    int ids[n + 10][m + 10][t + 10]; memset(ids, 0, sizeof ids);
    int cnt = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            for(int k = 0 ; k <= t ; ++ k) {
                ids[i][j][k] = ++ cnt;
            }
        }
    }
    int S = ++ cnt, T = ++ cnt;
    vector<int> vals[n + 10][m + 10][t + 10];

    // 进入的时候获得收益
    for(int i = 1 ; i <= z ; ++ i) {
        int x, y, p, q, h;
        scanf("%d%d%d%d%d", &x, &y, &p, &q, &h);
        for(int j = p ; j < q ; ++ j) {
            vals[x][y][j].emplace_back(h);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            for(int k = 0 ; k <= t ; ++ k) {
                vals[i][j][k].emplace_back(0);
            }
        }
    }

    const int MXN = 1e6 + 10;
    vector<int> head(MXN), rest(MXN), from(MXN), to(MXN), flow(MXN), cost(MXN);
    int tot = 1;
    auto add = [&] (int u, int v, int w, int c) {
        static auto add_sub = [&] (int u, int v, int w, int c) {
            from[++ tot] = u, to[tot] = v, flow[tot] = w, cost[tot] = c;
            rest[tot] = head[u], head[u] = tot;
        };
        add_sub(u, v, w, c);
        add_sub(v, u, 0, -c);
    };
    vector<int> dis(MXN), pre(MXN), inq(MXN);
    const int inf = 0x3f3f3f3f;
    auto spfa = [&] () {
        for(int i = 1 ; i <= cnt ; ++ i) {
            dis[i] = -inf;
            pre[i] = 0;
        }
        queue<int> q;
        q.push(S), dis[S] = 0, inq[S] = 1;
        while(q.size()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for(int i = head[u] ; i ; i = rest[i]) {
                int v = to[i];
                if(flow[i] && dis[v] < dis[u] + cost[i]) {
                    dis[v] = dis[u] + cost[i];
                    pre[v] = i;
                    if(!inq[v]) {
                        inq[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return dis[T] > 0; // 要求最大
        // return dis[T] != -inf;
    };
    auto mcmf = [&] () {
        ll res = 0;
        while(spfa()) {
            int mn = inf;
            for(int i = pre[T] ; i ; i = pre[from[i]]) {
                mn = min(mn, flow[i]);
            }
            for(int i = pre[T] ; i ; i = pre[from[i]]) {
                flow[i] -= mn, flow[i ^ 1] += mn;
            }
            // printf("flow = %d, dis = %lld\n", mn, dis[T]);
            res += mn * dis[T];
        }
        return res;
    };

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(str[i][j] == 'S') {
                add(S, ids[i][j][0], 1, 0);
            }
            if(str[i][j] != '#') {
                for(auto e: vals[i][j][t]) {
                    add(ids[i][j][t], T, 1, e);
                }
            }
        }
    }
    for(int tm = 0 ; tm < t ; ++ tm) {

        // 临时搞出来一层
        int tmp[n + 10][m + 10];
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= m ; ++ j) {
                tmp[i][j] = ++ cnt;
                add(tmp[i][j], ids[i][j][tm + 1], 1, 0);
            }
        }

        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= m ; ++ j) {
                if(str[i][j] != '#') {
                    static int mv[5][2] = {
                        { 0, 1 },
                        { 0, -1 },
                        { 1, 0 },
                        { -1, 0 }
                    };
                    for(int k = 0 ; k < 4 ; ++ k) {
                        int nx = i + mv[k][0], ny = j + mv[k][1];
                        if(1 <= nx && nx <= n && 1 <= ny && ny <= m && str[nx][ny] != '#') {
                            add(ids[i][j][tm], tmp[nx][ny], 1, 0);
                        }
                    }
                    for(auto e: vals[i][j][tm]) {
                        add(ids[i][j][tm], tmp[i][j], 1, e);
                    }
                }
            }
        }
    }


    printf("%lld\n", mcmf());


    // -----------------------------------------END----------------------------------------

    return 0;
}
