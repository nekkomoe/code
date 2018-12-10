#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef long double ld;

const int N = 310;

int n; ld f[N]; 

int main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        ld p; cin >> p; p /= 100;
        
        ld p1 = p;
        ld p2 = (1 - p) * p;
        ld p3 = (1 - p1 - p2);
        
//        cout << p1 << ' ' << p2 << ' ' << p3 << ':' << p1 + p2 + p3 << endl;
        
        f[i] = p1 * (f[i - 1] + 1) + p2 * (f[i - 1] + 1) + p3 * f[i - 1];
    }
    cout << fixed << setprecision(3) << f[n] << endl;
}

