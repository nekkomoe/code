#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n, a[N], ans;

int main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) cin >> a[i], ans += a[i];
    sort(a + 1, a + 1 + n);
    ans = ans - a[n] + a[n] / 2;
    cout << ans << endl;
}

