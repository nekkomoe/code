#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1510, MAXN = 5e6 + 10;

struct P {
    int x, y;
    ll dot(const P&p) const { return (ll) x * p.x + (ll) y * p.y; }
    ll det(const P&p) const { return (ll) x * p.y - (ll) y * p.x; }

};

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}

P winend, fly[MAXN], poly[MAXN];
int n;

int temp[N][N], ans, fly_vis[N][N];

int temp_blo[N * N], temp_top;

int fly_blo[N * N], fly_top;

const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 };

const int FFTN = 1e7 + 10;
ll A[FFTN], B[FFTN], F[FFTN];

int rev(int x, int n) {
    int res = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        res = (res << 1) | ((x >> i) & 1);
    }
    return res;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

void ntt(ll *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) {
        F[rev(i, n)] = a[i];
    }

    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = F[k], v = w * F[k + i / 2] % mod;
                F[k] = (u + v) % mod;
                F[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }

    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = F[i];
        if(ty) {
            a[i] = a[i] * inv % mod;
        }
    }
}

P bak[FFTN];

int pxlen, pylen;

ll C[FFTN];


void truegetA(int len) {

    // for(int i = 0 ; i < len ; ++ i) {
    //     printf("%lld ", A[i]);
    // } puts("");

    // for(int i = 0 ; i < len ; ++ i) {
    //     printf("%lld ", B[i]);
    // } puts("");

    for(int i = 0 ; i < len ; ++ i) {
        // C[i]
        C[i] = 0;
        for(int j = 0 ; j < len ; ++ j) {
            if(A[i + j] && B[j]) {
                C[i] = 1;
                break;
            }
        }
    }
    for(int i = 0 ; i < len ; ++ i) {
        A[i] = C[i];
        // printf("%lld ", A[i]);
    }
    // puts("");
}

void runprog() {
    for(int i = 1 ; i <= winend.x ; ++ i) {
        for(int j = 1 ; j <= winend.y ; ++ j) {
            temp_blo[++ temp_top] = temp[i][j];
            fly_blo[++ fly_top] = fly_vis[i][j];
            bak[temp_top - 1] = (P) { i, j };
        }
    }
    int mxlen = fly_top;
    int len = 1; while(len <= mxlen * 2) len <<= 1;
    for(int i = 1 ; i <= temp_top ; ++ i) {
        A[i - 1] = fly_blo[i];
        B[i - 1] = temp_blo[i];
    }


    reverse(B, B + temp_top);
    ntt(A, 0, len), ntt(B, 0, len);
    for(int i = 0 ; i < len ; ++ i) {
        A[i] = A[i] * B[i] % mod;
    }
    ntt(A, 1, len);
    for(int i = 0 ; i < len ; ++ i) {
        A[i] = (A[i] + mod) % mod;
    }

    for(int i = 0 ; i < temp_top ; ++ i) {
        A[i] = A[temp_top + i - 1] != 0;
    }

    // truegetA(len);


    for(int i = 0 ; i < temp_top ; ++ i) {
        A[i] = (A[i] + mod) % mod;
        if(A[i] == 0) {
            P res = bak[i];
            if(res.x + pxlen - 1 <= winend.x) {
                if(res.y + pylen - 1 <= winend.y) {
                    ++ ans;
                    // printf("(%d, %d)\n", res.x, res.y);
                }
            }
        }
    }

    // cout << pxlen << ' ' << pylen << endl;
}

char str[MAXN];
int main() {
    scanf("%d%d%d", &winend.x, &winend.y, &n);
    for(int i = 1 ; i <= winend.x ; ++ i) {
        scanf("%s", str + 1);
        for(int j = 1 ; j <= winend.y ; ++ j) {
            fly_vis[i][j] = str[j] - '0';
        }
    }

    int pol_cnt = 0;
    P now = (P) { 1, 1 };
    poly[++ pol_cnt] = now;

    map<char, pair<int, int> > trans;
    trans['w'] = make_pair(-1, 0);
    trans['s'] = make_pair(1, 0);
    trans['a'] = make_pair(0, -1);
    trans['d'] = make_pair(0, 1);

    scanf("%s", str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        int dx = trans[str[i]].first, dy = trans[str[i]].second;
        now.x += dx, now.y += dy;
        poly[++ pol_cnt] = now;
        // printf("(%d, %d)\n", now.x, now.y);
    }

    int mnx = poly[1].x, mny = poly[1].y;
    for(int i = 1 ; i <= pol_cnt ; ++ i) {
        mnx = min(mnx, poly[i].x);
        mny = min(mny, poly[i].y);
    }
    for(int i = 1 ; i <= pol_cnt ; ++ i) {
        poly[i].x = poly[i].x - mnx + 1;
        poly[i].y = poly[i].y - mny + 1;
        temp[poly[i].x][poly[i].y] = 1;
        pxlen = max(pxlen, poly[i].x);
        pylen = max(pylen, poly[i].y);
    }

    // for(int i = 1 ; i <= winend.x ; ++ i) {
    //     for(int j = 1 ; j <= winend.y ; ++ j) {
    //         printf("%d ", fly_vis[i][j]);
    //     }
    //     puts("");
    // }
    // puts("");
    // for(int i = 1 ; i <= winend.x ; ++ i) {
    //     for(int j = 1 ; j <= winend.y ; ++ j) {
    //         printf("%d ", temp[i][j]);
    //     }
    //     puts("");
    // }

    runprog();
    printf("%d\n", ans);
}
