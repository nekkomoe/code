#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, P = 1e5;
int n, m, a, T, p[N], tot, vis[N], g[N], mu[N], sum[N];

struct Q {
    int n, m, id, a, ans;
} q[N]; bool operator < (Q a, Q b) { return a.a < b.a; }
bool cmp_q_id(Q a, Q b) { return a.id < b.id; }

struct F {
    int d, id;
} f[N]; bool operator < (F a, F b) { return a.d < b.d; }

int pw(int a, int b) {
    int r = 1;
    for( ; b ; b >>= 1, a *= a) if(b & 1) r *= a;
    return r;
}

struct BT {
    int a[N];
    void add(int i, int x) { for( ; i <= P ; i += i & -i) a[i] += x; }
    int sum(int i) { int res = 0; for( ; i ; i -= i & -i) res += a[i]; return res; }
} bt;

int main() {
    f[1].d = f[1].id = mu[1] = 1;
    for(int i = 2 ; i <= P ; ++ i) {
        f[i].id = i;
        if(!vis[i]) {
            p[++ tot] = i;
            mu[i] = -1;
            f[i].d = i + 1;
            g[i] = 1;
            sum[i] = i + 1;
        }
        for(int j = 1 ; j <= tot && i * p[j] <= P ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) {
                // mu[i * p[j]] = 0;
                g[i * p[j]] = g[i] + 1;
                sum[i * p[j]] = sum[i] + pw(p[j], g[i] + 1);
                f[i * p[j]].d = f[i].d / sum[i] * sum[i * p[j]];
                break;
            } else {
                mu[i * p[j]] = -mu[i];
                f[i * p[j]].d = f[i].d * f[p[j]].d;
                g[i * p[j]] = 1;
                sum[i * p[j]] = p[j] + 1;
            }
        }
    }
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++ i) scanf("%d%d%d", &q[i].n, &q[i].m, &q[i].a), q[i].id = i;
    sort(q + 1, q + 1 + T), sort(f + 1, f + 1 + P);
    for(int i = 1, p = 1 ; i <= T ; ++ i) {

        for( ; f[p].d <= q[i].a && p <= P ; ++ p)
            for(int j = 1 ; j * f[p].id <= P ; ++ j)
                bt.add(j * f[p].id, f[p].d * mu[j]);
        if(q[i].n > q[i].m) swap(q[i].n, q[i].m);
        for(int j = 1, k ; j <= q[i].n ; j = k + 1)
            k = min(q[i].n / (q[i].n / j), q[i].m / (q[i].m / j)),
            q[i].ans += (q[i].n / j) * (q[i].m / j) * (bt.sum(k) - bt.sum(j - 1));
    }
    sort(q + 1, q + 1 + T, cmp_q_id);
    for(int i = 1 ; i <= T ; ++ i) printf("%d\n", q[i].ans & 2147483647);
}
