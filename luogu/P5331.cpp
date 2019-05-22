// luogu-judger-enable-o2
#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 1e6 + 10, M = 1e6 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
int head[N], rest[M], from[M], to[M], tot = 1;
ll w[M], co[M];
void add_sig(int u, int v, ll w, ll co) {
    from[++ tot] = u, to[tot] = v, :: w[tot] = w, :: co[tot] = co, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, ll w, ll co) {
    add_sig(u, v, w, co), add_sig(v, u, 0, -co);
}
int n, s, t, W, a[N], vis[N];
ll dis[N];
int inq[N], pre[N];
int cnt, pts[N][4]; // in, out, x, y
int spfa() {
    for(int i = 1 ; i <= cnt ; ++ i) dis[i] = inf, pre[i] = 0;
    queue<int> q;
    q.push(s), inq[s] = 1, dis[s] = 0;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i], co = :: co[i];
            if(w[i] && dis[v] > dis[u] + co) {
                dis[v] = dis[u] + co;
                pre[v] = i;
                if(!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return dis[t] != inf;
}

ll getmincost() {
    ll sum = 0;
    while(spfa()) {
        ll mn = inf;
        for(int i = pre[t] ; i ; i = pre[from[i]]) {
            mn = min(mn, w[i]);
        }
        for(int i = pre[t] ; i ; i = pre[from[i]]) {
            w[i] -= mn;
            w[i ^ 1] += mn;
        }
        sum += dis[t] * mn;
    }
    return sum;
}

int ids_lef[N], ids_rig[N];
bool cmp(int i, int j) {
    return make_pair(a[i], i) < make_pair(a[j], j);
}
void nekko(int l, int r) {
    if(l >= r) {
        return ;
    } else {
        int mid = (l + r) >> 1;
        nekko(l, mid), nekko(mid + 1, r);
        int tl = 0, tr = 0;
        // [l, mid]
        for(int i = l ; i <= mid ; ++ i) {
            ids_lef[++ tl] = i;
        }
        // [mid + 1, r]
        for(int i = mid + 1 ; i <= r ; ++ i) {
            ids_rig[++ tr] = i;
        }
        sort(ids_lef + 1, ids_lef + 1 + tl, cmp);
        sort(ids_rig + 1, ids_rig + 1 + tr, cmp);
        vector<int> lk_lef(tr + 3), lk_rig(tr + 3); // 对于 [mid + 1, r]往左连 / 往右连
        for(int i = 1 ; i <= tr ; ++ i) {
            lk_lef[i] = ++ cnt;
            if(lk_lef[i - 1]) {
                add(lk_lef[i], lk_lef[i - 1], inf, 0);
            }
            add(lk_lef[i], pts[ids_rig[i]][1], 1, -a[ids_rig[i]]);
        }
        for(int i = tr ; i >= 1 ; -- i) {
            lk_rig[i] = ++ cnt;
            if(lk_rig[i + 1]) {
                add(lk_rig[i], lk_rig[i + 1], inf, 0);
            }
            add(lk_rig[i], pts[ids_rig[i]][1], 1, a[ids_rig[i]]);
        }
        for(int i = 1 ; i <= tl ; ++ i) {
            for(int j = tr ; j >= 1 ; -- j) {
                if(a[ids_lef[i]] >= a[ids_rig[j]]) {
                    add(pts[ids_lef[i]][2], lk_lef[j], 1, 0);
                    break;
                }
            }
            for(int j = 1 ; j <= tr ; ++ j) {
                if(a[ids_lef[i]] < a[ids_rig[j]]) {
                    add(pts[ids_lef[i]][3], lk_rig[j], 1, 0);
                    break;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &W);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        for(int j = 0 ; j < 4 ; ++ j) {
            pts[i][j] = ++ cnt;
        }
    }
    s = ++ cnt, t = ++ cnt;
    for(int i = 1 ; i <= n ; ++ i) {
        add(s, pts[i][0], 1, 0);
        add(s, pts[i][1], 1, W);

        add(pts[i][0], pts[i][2], 1, a[i]);
        add(pts[i][0], pts[i][3], 1, -a[i]);
        
        add(pts[i][1], t, 1, 0);
    }
    
    nekko(1, n);

    printf("%lld\n", getmincost());
}
