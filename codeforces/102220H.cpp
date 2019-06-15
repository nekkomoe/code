#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

int n, q;
ll a[N], b[N];

struct BIT {
    ll a[N];
    void add(int x, ll v) {
        for( ; x <= n ; x += x & -x) {
            a[x] += v;
        }
    }

    void add(int l, int r, ll v) {

        // for(int i = l ; i <= r;  ++ i) a[i] += v; return ;

        add(l, v), add(r + 1, -v);
    }

    ll ask(int x) {

        // return a[x];

        ll r = 0;
        for( ; x ; x -= x & -x) {
            r += a[x];
        }
        return r;
    }

} bit;

struct SEQ_BIT {
    ll a[N];
    void add(int x, ll v) {

        // a[x] += v;
         // return;

        for( ; x <= n ; x += x & -x) {
            a[x] += v;
        }
    }

    ll ask(int x) {

        // ll s = 0;
        // for(int i = 1 ; i <= x ; ++ i) s += x;
        //     return s;

        ll r = 0;
        for( ; x ; x -= x & -x) {
            r += a[x];
        }
        return r;
    }
    ll ask(int l, int r) {
        return ask(r) - ask(l - 1);
    }
} sbit;

void runprog() {
    scanf("%d%d", &n, &q);

    for(int i = 0 ; i <= n ; ++ i) {
        bit.a[i] = sbit.a[i] = 0;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        bit.add(i, i, a[i]);
        b[i] = a[i] - a[i - 1];
        if(b[i] > 0) {
            sbit.add(i, b[i]);
        }
    }
    for(int i = 1 ; i <= q ; ++ i) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            int k; scanf("%d", &k);
            bit.add(l, r, k);

            // b[l] += k, b[r + 1] -= k;
            if(b[l] > 0) {
                sbit.add(l, -b[l]);
            }
            b[l] += k;
            if(b[l] > 0) {
                sbit.add(l, b[l]);
            }

            if(b[r + 1] > 0) {
                sbit.add(r + 1, -b[r + 1]);
            }
            b[r + 1] -= k;
            if(b[r + 1] > 0) {
                sbit.add(r + 1, b[r + 1]);
            }
        } else {
            ll sum = bit.ask(l);
            if(l + 1 <= r) {
                sum += sbit.ask(l + 1, r);
            }
            // for(int i = l + 1 ; i <= r ; ++ i) {
            //     if(b[i] > 0) {
            //         sum += b[i];
            //     }
            // }
            printf("%lld\n", sum);
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
