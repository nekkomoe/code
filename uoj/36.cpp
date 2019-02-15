#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const int N = 1e5 + 10; 

int n, k;
ull inp[N], a[N], bs[N];

void build() {
    for(int i = 1 ; i <= n ; ++ i) {
        ull x = inp[i];
        for(ull j = 63 ; ~ j ; -- j) {
            if(x & (1ull << j)) {
                if(!bs[j]) {
                    bs[j] = x;
                    break;
                } else {
                    x ^= bs[j];
                }
            }
        }
    }
    n = 0;
    for(ull j = 63 ; ~ j ; -- j) {
        if(bs[j]) {
            a[++ n] = bs[j];
        }
    }
}

void print(ull x) {
    cout << x / 2;
    if(x % 2) cout << ".5" << endl;
}

typedef __int128 t;

t pw(t a, t b) {
    t r = 1;
    for( ; b ; b >>= 1, a *= a)
        if(b & 1)
            r *= a; 
    return r;
}

int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> inp[i];
    }
    build();
    if(k == 1) {
        ull ans = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            ans |= a[i];
        }
        print(ans);
    } else if(k == 2) {
        ull ans = 0;
        for(int i = 0 ; i <= 63 ; ++ i) {
            for(int j = 0 ; j <= 63 ; ++ j) {
                int f[3] = { 0, 0, 0 };
                for(int k = 1 ; k <= n ; ++ k) {
                    if(a[k] & (1ull << i)) f[0] = 1;
                    if(a[k] & (1ull << j)) f[1] = 1;
                    if(((a[k] >> i) & 1) != ((a[k] >> j) & 1)) f[2] = 1;
                }
                if(f[0] && f[1]) {
                    ans += 1ull << (i + j - f[2]);
                }
            }
        }
        print(ans);
    } else {
        t ans = 0;
        for(ull i = (1ull << n) - 1 ; ~ i ; -- i) {
            ull sum = 0;
            for(int j = 1 ; j <= n ; ++ j) {
                if((i >> (j - 1)) & 1) {
                    sum ^= a[j];
                } 
            }
            ans += pw(sum, k);
        }
        while(n > 1 && ans % 2 == 0) ans /= 2, -- n; 
        print(ans);
    }
}
