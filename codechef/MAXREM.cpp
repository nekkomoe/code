#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    int n; scanf("%d", &n); vector<int> a(n);
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());
    for(int i = a.size() - 1 ; i >= 0 ; -- i) {
        if(a[i] != a.back()) {
            printf("%d\n", a[i]);
            return 0;
        }
    }
    puts("0");
}
