#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

int n, a[N], p[N];

int cnt[N];

int main() {

    // freopen("sort.in", "r", stdin);
    // freopen("sort.out", "w", stdout);

    scanf("%d", &n);
    int maxval = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        p[i] = i;
        maxval = max(maxval, a[i]);
    }
    sort(a + 1, a + 1 + n);

    if(n <= 10) {
        int ans = 0;
        do {
            int x = a[p[1]];
            for(int i = 2 ; i <= n ; ++ i) {
                x %= a[p[i]];
            }
            ans = max(ans, x);
        } while(next_permutation(p + 1, p + 1 + n));
        printf("%d\n", ans);
    } else if(a[1] != a[2]) {
        /*
            首先答案不可能会大于最小值的
            如果最小值唯一，那么答案就可以取到最小值
        */
        printf("%d\n", a[1]);
    } else if(maxval <= 1000) {

        int ans = 0;
        for(int i = 1 ; i <= n ; ++ i) {
             ++ cnt[a[i]];
        }

        set<int> f;
        for(int i = 1 ; i <= maxval ; ++ i) {
            if(cnt[i]) {
                f.emplace(i);
            }
        }
        vector<int> nek;
        for(int j = maxval ; j >= 1 ; -- j) {
            if(cnt[j]) {
                nek.emplace_back(j);
            }
        }

        for(int x: nek) {
            set<int> g = f;
            for(int y: f) {
                g.emplace(y % x);
            }
            f = g;
        }
        for(int x: f) {
            ans = max(ans, x % nek.back());
        }

        if(cnt[nek.back()] == 1) {
            ans = max(ans, nek.back());
        }

        // for(int i = 1 ; i <= maxval ; ++ i) {
        //     if(cnt[i]) {
        //         // puts("wdnmd");
        //         -- cnt[i];
        //         vector<int> nek;
        //         for(int j = maxval ; j >= 1 ; -- j) {
        //             if(cnt[j]) {
        //                 nek.emplace_back(j);
        //             }
        //         }
        //         if(nek.empty()) {
        //             // 放呢，不可能是空的，不然就一个数，这个在 n<=10 就判过了
        //         } else {
        //             // 首先肯定是要递减的选数，其次可以发现 x % y，如果 y<=x，则x至少会 /2
        //             // 因此每一轮可行的个数就 /2了，所以均摊下来就 nlogn 了
        //             // 有个问题就是，有一些数它可能会一直保留到结束……
        //             set<int> f; f.emplace(i);
        //             for(int x: nek) {
        //                 set<int> g = f;
        //                 for(int y: f) {
        //                     g.emplace(y % x);
        //                 }
        //                 f = g;
        //                 // printf("sz = %d\n", int(f.size()));
        //             }
        //             for(int x: f) {
        //                 ans = max(ans, x % nek.back());
        //             }
        //         }
        //         ++ cnt[i];
        //     }
        // }
        printf("%d\n", ans);
    } else {
        bitset<N> f, g;
        reverse(a + 1, a + 1 + n);
        for(int i = 1 ; i <= n ; ++ i) {
            cnt[a[i]] = 1;
        }
        for(int i = maxval ; ~ i ; -- i) {
            if(cnt[i]) {
                for(int j = i ; j <= maxval ; j += i) {
                    g[j] = 1;
                }
                f[i] = 1;
            } else {
                f[i] = ((f >> i) & g).any();
            }
        }
        for(int i = a[n] - 1 ; ~ i ; -- i) {
            if(f[i]) {
                printf("%d\n", i);
                break;
            }
        }
    }
}
