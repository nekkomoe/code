#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, k, a[N], ans;

int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i) cin >> a[i];
    sort(a + 1, a + 1 + n);
    ans = a[k] - a[1];
    for(int i = 1 ; i + k - 1 <= n ; ++ i)
        ans = min(ans, a[i + k - 1] - a[i]);
    cout << ans << endl;
}

