#include <bits/stdc++.h>
#include <sys/mman.h>
#include <unistd.h>
using namespace std;
typedef long long ll;

struct FastIO {
    static const int S = 1e8;
    int wpos;
    char wbuf[S];
    char *buf;
    FastIO() {
        fseek(stdin, 0, SEEK_END);
        register int file_lenth = ftell(stdin);
        rewind(stdin);
        buf = (char *) mmap( 0, file_lenth ,PROT_READ, MAP_PRIVATE, fileno(stdin), 0 ) - 1;
    }
    inline int operator () () {
        register int c = 0, x = 0;
        while ((c = *++buf) <= 32);
        for (; isdigit(c) ; c = *++buf) x = x * 10 + c - '0';
        return x;
    }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
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


const int mod = 1e9 + 7, N = 3e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

int n, q, a[N], m;

ll fac[N];

void lsh() {

    fac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }

    vector<int> num;
    for(int i = 1 ; i <= n ; ++ i) {
        num.emplace_back(a[i]);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    m = num.size();
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1;
    }
}
int L[N], R[N], ids[N], lim;

const int LEN = 550;
int cnt[1500][N]; // 数字i在前j块出现次数
int f[1500][1500];

int pak[N];
inline void mul(ll &x, ll y) {
    // x = x * y % mod;
    (x *= y) >= mod ? x %= mod : 0;
}

int blol, blor;
int *gcr, *gcl;
inline int getcnt(int x) {
    // return cnt[x][blor] - cnt[x][blol - 1];
    // return cnt[blor][x] - cnt[blol - 1][x];
    return gcr[x] - gcl[x];
}

ll sol(int l, int r) {
    ll res = 1;

    if(ids[l] == ids[r] || ids[l] + 1 == ids[r]) {
        for(int i = l ; i <= r ; ++ i) {
            int x = a[i];
            mul(res, ++ pak[x]);
        }
        for(int i = l ; i <= r ; ++ i) {
            pak[a[i]] = 0;
        }
    } else {
        // blol = ids[l] + 1, blor = ids[r] - 1;
        gcl = cnt[ids[l]], gcr = cnt[ids[r] - 1];
        mul(res, f[ids[l] + 1][ids[r] - 1]);
        for(int i = l ; i <= R[ids[l]] ; ++ i) {
            int x = a[i];
            mul(res, ++ pak[x] + getcnt(x));
        }
        for(int i = L[ids[r]] ; i <= r ; ++ i) {
            int x = a[i];
            mul(res, ++ pak[x] + getcnt(x));
        }

        for(int i = l ; i <= R[ids[l]] ; ++ i) {
            pak[a[i]] = 0;
        }
        for(int i = L[ids[r]] ; i <= r ; ++ i) {
            pak[a[i]] = 0;
        }
    }

    return fac[r - l + 1] * pw(res, mod - 2) % mod;
}

int main() {
    n = io(), q = io();
    int LEN = sqrt(n) + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = io();
        int x = ids[i] = (i - 1) / LEN + 1;
        R[x] = i;
        if(!L[x]) L[x] = i;
    }
    lsh();
    lim = ids[n];
    
    for(int j = 1 ; j <= lim ; ++ j) {
        for(int i = 1 ; i <= m ; ++ i) {
            cnt[j][i] = cnt[j - 1][i];
        }
        for(int i = L[j] ; i <= R[j] ; ++ i) {
            ++ cnt[j][a[i]];
        }
    }

    for(int i = 1 ; i <= lim ; ++ i) {

        ll res = 1;
        for(int j = L[i] ; j <= n ; ++ j) {
            int x = a[j];
            mul(res, ++ pak[x]);
            if(R[ids[j]] == j) {
                f[i][ids[j]] = res;
            }
        }

        for(int j = L[i] ; j <= n ; ++ j) {
            pak[a[j]] = 0;
        }
    }

    ll lastans = 0;
    while(q --) {
        int L1 = io(), L2 = io(), R1 = io(), R2 = io();
        int L = ((ll) L1 * lastans % n + L2) % n + 1;
        int R = ((ll) R1 * lastans % n + R2) % n + 1;

        // int L = io(), R = io();

        if(L > R) swap(L, R);
        io(lastans = sol(L, R));
    }
}
