#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 60;
int n, x[N], y[N];
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &x[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &y[i]);

    int sum = 0;

    for(int i = 1 ; i <= n ; ++ i) {
        sum += x[i] - y[i];
    }
    if(sum >= 0) puts("Yes");
    else puts("No");
}
