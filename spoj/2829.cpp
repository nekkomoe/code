#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9;

int n, m, c[1 << 16], mx;
ll f[2][1 << 16];

void sol() {
    cin >> n >> m;
    mx = 1 << m;
    for(int i = 1 ; i <= n ; ++ i) cin >> c[i];
    
    int p = 0;
    for(int j = 0 ; j < mx ; ++ j) f[p][j] = 1;
    for(int j = 0 ; j < mx ; j += c[1]) f[p][j] = 0;
    for(int k = 0 ; k < m ; ++ k)
        for(int s = 0 ; s < mx ; ++ s)
            if(s & (1 << k))
                (f[p][s] += f[p][s - (1 << k)]) %= mod;
    
    for(int i = 2 ; i <= n ; ++ i) {
        p ^= 1;
        for(int j = 0 ; j < mx ; ++ j) f[p][j] = f[p ^ 1][mx - 1 - j];
        
        for(int j = 0 ; j < mx ; j += c[i]) {
            f[p][j] = 0;
        }
        for(int k = 0 ; k < m ; ++ k)
            for(int s = 0 ; s < mx ; ++ s)
                if(s & (1 << k))
                    (f[p][s] += f[p][s - (1 << k)]) %= mod;
    }
    cout << f[p][mx - 1] << endl;
}

int main() {
    ios :: sync_with_stdio();
    int t; cin >> t;
    while(t --) sol(); 
}

