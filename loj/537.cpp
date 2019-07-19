#include <cstdio>
#include <cstring>
#include <algorithm>
using std :: sort;
using std :: max;
const int N = 6000000;
typedef long long ll;
char s[N];
int n, k;
ll hs[N], cnt, ans, tot;

int main() {
    scanf("%s%d", s + 1, &k);
    n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        if(s[i] == 'A') s[i] = 1;
        if(s[i] == 'C') s[i] = 2;
        if(s[i] == 'T') s[i] = 3;
        if(s[i] == 'G') s[i] = 4;
    }
    for(int i = 1 ; i + k - 1 <= n ; ++ i) {
        int l = i, r = i + k - 1;
        ll tmp = 0;
        for(int j = l ; j <= r ; ++ j) {
            tmp = tmp * 10 + s[j];
        }
        hs[++ cnt] = tmp;
    }
    sort(hs + 1, hs + 1 + cnt);
    hs[0] = hs[cnt + 1] = -1;
    for(int i = 1 ; i <= cnt + 1 ; ++ i) {
        if(hs[i] != hs[i - 1]) {
            ans = max(ans, tot);
            tot = 1;
        } else {
            ++ tot;
        }
    }
    printf("%lld\n", ans);
}
