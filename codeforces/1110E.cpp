#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, a[N], b[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &b[i]);
    if(a[1] != b[1]) {
        puts("No");
        return 0;
    }
    for(int i = 1 ; i <= n ; ++ i) a[i] = a[i + 1] - a[i], b[i] = b[i + 1] - b[i]; -- n;
    sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] != b[i]) {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
}
