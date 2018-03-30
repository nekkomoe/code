%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 100010;
const ll inf = 0x3f3f3f3f3f3f3f3fll;

ll a[N], b[N], g[N], ans;
int n, f[N], mx, bak[N];
struct P { ll x, y; };
vector<P> sta;

P operator - (P a, P b) { return (P) { a.x - b.x, a.y - b.y }; }
ll crs(P a, P b) { return a.x * b.y - b.x * a.y; }
bool cmp(int i, int j) { return a[i] - i == a[j] - j ? i < j : a[i] - i < a[j] - j; }
ll getx(ll i) { return 2 * (a[i] - i); }
ll gety(ll i) { return i * (i + 1) - 2 * i * a[i] - 2 * a[i] + 2 * g[i]; }
ll getg(ll i, P j) { return (j.x * i + i * (i - 1) + j.y) / 2 + a[i] + b[i]; }
void cdq(int l, int r) {
    if(l == r) return ;
    int mid = (l + r) >> 1, mx = -1;
    cdq(l, mid);
    for(int i = l ; i <= r ; ++ i) bak[i - l + 1] = i;
    sort(bak + 1, bak + 1 + r - l + 1, cmp);
    for(int _ = 1, i ; _ <= r - l + 1 ; ++ _) {
        if((i = bak[_]) <= mid) {
            if(f[i] < mx || (i != 0 && !f[i])) continue;
            if(f[i] > mx) sta.clear(), mx = f[i];
            P p = (P) { getx(i), gety(i) };
            while(sta.size() > 1 && crs(sta[sta.size() - 1] - sta[sta.size() - 2], p - sta[sta.size() - 1]) <= 0) sta.pop_back();
            sta.push_back(p);
        } else {
            if(f[i] > mx + 1) continue;
            if(f[i] < mx + 1) g[i] = inf;
            f[i] = mx + 1;
            int L = 0, R = sta.size() - 1;
            while(R - L > 2) {
                int m1 = (R - L) / 3 + L, m2 = (R - L) / 3 * 2 + L;
                if(sta[m1].x * i + sta[m1].y > sta[m2].x * i + sta[m2].y) L = m1 + 1;
                else R = m2 - 1;
            }
            for(int j = L ; j <= R ; ++ j) g[i] = min(g[i], getg(i, sta[j]));
        }
    }
    cdq(mid + 1, r);
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &b[i]);
    for(int i = 1 ; i <= n ; ++ i) g[i] = inf;
    cdq(0, n);
    for(int i = 1 ; i <= n ; ++ i) {
        g[i] += (ll) (n - i) * (a[i] + 1) + (ll) (n - i) * (n - i - 1) / 2;
        if(mx < f[i]) mx = f[i], ans = g[i]; else if(mx == f[i]) ans = min(ans, g[i]);
    }
    printf("%d %lld\n", mx, ans);
}


