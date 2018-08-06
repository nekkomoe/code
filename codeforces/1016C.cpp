#include "bits/stdc++.h"
using namespace std;
const int N = 3e5 + 10;
typedef long long ll;
int n;
ll a[N], b[N];
ll a_sub[N], a_sub_sub[N];
ll a_pre[N], a_pre_pre[N];
ll b_sub[N], b_sub_sub[N];
ll b_pre[N], b_pre_pre[N];
int vis[N][3];
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &b[i]);
    for(int i = n ; i >= 1 ; -- i) {
        a_sub[i] = a_sub[i + 1] + a[i];
        a_sub_sub[i] = a_sub_sub[i + 1] + a_sub[i];

        b_sub[i] = b_sub[i + 1] + b[i];
        b_sub_sub[i] = b_sub_sub[i + 1] + b_sub[i];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        a_pre[i] = a_pre[i - 1] + a[i];
        a_pre_pre[i] = a_pre_pre[i - 1] + a_pre[i];

        b_pre[i] = b_pre[i - 1] + b[i];
        b_pre_pre[i] = b_pre_pre[i - 1] + b_pre[i];
    }


    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ans += (i - 1) * a[i];
        ans += (n + n - i) * b[i];
    }

    ll sum = 0; int stp = 1;
    vis[1][1] = 1;
    for(int x = 1, y = 2 ; ; ) {
        if(x == n + 1) break;

        // cout << x << ' ' << y << ' ' << sum << endl;

        vis[x][y] = 1;

        if(y == 1) {
            sum += stp * a[x];
            ll lnx = stp * a_sub[x + 1] + a_sub_sub[x + 1];
            int w = stp + n - x;
            ll lny = (w * b_pre[n] + b_pre_pre[n]) - ((w + n - x) * b_pre[x] + b_pre_pre[x]);
            // if(lny < 0) lny = 0;
            ans = max(ans, sum + lnx + lny);
            // cout << "1: " << x << ' ' << y << ' ' << sum + lnx + lny << ' ' << sum << ' '  << lnx << ' ' << lny << " w = " << w << endl;
        } else if(y == 2) {
            sum += stp * b[x];
            ll lny = stp * b_sub[x + 1] + b_sub_sub[x + 1];
            int w = stp + n - x;
            ll lnx = (w * a_pre[n] + a_pre_pre[n]) - ((w + n - x) * a_pre[x] + a_pre_pre[x]);
            // if(lnx < 0) lnx = 0;
            ans = max(ans, sum + lnx + lny);
            // cout << "2: " << x << ' ' << y << ' ' << sum + lnx + lny << ' ' << sum << ' '  << lnx << ' ' << lny << " w = " << w << endl;
        }


        if(vis[x][3 - y] == 0) {
            y = 3 - y;
        } else {
            ++ x;
        }
        ++ stp;

        // cout << sum << endl;
    }

    printf("%lld\n", ans);
}

// 4
// 1 6 2 3
// 9 8 3 2
