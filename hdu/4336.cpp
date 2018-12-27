#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 30;

int n; double p[N];

void sol() {
    for(int i = 1 ; i <= n ; ++ i) scanf("%lf", &p[i]);
    double res = 0;
    for(int s = 1 ; s < (1 << n) ; ++ s) {
        int cnt = 0; double sum = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            if(s & (1 << (i - 1))) {
                ++ cnt;
                sum += p[i];
            }
        }
        res += (cnt & 1 ? 1.0 : -1.0) / sum;
    }
    printf("%.4f\n", res);
}

int main() {
    while(scanf("%d", &n) == 1) {
        sol();
    }
}
