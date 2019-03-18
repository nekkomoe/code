#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, a[N], c[N];

namespace ISSCC {
    int vis[N];
    int isscc() {
        int x = 1, flag = 0;
        while(!vis[x]) {
            vis[x] = 1;
            x = a[x];
            if(x == 1) {
                flag = 1;
                break;
            }
        }
        if(!flag) return 0;
        for(int i = 1 ; i <= n ; ++ i) {
            if(vis[i] == 0) {
                return 0;
            }
        }
        return 1;
    }
}

namespace force {
    ll ans;
    int op[N], deg[N], vis[N];

    int check() {
        for(int i = 1 ; i <= n ; ++ i) deg[i] = 0, vis[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            if(op[i]) {
                ++ deg[a[i]];
            }
        }
        queue<int> q;
        for(int i = 1 ; i <= n ; ++ i) {
            if(!deg[i]) {
                q.push(i);
            }
            if(deg[i] > 1) {
                return 0;
            }
        }
        while(q.size()) {
            int u = q.front(); q.pop();
            vis[u] = 1;
            if(op[u]) {
                int v = a[u];
                if(! -- deg[v]) {
                    q.push(v);
                }
            }
        }
        for(int i = 1 ; i <= n ; ++ i) {
            if(!vis[i]) {
                return 0;
            }
        }
        return 1;
    }

    void dfs(int stp, ll sum = 0) {
        if(sum >= ans) return ;
        if(stp == n + 1) {
            if(check()) {
                ans = sum;
            }
        } else {
            op[stp] = 0, dfs(stp + 1, sum + c[stp]);
            op[stp] = 1, dfs(stp + 1, sum);
        }
    }

    void sol() {
        for(int i = 1 ; i <= n ; ++ i) ans += c[i];
        dfs(1);
        printf("%lld\n", ans);
    }
}

// 一脸不可写
namespace base_circle_tree {

    int dfn[N], low[N], clk, id[N], ins[N], cnt;
    vector<int> vec[N];

    stack<int> sta;

    void dfs(int u) {
        dfn[u] = low[u] = ++ clk;
        sta.push(u);
        ins[u] = 1;
        int v = a[u];
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]){
            low[u] = min(low[u], dfn[v]);
        }
        if(dfn[u] == low[u]) {
            cnt ++;
            int v;
            do {
                v = sta.top();
                sta.pop();
                ins[v] = 0;
                id[v] = cnt;
                vec[cnt].push_back(v);
            } while(u != v);
        }
    }

    ll ans;
    ll cost[N], t[N], s[N], f[N], allsum;

    int que[N], l, r, len;

    int arr[N], arr_cnt;

    ll get(int l, int r) {
        f[l - 1] = 0;
        int tmpl = t[l]; t[l] = 0;
        for(int i = l ; i <= r ; ++ i) {
            f[i] = f[i - 1] + t[i];
            for(int j = l - 1 ; j < i ; ++ j) {
                f[i] = min(f[i], f[j] + s[i] - s[j + 1] + t[j + 1]);
            }
            // printf("s[%d] = %lld\n", i, s[i]);
        }
        t[l] = tmpl;

        // for(int i = l ; i <= r ; ++ i) {
        //     printf("%lld ", f[i]);
        // } puts("");

        return f[r] + t[l];
    }

    ll runprog(int P) {

        // 先拆环为链
        arr_cnt = 0;
        for(int i = 0 ; i < vec[P].size() ; ++ i) {
            arr[++ arr_cnt] = vec[P][i];
        }
        len = arr_cnt;
        for(int i = 0 ; i < vec[P].size() ; ++ i) {
            arr[++ arr_cnt] = vec[P][i];
        }

        // for(int i = 1 ; i <= arr_cnt ; ++ i) {
        //     printf("%d ", arr[i]);
        // } puts("");

        arr[0] = vec[P].back();
        for(int i = 1 ; i <= arr_cnt ; ++ i) {
            t[i] = c[arr[i - 1]];
            s[i] = s[i - 1] + cost[arr[i]];
        }

        ll res = allsum;

        for(int i = 1 ; i <= arr_cnt ; ++ i) {
            if(i >= len) {
                res = min(res, get(i - len + 1, i));
            }
        }

        l = 1, r = 0;

        // printf("res = %lld\n", res);

        return res;
    }

    void sol() {

        for(int i = 1 ; i <= n ; ++ i) {
            if(!dfn[i]) {
                dfs(i);
            }
            allsum += c[i];
        }

        for(int u = 1 ; u <= n ; ++ u) {
            if(vec[id[u]].size() == 1) {
                int fa = a[u];
                // if(vec[id[fa]].size() != 1) {
                    // printf("%d -> %d\n", u, fa);
                    if(c[u] >= cost[fa]) {
                        ans += cost[fa];
                        cost[fa] = c[u];
                    } else {
                        ans += c[u];
                    }
                // }
            }
        }

        // for(int i = 1 ; i <= n ; ++ i) {
        //     printf("u = %d, cost = %lld, belsz = %d\n", i, cost[i], (int) vec[id[i]].size());
        // }

        for(int i = 1 ; i <= cnt ; ++ i) {
            if(vec[i].size() != 1) {
                reverse(vec[i].begin(), vec[i].end());
                ans += runprog(i);
            }
        }

        printf("%lld\n", ans);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &a[i], &c[i]);
    }

    if(ISSCC :: isscc()) {
        puts("0");
    } else {
        base_circle_tree :: sol();
    }
}
