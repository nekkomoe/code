#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e4 + 10;

ll ans;
int n, m, w, a[N], h[N];
int L[N], R[N], ban[N];
ll f[510][510];
vector<int> num;
int lim;
ll calc(ll x) {
    return x * (x - 1) / 2;
}
int main() {
// #ifdef ONLINE_JUDGE
//     freopen("friend.in", "r", stdin);
//     freopen("friend.out", "w", stdout);
// #endif
    scanf("%d%d%d", &n, &m, &w);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
        h[i] = w - h[i];
    }
    for (int i = 1; i <= m; ++i) {
        int pos, val;
        scanf("%d%d", &pos, &val);
        int l = pos, r = pos;
        while (l - 1 >= 1 && val > h[l]) {
            --l;
        }
        while (r + 1 <= n && val > h[r]) {
            ++r;
        }
        L[i] = l, R[i] = r;
        num.push_back(l);
        num.push_back(r);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    lim = num.size();
    for(int i = 1 ; i <= m ; ++ i) {
        // printf("%d %d\n", L[i], R[i]);
        L[i] = lower_bound(num.begin(), num.end(), L[i]) - num.begin() + 1;
        R[i] = lower_bound(num.begin(), num.end(), R[i]) - num.begin() + 1;
    }
    for(int len = 1 ; len <= lim ; ++ len) {
        for(int i = 1 ; i + len - 1 <= lim ; ++ i) {
            int j = i + len - 1;

            for(int k = 1 ; k <= lim ; ++ k) {
                a[k] = 0;
            }
            for(int k = 1 ; k <= m ; ++ k) {
                int l = L[k], r = R[k];
                if(i <= l && r <= j) {
                    a[l] ++;
                    a[r + 1] --;
                }
            }
            for(int k = 1 ; k <= lim ; ++ k) {
                a[k] += a[k - 1];
            }

            for(int k = i ; k <= j ; ++ k) {
                f[i][j] = max(f[i][j], f[i][k - 1] + calc(a[k]) + f[k + 1][j]);
            }
        }
    }
    printf("%lld\n", f[1][lim]);
}
