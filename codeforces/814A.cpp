#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, k, a[N], b[N];
bool check() {
    for(int i = 1 ; i < n ; ++ i)
        if(a[i] > a[i + 1])
            return 0;
    return 1;
}
int main() {
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i) cin >> a[i];
    for(int i = 1 ; i <= k ; ++ i) cin >> b[i];
    if(k >= 2) return puts("Yes"), 0;
    for(int i = 1 ; i <= n ; ++ i)
        if(a[i] == 0)
            a[i] = b[1];
    puts(check() ? "No" : "Yes");
}