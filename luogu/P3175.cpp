#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int NNN = 1e7 + 10;

int N, n; double s[NNN];

int main() {
    scanf("%d", &n); N = 1 << n;
    for(int i = 0 ; i < N ; ++ i) scanf("%lf", &s[i]);
    for(int j = 0 ; j < n ; ++ j)
        for(int i = 0 ; i < N ; ++ i)
            if(i & (1 << j))
                s[i] += s[i - (1 << j)];
    double ans = 0;
    for(int i = 1 ; i < N ; ++ i) {
        int cnt = 0;
        for(int j = 0 ; j < n ; ++ j)
            cnt += (i >> j) & 1;
        double t = 1 - (s[N - 1 - i]);
        if(t < 1e-6) return puts("INF"), 0;
        ans += (cnt & 1 ? 1 : -1) / t;
    }
    printf("%.6f\n", ans);
}

