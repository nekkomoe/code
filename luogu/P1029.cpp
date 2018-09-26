// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int x, y;
int split(int x) {
    int tot = 0;
    for(int i = 2 ; i * i <= x ; ++ i)
        if(x % i == 0) {
            ++ tot;
            while(x % i == 0) x /= i;
        }
    return tot + (x > 1);
}

int main() {
    scanf("%d%d", &x, &y);
    if(y % x) return puts("0"), 0;
    printf("%lld\n", 1ll << split(y / x)); 
}
