#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

void sol() {
    long long a, b, c, d;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    puts(gcd(a, b) == gcd(c, d) ? "Yes" : "No");
}

int main() {
    int T; scanf("%d", &T);
    while(T --) sol();
}
