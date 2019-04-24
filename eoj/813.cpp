#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 998244353;

using namespace std;
// orz laofudasuan
// modified

namespace io {
const int SIZE = (1 << 21) + 1;
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
// print the remaining part
inline void flush() {
    fwrite(obuf, 1, oS - obuf, stdout);
    oS = obuf;
}
// putchar
inline void putc(char x) {
    *oS++ = x;
    if (oS == oT)
        flush();
}
// input a signed integer
template <class I>
inline void gi(I &x) {
    for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
        if (c == '-')
            f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
    x *= f;
}
// print a signed integer
template <class I>
inline void print(I x) {
    if (!x)
        putc('0');
    if (x < 0)
        putc('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putc(qu[qr--]);
}
// no need to call flush at the end manually!
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io ::gi;
using io ::print;
using io ::putc;

ll a[100];
int n, q;

int check(int x) {
    for(int i = 31 ; ~ i ; -- i) {
        if (x & (1ll << i)) {
            if (!a[i]) {
                return 1;
            }
            x ^= a[i];
        }
    }
    return 0;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for (; b; b >>= 1, a = a * a % mod) {
        if (b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int main() {
// #ifdef ONLINE_JUDGE
//     freopen("xor.in", "r", stdin);
//     freopen("xor.out", "w", stdout);
// #endif
    int tot = 0;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        int x; scanf("%d", &x);
        for (int j = 31; ~j; --j) {
            if (x & (1ll << j)) {
                if (!a[j]) {
                    a[j] = x;
                    break;
                }
                x ^= a[j];
            }
        }
    }
    for (int i = 0; i <= 31; ++i) {
        if (a[i]) {
            ++tot;
        }
    }
    // printf("tot = %d\n", tot);
    ll tmp = pw(2, n - tot);
    while (q--) {
        int x;
        gi(x);
        if (check(x)) {
            // putc('0');
            puts("0");
        } else {
            // print(tmp);
            printf("%lld\n", tmp);
        }
        // putc('\n');
    }
}
