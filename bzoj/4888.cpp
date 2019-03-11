#include <cstdio>
#include <cstring>
 
const int N = 1e6 + 10;
 
typedef long long ll;
 
ll bit[2][N], n, s[N], a[N], ans, cnt, tmp, mx, now;
 
void add(int i, int ty) {
    for( ; i <= (int) 1e6 ; i += i & -i) ++ bit[ty][i];
}
 
ll sum(int i, int ty) {
    ll ret = 0;
    for( ; i ; i -= i & -i) ret += bit[ty][i];
    return ret;
}
 
int main() {
    scanf("%lld\n", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &s[i]), s[i] += s[i - 1], mx = mx < s[i] ? s[i] : mx;
    for(int i = 0 ; i <= 20 ; ++ i) {
        if((1 << i) > mx) break;
        memset(bit, 0, sizeof bit);
        add(1, 0);
        cnt = 0;
        for(int j = 1 ; j <= n ; ++ j) {
            tmp = s[j] & (1 << i);
            if(tmp) now = sum(a[j] + 1, 0) + sum((int) 1e6, 1) - sum(a[j] + 1, 1);
            else now = sum(a[j] + 1, 1) + sum((int) 1e6, 0) - sum(a[j] + 1, 0);
            cnt ^= now & 1;
            add(a[j] + 1, tmp ? 1 : 0);
            a[j] |= tmp;
        }
        ans |= cnt * (1 << i);
    }
    printf("%lld\n", ans);
}
