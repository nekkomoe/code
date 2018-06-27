#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int pre[N], sub[N], n, a[N], ans, pos[N], cnt, last[N];

ll s[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
        if(a[i] == 1) pos[++ cnt] = i;
    }
    pos[cnt + 1] = n + 1;
    for(int i = 1 ; i <= n ; ++ i) pre[i] = last[a[i]], last[a[i]] = i;
    for(int i = 1 ; i <= n ; ++ i) last[i] = n + 1;
    for(int i = n ; i >= 1 ; -- i) sub[i] = last[a[i]], last[a[i]] = i;
    for(int i = 1 ; i <= cnt ; ++ i) {
        int j = pos[i];
        int mx = 0, R = n + 1;
        for(int k = j ; k >= pos[i - 1] + 1 ; -- k) {
            mx = max(mx, a[k]);
            R = min(R, sub[k] - 1);
            if(k + mx - 1 <= R
            && s[k + mx - 1] - s[k - 1] == (ll) mx * (1 + mx) / 2)
                ans = max(ans, mx);
        }
    }
    for(int i = cnt ; i ; -- i) {
        int j = pos[i];
        int mx = 0, L = 0;
        for(int k = j ; k <= pos[i + 1] + 1 ; ++ k) {
            mx = max(mx, a[k]);
            L = max(L, pre[k] + 1);
            if(k + mx - 1 >= L
            && s[k] - s[k - mx] == (ll) mx * (1 + mx) / 2)
                ans = max(ans, mx);
        }
    }
    printf("%d\n", ans);
}
