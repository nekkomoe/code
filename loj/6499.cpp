#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define P(a) while(a isdigit(c=getchar()))
void io(int &x) {int c;P(!);x=c-48;P()x=x*10+c-48;}

const int mod = 1e9 + 7, N = 1e5 + 10;

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

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

int n, m, ty;
int ids[N], LEN, a[N], L[N], R[N], ans;
typedef bitset<50005> nekko;

nekko info[10][105], cat;
int lg[N];
int num[N];

int main() {
    io(n), io(m), io(ty);
    LEN = 1000;
    lg[0] = -1;
    for(int i = 1 ; i <= n ; ++ i) {
        io(a[i]);
        num[i] = a[i];
    }
    sort(num + 1, num + 1 + n);
    int top = unique(num + 1, num + 1 + n) - num;
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(num + 1, num + 1 + top, a[i]) - num + 1;
        lg[i] = lg[i >> 1] + 1;
        ids[i] = (i - 1) / LEN + 1;
        if(!L[ids[i]]) {
            L[ids[i]] = i;
        }
        R[ids[i]] = i;
        info[0][ids[i]].set(a[i]);
    }
    int cnt = ids[n];
    for(int j = 1 ; (1 << j) <= cnt ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= cnt ; ++ i) {
            info[j][i] = info[j - 1][i] | info[j - 1][i + (1 << (j - 1))];
        }
    }
    for(int ppp = 0 ; ppp < m ; ++ ppp) {
        int k; io(k);
        int coef = ans; ans = 0;
        cat.reset();
        while(k --) {
            int l, r; io(l), io(r);
            if(ty && ppp) {
                l = (l ^ coef) % n + 1;
                r = (r ^ coef) % n + 1;
            }
            if(l > r) {
                swap(l, r);
            }
            if(ids[l] + 1 >= ids[r]) {
                for(int i = l ; i <= r ; ++ i) {
                    cat.set(a[i]);
                }
            } else {
                for(int i = l ; i <= R[ids[l]] ; ++ i) {
                    cat.set(a[i]);
                }
                for(int i = L[ids[r]] ; i <= r ; ++ i) {
                    cat.set(a[i]);
                }
                l = ids[l] + 1, r = ids[r] - 1;
                int k = lg[r - l + 1];
                cat |= info[k][l] | info[k][r - (1 << k) + 1];
            }
        }
        printf("%d\n", ans = cat.count());
    }
}
