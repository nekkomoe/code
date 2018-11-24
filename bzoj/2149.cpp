#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//typedef __int128 ll;
const int N = 1e5 + 10;
int n, a[N], b[N];

int f[N];
ll c[N], g[N];

namespace getf {
    
    vector<int> num;
    int bit[N], cnt;
    int ask(int x) {
        int res = bit[x];
        for( ; x ; x -= x & -x)
            res = min(res, bit[x]);
        return res;
    }
    void mod(int x, int y) {
        for( ; x <= cnt ; x += x & -x)
            bit[x] = min(bit[x], y);
    }
    int get(int x) {
        return lower_bound(num.begin(), num.end(), x) - num.begin() + 1;
    }
    
    void sol() {
        for(int i = 1 ; i <= n ; ++ i) {
            num.push_back(a[i] - i);
        }
        num.push_back(0);
        sort(num.begin(), num.end());
        num.erase(unique(num.begin(), num.end()), num.end());
        cnt = num.size();
        for(int i = 1 ; i <= cnt ; ++ i) bit[i] = 0x3f3f3f3f;
        mod(get(0), 0);
        for(int i = 1 ; i <= n ; ++ i) {
            f[i] = ask(get(a[i] - i));
            f[i] += i - 1;
            mod(get(a[i] - i), f[i] - i);
        }
    }
}

ll u[N], v[N], p[N], q[N], s[N];

namespace getq {
    
    vector<int> num;
    int cnt;
    int get(int x) {
        return lower_bound(num.begin(), num.end(), x) - num.begin() + 1;
    }
    
    int id[N], insid[N], askid[N];
    bool cmp(int x, int y) {
        return a[x] - x < a[y] - y;
    }
    bool cmpeq(int x, int y) {
        return a[x] - x <= a[y] - y;
    }
    
    struct P {
        ll x, y;
        P(ll x = 0, ll y = 0) : x(x), y(y) {}
    };
    ll operator * (P a, P b) {
        // 事实上这个会爆 long long 的 
        return a.x * b.y - b.x * a.y;
    }
    P operator - (P a, P b) {
        return P(a.x - b.x, a.y - b.y);
    }
    
    vector<P> sta[N * 3];
    
    ll calc(P p, ll k) {
        return p.y + k * p.x;
    }
    
    double getk(P a, P b) {
        return (double) (a.y - b.y) / (a.x - b.x);
    }
    
    void cdq(int l, int r) {
        int mid = (l + r) >> 1;
        if(l == r) {
            int i = l;
            g[i] += u[i];
            v[i] = g[i] + (ll) (i - a[i]) * i - s[i];
        } else {
            cdq(l, mid);
            for(int i = l ; i <= r ; ++ i) id[i] = i;
            sort(id + l, id + mid + 1, cmp);
            sort(id + mid + 1, id + r + 1, cmp);
            for(int j = mid + 1, i = l - 1 ; j <= r ; ++ j) {
                while(i + 1 <= mid && cmpeq(id[i + 1], id[j])) {
                    ++ i;
                    // ins i
                    P p = P(q[id[i]], v[id[i]]);
                    // 由于已经按照 ai-i 升序排序了，而且 qi=ai-i，因此横坐标是依次插入的
                    // 也就是说可以暴力维护下凸壳
                    while(sta[insid[id[i]]].size() >= 2) {
                        P a = sta[insid[id[i]]][sta[insid[id[i]]].size() - 1];
                        P b = sta[insid[id[i]]][sta[insid[id[i]]].size() - 2];
                        if((b - a) * (p - a) >= 0) {
                            sta[insid[id[i]]].pop_back();
                        } else {
                            break;
                        }
                    }
                    sta[insid[id[i]]].push_back(p);
                    
                }
                // ask j
                int pos = askid[id[j]];
                
                if(sta[pos].size()) {
                    g[id[j]] = min(g[id[j]], min(calc(sta[pos][0], p[id[j]]), calc(sta[pos].back(), p[id[j]])));
                    ll k = -p[id[j]];
                    int l = 0, r = sta[pos].size() - 2;
                    while(l <= r) {
                        int mid = (l + r) >> 1;
                        // 注意，由于是在叉积面积 >= 0 的时候就弹栈，因此凸壳上相邻两点一定存在斜率
                        if(getk(sta[pos][mid], sta[pos][mid + 1]) > k) {
                            r = mid - 1;
                            g[id[j]] = min(g[id[j]], calc(sta[pos][mid], p[id[j]]));
                        } else {
                            l = mid + 1;
                            g[id[j]] = min(g[id[j]], calc(sta[pos][mid + 1], p[id[j]]));
                        }
                    }
                }
            }
            for(int i = l ; i <= mid ; ++ i) {
                sta[insid[id[i]]].clear();
            }
            cdq(mid + 1, r);
        }
    }
    
    void sol() {
        num.push_back(0);
        for(int i = 0 ; i <= n ; ++ i) {
            num.push_back(a[i] - i);
            num.push_back(f[i] - i);
            num.push_back(f[i] - i + 1);
        }
        sort(num.begin(), num.end());
        num.erase(unique(num.begin(), num.end()), num.end());
        cnt = num.size();
        for(int i = 0 ; i <= n ; ++ i) {
            insid[i] = get(f[i] - i);
            askid[i] = get(f[i] - i + 1); 
        }
        cdq(0, n);
    }
}

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void space(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

int main() {
    n = io();
    for(int i = 1 ; i <= n ; ++ i) a[i] = io();
    for(int i = 1 ; i <= n ; ++ i) b[i] = io();
    a[++ n] = 0x3f3f3f3f, b[n] = 0;
    getf :: sol(); 
    for(int i = 1 ; i <= n ; ++ i) {
        s[i] = s[i - 1] + i;
        u[i] = a[i] + b[i] + s[i - 1];
        p[i] = i - 1;
        q[i] = a[i] - i;
        g[i] = 0x3f3f3f3f3f3f3f3fll;
    }
    getq :: sol();
    io.space(n - 1 - f[n]);
    io.space((long long) (g[n] - a[n])); 
}

