#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10;
int n;
struct CIR {
    ll x, y;
} cir[N];
 
ll pw(ll x) { return x * x; }
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld%lld", &cir[i].x, &cir[i].y);
    for(int i = 1 ; i <= n ; ++ i) {
        bool f = 1; ll dis = -1;
        for(int j = 1 ; j <= n ; ++ j) {
            if(i == j) continue;
            ll t = pw(abs(cir[i].x - cir[j].x)) + pw(abs(cir[i].y - cir[j].y));
            if(dis == -1) dis = t;
            else if(dis != t) {
                f = 0;
                break;
            }
        }
        if(f) printf("%d\n", i), exit(0);
    }
    puts("-1");
}
