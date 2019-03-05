#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 510;

struct P {
    int x, y;
    ll dot(const P&p) const { return (ll) x * p.x + (ll) y * p.y; }
    ll det(const P&p) const { return (ll) x * p.y - (ll) y * p.x; }

};

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}

P panel[10010], winend, fly[N * N];
int n, k;

int check_all_in_window(int dx, int dy) {
    for(int i = 0 ; i < k ; ++ i) {
        int nx = panel[i].x + dx, ny = panel[i].y + dy;
        if(!(0 <= nx && nx <= winend.x && 0 <= ny && ny <= winend.y)) {
            return 0;
        }
    }
    return 1;
} 

const double EPS = 1e-7;
inline int sign(const double &a) {return a < -EPS ? -1 : a > EPS;}

inline bool inSeg(P u, P v, P p) { return sign((u - p).det(v - p)) == 0 && sign((u - p).dot(v - p)) <= 0; }

int nxt[10010];

inline int check_in_pol(P p) {
    int ret = 0;
    for(int i = 0; i < k; ++ i) {
        P u = panel[i], v = panel[nxt[i]];
        if (inSeg(u, v, p)) return true;
        if (sign(u.y - v.y) <= 0) swap(u, v);
        if (sign(p.y - u.y) > 0 || sign(p.y - v.y) <= 0) continue;
        ret += sign((v - p).det(u - p)) > 0;
    }
    return ret & 1;
}

int temp[N][N], ans, fly_vis[N][N];







int temp_blo[N * N], temp_top;

int fly_blo[N * N], fly_top;

const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 };

const int FFTN = 1e6;
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

int pxlen = 0, pylen = 0;

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


    // for(int i = 1 ; i <= winend.x ; ++ i) {
    //     for(int j = 1 ; j <= winend.y ; ++ j) {
    //         printf("%d ", temp[i][j]);
    //     } puts("");
    // } puts("");

    // for(int i = 1 ; i <= winend.x ; ++ i) {
    //     for(int j = 1 ; j <= winend.y ; ++ j) {
    //         printf("%d ", fly_vis[i][j]);
    //     } puts("");
    // } puts("");

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

    // truegetA(fly_top);

    for(int i = 0 ; i < temp_top ; ++ i) {
        // printf("%d ", A[temp_top + i - 1] != 0);
        A[i] = A[temp_top + i - 1] != 0;
    }
    // puts("");

    // cout << pxlen << ' ' << pylen << endl;
    // cout << winend.x << ' ' << winend.y << endl;

    for(int i = 0 ; i < temp_top ; ++ i) {
        A[i] = (A[i] + mod) % mod;
        // printf("%lld ", A[i] & 1);
        if(A[i] == 0) {
            P res = bak[i];
            if(res.x + pxlen - 1 <= winend.x) {
                if(res.y + pylen - 1 <= winend.y) {
                    ++ ans;
                    // printf("(%d, %d), %d, %d\n", res.x, res.y, res.x + pxlen - 1, res.y + pylen - 1);
                }
            }
        }
    }
    // puts("");

}












int main() {



    // test for ntt
    // for(int i = 0 ; i < 3 ; ++ i) A[i] = B[i] = 1;
    // int len = 16;
    // ntt(A, 0, len), ntt(B, 0, len);
    // for(int i = 0 ; i < len ; ++ i) {
    //     A[i] = A[i] * B[i] % mod;
    // }
    // ntt(A, 1, len);
    // for(int i = 0 ; i < len ; ++ i) {
    //     printf("%lld ", (A[i] + mod) % mod);
    // } puts("");







    scanf("%d%d%d", &winend.x, &winend.y, &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &fly[i].x, &fly[i].y);
    }
    scanf("%d", &k);
    for(int i = 0 ; i < k ; ++ i) {
        nxt[i] = i + 1;
        scanf("%d%d", &panel[i].x, &panel[i].y);
    }
    nxt[k - 1] = 0;

    // int ans = 0;
    // for(int delx = -panel[1].x ; delx <= winend.x - panel[1].x ; ++ delx) {
    //     for(int dely = -panel[1].y ; dely <= winend.y - panel[1].y ; ++ dely) {
    //         if(check_all_in_window(delx, dely)) {
    //             for(int i = 0 ; i < k ; ++ i) {
    //                 panel[i].x += delx;
    //                 panel[i].y += dely;
    //             }
    //             int flag = 1;
    //             for(int i = 1 ; i <= n ; ++ i) {
    //                 if(check_in_pol(fly[i])) {
    //                     flag = 0;
    //                     break;
    //                 }
    //             }
    //             ans += flag;

    //             for(int i = 0 ; i < k ; ++ i) {
    //                 panel[i].x -= delx;
    //                 panel[i].y -= dely;
    //             }
    //         }
    //     }
    // }

    int mnx = panel[1].x, mny = panel[1].y;
    for(int i = 0 ; i < k ; ++ i) {
        mnx = min(mnx, panel[i].x);
        mny = min(mny, panel[i].y);
    }
    for(int i = 0 ; i < k ; ++ i) {
        panel[i].x -= mnx;
        panel[i].y -= mny;
        if(!(0 <= panel[i].x && panel[i].x <= winend.x && 0 <= panel[i].y && panel[i].y <= winend.y)) {
            puts("0");
            return 0;
        }
    }

    // all += 1
    winend.x ++, winend.y ++;
    for(int i = 0 ; i < k ; ++ i) {
        panel[i].x ++;
        panel[i].y ++;
        pxlen = max(pxlen, panel[i].x);
        pylen = max(pylen, panel[i].y);
    }
    for(int i = 1 ; i <= pxlen ; ++ i) {
        for(int j = 1 ; j <= pylen ; ++ j) {
            if(check_in_pol((P) { i, j })) {
                temp[i][j] = 1;
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        fly[i].x ++;
        fly[i].y ++;
        fly_vis[fly[i].x][fly[i].y] = 1;
    }

    runprog();



    printf("%d\n", ans);
}
