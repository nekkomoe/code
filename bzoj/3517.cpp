#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010; 

int n, s[N], t[N]; char str[N][N];

int main() {
    ios :: sync_with_stdio();
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> str[i] + 1;
        for(int j = 1 ; j <= n ; ++ j) {
            int x = str[i][j] - '0';
            s[i] ^= x;
            t[j] ^= x;
        }
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            ans += s[i] ^ t[j] ^ (str[i][j] - '0');
        }
    }
    cout << min(ans, n * n - ans) << endl;
}

