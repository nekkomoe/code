#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 10;

struct E { int u, v, w; } e[N];

int n, m, d;

namespace checkunsolvable {
    int fa[N];
    inline int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
    inline bool check() {
        for(int i = 1 ; i <= n ; ++ i) fa[i] = i;
        for(int i = 1 ; i <= m ; ++ i) fa[get(e[i].u)] = get(e[i].v);
        for(int i = 1 ; i <= d ; ++ i) if(get(i) != get(n - i + 1)) return 1;
        return 0;
    }
}

namespace pianfen_spfa {

    int head[N], rest[N], from[N], to[N], w[N], tot = 1, pre[N], dis[N], s, t, rev[N];

    int a[N], vis[N], b[N], res;

    inline void add(int u, int v, int ww) { from[++ tot] = u, to[tot] = v, w[tot] = ww, rest[tot] = head[u], head[u] = tot; }

    struct T { int u, w; };

    inline bool operator < (T a, T b) { return a.w > b.w; }

    priority_queue<T> q;

    int spfa() {
        memset(dis, 0x3f, (sizeof(int)) * (n + 1));
        dis[s] = 0, q.push((T) { s, 0 });
        while(q.size()) {
            T t = q.top(); q.pop();
            int u = t.u;
            if(t.w > dis[u]) continue;
            for(int i = head[u], v ; i ; i = rest[i])
                if(dis[v = to[i]] > dis[u] + w[i])
                    dis[v] = dis[u] + w[i], pre[v] = i, q.push((T) { v, dis[v] });
        }
        int ret = 0;
        for(int i = pre[t] ; ; i = pre[from[i]]) {
            ret += w[i], w[i] = w[i ^ 1] = 0;
            if(ret >= res) break;
            if(from[i] == s) break;
        }
        return ret;
    }

    inline int sub() {

        for(int i = 1, t = 2 ; i <= m ; ++ i, t += 2) w[t] = w[t + 1] = e[i].w;

        int ans = 0;
        for(int _ = 1 ; _ <= d ; ++ _) {
            int i = a[_];
            s = i, t = n - i + 1;
            if(b[i]) swap(s, t);
            ans += spfa();
            if(ans >= res) break;
        }
        return ans;
    }

    inline int sol() {
        for(int i = 1 ; i <= m ; ++ i)
            add(e[i].u, e[i].v, e[i].w),
            rev[tot] = tot + 1,
            add(e[i].v, e[i].u, e[i].w),
            rev[tot] = tot - 1;
        for(int i = 1 ; i <= d ; ++ i) a[i] = i;
        sort(a + 1, a + 1 + d);
        res = 0x3f3f3f3f;
        do {
            for(int s = 0 ; s < (1 << d) ; ++ s) {
                for(int i = 1 ; i <= d ; ++ i) b[i] = (s >> (i - 1)) & 1;
                res = min(res, sub());
            }
        } while(next_permutation(a + 1, a + 1 + d));
        return res;
    }
}

template<typename T> inline void read(T &x) {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    read(n), read(m), read(d);
    for(int i = 1, u, v, w ; i <= m ; ++ i) read(e[i].u), read(e[i].v), read(e[i].w);
    if(checkunsolvable :: check()) puts("-1");
    else printf("%d\n", pianfen_spfa :: sol());
}

