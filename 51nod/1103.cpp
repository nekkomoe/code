#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 50000 + 10;

int n; ll sum[N], a[N];

int vis[N];

int main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i], sum[i] = (sum[i - 1] + a[i]) % n;
    }
    memset(vis, -1, sizeof vis);
    vis[0] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ll x = (sum[i] + n) % n;
        if(vis[x] != -1) {
            cout << i - vis[x] << endl;
            for(int j = vis[x] + 1 ; j <= i ; ++ j)
                cout << a[j] << endl;
            return 0;
        }
        vis[x] = i;
    }
}

