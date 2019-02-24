#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e4 + 10;
int n, a[N], b[N], mn = -1;

int main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i] >> b[i];
        ans += max(0, min(a[i], b[i]) - max(max(a[i - 1], b[i - 1]), mn) + 1);
        mn = min(a[i], b[i]) + 1;
    } 
    cout << ans << endl; 
}
