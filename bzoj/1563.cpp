#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

//typedef long long ll;

typedef long double ll;

int n; ll l, p;

const ll MX = 1000000000000000000ll;

string s[N];

int from[N];

ll f[N], sum[N];

struct data {
    int l, r, p;
} dt[N];

ll pw(ll a, ll b) {
    if(a < 0) a = -a;
    ll res = 1;
    for(ll i = 1 ; i <= b ; ++ i) res *= a; 
    return res;
}

ll calc(int j, int i) {
    return f[j] + pw(sum[i] - sum[j] + i - j - 1 - l, p);
}

int get(data x, int y) {
    int l = x.l, r = x.r;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(calc(x.p, mid) < calc(y, mid)) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

void dfs(int u, int fa = n) {
    int ban = 0;
    if(u) dfs(from[u], u);
    for(int i = u + 1 ; i <= fa ; ++ i) {
        cout << s[i];
        if(i < fa) cout << ' ';
        ban = 1;
    }
    if(ban) cout << endl;
}

void sol() {
    cin >> n >> l >> p;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> s[i];
        sum[i] = sum[i - 1] + s[i].length();
    }
    int ql = 1, qr = 1;
    dt[1] = (data) { 0, n, 0 };
    for(int i = 1 ; i <= n ; ++ i) {
        while(ql <= qr && dt[ql].r < i) ql ++;
        f[i] = calc(dt[ql].p, i);
        from[i] = dt[ql].p;
        if(ql > qr || calc(dt[qr].p, n) >= calc(i, n)) {
            while(ql <= qr && calc(dt[qr].p, dt[qr].l) >= calc(i, dt[qr].l)) qr --;
            if(ql <= qr) {
                int t = get(dt[qr], i);
                dt[qr].r = t - 1;
                dt[++ qr] = (data) {t, n, i};
            } else {
                dt[++ qr] = (data) {i, n, i};
            }
        }
    }
    if(f[n] > MX) puts("Too hard to arrange");
    else {
        printf("%lld\n", (long long) f[n]);
//        dfs(n);
    }
}

int main() {
//#ifndef ONLINE_JUDGE
//    freopen("data.in", "r", stdin);
//#endif
    int T; scanf("%d", &T);
    while(T --) sol(), puts("--------------------");
}
