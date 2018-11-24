#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int id[N], a[N], b[N], ans; 

bool cmp(int i, int j) {
    return a[i] + b[i] < a[j] + b[j];
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &a[i], &b[i]), id[i] = i;
    sort(id + 1, id + 1 + n, cmp);
    for(int i = 1 ; i <= n / 2 ; ++ i) ans += min(a[id[i]], b[id[i]]);
    for(int i = n / 2 + 1 ; i <= n ; ++ i) ans -= max(a[id[i]], b[id[i]]);
    printf("%d\n", ans);
}

