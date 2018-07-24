#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
int main() {
    int T; scanf("%d", &T);
    while(T --) {
        ll a, b, c, d; scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        ll g = gcd(b, d);
        if(b > a || b > d) puts("No");
        else if(c + 1 >= b) puts("Yes");
        else puts((a - c - 1) / g > (a - b) / g ? "No" : "Yes");
    }
}
