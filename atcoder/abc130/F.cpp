#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7, N = 1e5 + 10;
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
#define double long double
ll getinv(ll n) {
    return pw(n, mod - 2);
}
 
ll x[N], y[N], dir[N];
int n;
// const ll inf = 0x3f3f3f3f3f3f3f3fll;
const double inf = 1e60;
 
double get_ran_x(double T) {
    double mn = inf, mx = -inf;
    for(int i = 1 ; i <= n ; ++ i) {
        if(dir[i] == 'L') {
            mn = min(mn, x[i] - T);
            mx = max(mx, x[i] - T);
        } else if(dir[i] == 'R') {
            mn = min(mn, x[i] + T);
            mx = max(mx, x[i] + T);
        } else {
            mn = min(mn, (double) x[i]);
            mx = max(mx, (double) x[i]);
        }
    }
    return (mx - mn);
}
 
double get_ran_y(double T) {
    double mn = inf, mx = -inf;
    for(int i = 1 ; i <= n ; ++ i) {
        if(dir[i] == 'U') {
            mn = min(mn, y[i] + T);
            mx = max(mx, y[i] + T);
        } else if(dir[i] == 'D') {
            mn = min(mn, y[i] - T);
            mx = max(mx, y[i] - T);
        } else {
            mn = min(mn, (double) y[i]);
            mx = max(mx, (double) y[i]);
        }
    }
    return (mx - mn);
}
double get(double T) {
    return get_ran_x(T) * get_ran_y(T);
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        char s[10];
        scanf("%lld%lld%s", &x[i], &y[i], s);
        dir[i] = s[0];
    }
 
    // n = 1e5;
    // for(int i = 1 ; i <= n ; ++ i) {
    //     // char s[10];
    //     // scanf("%lld%lld%s", &x[i], &y[i], s);
    //     // dir[i] = s[0];
    //     x[i] = rand() % int(2e8) - int(1e8);
    //     y[i] = rand() % int(2e8) - int(1e8);
    //     dir[i] = "LRUD"[rand() % 4];
    // }
 
    // for(int T = 0 ; T <= 100 ; ++ T) {
    //     double ranx = get_ran_x(T);
    //     double rany = get_ran_y(T);
    //     printf("%lf %lf: %lf\n", ranx, rany, ranx * rany);
    // }
    double l = 0, r = 1e10;
    for(int i = 1 ; i <= 1000 ; ++ i) {
        double len = (r - l) / 3;
        double ml = l + len, mr = l + len * 2;
        if(get(ml) < get(mr)) {
            r = mr;
        } else {
            l = ml;
        }
    }
    // cout << l << ' ' << r << endl;
    double ans = get(l);
    cout << fixed << setprecision(10) << ans << endl;
}
