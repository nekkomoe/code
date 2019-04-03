#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
 
const int N = 5e5 + 10, mod = 1005060097;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

const ll g[2] = { 5, pw(5, mod - 2) };
 
char s[N];

int p, q, np, nq, ch[N][26], last = 1, cnt = 1, pre[N], len[N], n, sz[N], tmp[N], bak[N];
 
int nd(int l) {
    return len[++ cnt] = l, cnt;
}
 
void ins(int c) {
    pre[last = np = nd(len[p = last] + 1)] = 1, sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int k, m;
ll num[N];

ll f[N];

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
int REV[N], inv, tpw[2][N];
void ntt(int *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) f[REV[i]] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        int wn = tpw[ty][i];
        for(int j = 0 ; j < n ; j += i) {
            int w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                int u = f[k], v = (ll) w * f[k + i / 2] % mod;
                f[k] = (ll) (u + v) % mod;
                f[k + i / 2] = (ll) (u - v) % mod;
                w = (ll) w * wn % mod;
            }
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty) a[i] = (ll) a[i] * inv % mod;
    }
}

int a[N], b[N], c[N], ans;

void runprog() {
    int len = 1; while(len < 2 * n) len <<= 1;
    for(int i = 0 ; i < len ; ++ i) REV[i] = rev(i, len);
    for(int i = 2 ; i <= len ; i <<= 1) {
        for(int ty = 0 ; ty < 2 ; ++ ty) {
            tpw[ty][i] = pw(g[ty], (mod - 1) / i);
        }
    }
    inv = pw(len, mod - 2);
    for(int i = 1 ; i <= n ; ++ i) b[i] = num[i];
    a[0] = 1;
    for( ; k ; k >>= 1) {
        if(k & 1) {
            ntt(a, 0, len);
            for(int i = 0 ; i < len ; ++ i) c[i] = b[i];
            ntt(c, 0, len);
            for(int i = 0 ; i < len ; ++ i) a[i] = (ll) a[i] * c[i] % mod;
            ntt(a, 1, len);
            for(int i = n + 1 ; i < len ; ++ i) a[i] = 0;
        }
        ntt(b, 0, len);
        for(int i = 0 ; i < len ; ++ i) b[i] = (ll) b[i] * b[i] % mod;
        ntt(b, 1, len);
        for(int i = n + 1 ; i < len ; ++ i) b[i] = 0;
    }
    ans = a[m];
}
int main() {
    scanf("%d%d", &k, &m);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a');
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        sz[pre[bak[i]]] += sz[bak[i]];
    }
    for(int i = 2 ; i <= cnt ; ++ i) {
        (num[sz[i]] += (ll) sz[i] * (len[i] - len[pre[i]]) % mod) %= mod;
    }
    runprog();
    printf("%d\n", (ans % mod + mod) % mod);
}
