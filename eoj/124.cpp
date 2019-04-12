#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 }, N = 1e7 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
ll f[N];
void ntt(ll *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) {
        f[rev(i, n)] = a[i];
    }
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % mod;
                f[k] = (u + v) % mod;
                f[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }
    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty) {
            a[i] = a[i] * inv % mod;
        }
    }
}

int n;
ll R[N], w[N], sum[N];

int get(int l, int r) {
    int ql = l, qr = r;
    -- r;
    int res = l;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(sum[mid] - sum[ql - 1] <= sum[qr] - sum[mid]) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}
int getlen(int len) {
    int res = 1;
    while(res <= len) res <<= 1;
    return res;
}

ll A[N], B[N];
void getmul(ll *tar, ll *a, ll *b, int len) {
    for(int i = 0 ; i < len ; ++ i) {
        A[i] = a[i];
        B[i] = b[i];
    }
    ntt(A, 0, len), ntt(B, 0, len);
    for(int i = 0 ; i < len ; ++ i) {
        A[i] = A[i] * B[i] % mod;
    }
    ntt(A, 1, len);
    for(int i = 0 ; i < len ; ++ i) {
        tar[i] = A[i];
    }
}

void sol(ll *f, int l, int r) {
    if(l == r) {
        f[0] = 1;
        f[w[l]] = -1;
    } else {
        int mid = get(l, r);
        int len = getlen(sum[r] - sum[l - 1]);
        ll *a = new ll[len + 5];
        ll *b = new ll[len + 5];
        for(int i = 0 ; i < len ; ++ i) {
            a[i] = b[i] = 0;
        }
        sol(a, l, mid), sol(b, mid + 1, r);
        getmul(f, a, b, len);
        delete[] a;
        delete[] b;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &w[i]);
    }
    sort(w + 2, w + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        sum[i] = sum[i - 1] + w[i];
    }

    sol(R, 2, n);

    ll mx = sum[n] - w[1], ans = 0;
    for(int i = 0 ; i <= mx ; ++ i) {
        ans = (ans + R[i] * w[1] % mod * pw(w[1] + i, mod - 2) % mod) % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
