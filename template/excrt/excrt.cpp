#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
const int N = 1e5 + 10;
ll x, y, d; int n;

void exgcd(ll &x, ll &y, ll a, ll b) {
    if(!b) d = a, x = 1, y = 0;
    else exgcd(y, x, b, a % b), y -= a / b * x;
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll a, b, A, B;

void merge() {
    exgcd(x, y, a, A);
    ll c = B - b;
    if(c % d) puts("-1"), exit(0);
    x = x * c / d % (A / d);
    if(x < 0) x += A / d;
    ll mod = lcm(a, A);
    b = (a * x + b) % mod; if(b < 0) b += mod;
    a = mod;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        long long _A, _B;
        scanf("%lld%lld", &_A, &_B), A = _A, B = _B;
        if(i > 1) merge();
        else a = A, b = B;
    }
    printf("%lld\n", (long long)(b % a));
}