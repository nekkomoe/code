#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a %  b) : a;
}

int n, q;

int id[N], L[N], R[N], cnt, len;

ll val[N], a[N], endgcd[N], allxorsum[N];

void rebuild(int i) {
    a[L[i]] = endgcd[i] = val[L[i]];
    for(int j = L[i] + 1 ; j <= R[i] ; ++ j) {
        endgcd[i] = gcd(endgcd[i], val[j]);
        a[j] = a[j - 1] ^ val[j];
    }
    allxorsum[i] = a[R[i]];
    sort(a + L[i], a + R[i] + 1);
}

int checkhas(int l, int r, ll val) {
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(a[mid] == val) return 1;
        else if(a[mid] < val) l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}

void init() {
    len = max((int) sqrt(n), 1);
    for(int i = 1 ; i <= n ; ++ i) {
        id[i] = (i - 1) / len + 1;
        cnt = id[i];
        if(!L[cnt]) L[cnt] = i; R[cnt] = i;
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        rebuild(i);
    }
}

void ask(ll x) {
    int ans = -1;
    ll sumgcd = val[1], sumxor = 0;
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(gcd(sumgcd, endgcd[i]) == sumgcd) {
            if(x % sumgcd == 0) {
                ll tmpx = x, tmpsum = 0;
                x = (x / sumgcd) ^ sumxor;
                if(checkhas(L[i], R[i], x)) {
                    for(int j = L[i] ; j <= R[i] ; ++ j) {
                        tmpsum ^= val[j];
                        sumxor ^= val[j];
                        if(tmpsum == x) {
                            ans = j;
                            break;
                        }
                    }
                    break;
                }   
                x = tmpx;
            }       
            sumxor ^= allxorsum[i];
        } else {
            for(int j = L[i] ; j <= R[i] ; ++ j) {
                sumgcd = gcd(sumgcd, val[j]);
                sumxor ^= val[j];
                if(sumxor * sumgcd == x) {
                    ans = j;
                    break;
                }
            }
            if(ans != -1) break;
        }
    }
    if(ans == -1) puts("no");
    else printf("%d\n", ans - 1);
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        val[i] = a[i];
    }
    init(); 
    scanf("%d", &q);
    for(int i = 1 ; i <= q ; ++ i) {
        char op[10]; scanf("%s", op);
        if(op[0] == 'M') {
            int pos, x; scanf("%d%d", &pos, &x); ++ pos;
            val[pos] = x;
            rebuild(id[pos]);
        } else if(op[0] == 'Q') {
            ll x; scanf("%lld", &x);
            ask(x);
        } 
    }
} 

