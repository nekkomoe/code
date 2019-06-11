#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n;
struct MON {
    ll hp, atk;
    ll cnt;
} mon[N];
bool operator < (MON A, MON B) {
    // return x.atk * y.hp == y.atk * x.hp ? x.atk > y.atk : x.atk * y.hp > y.atk * x.hp;

    int x = A.cnt, y = B.cnt;
    return (A.atk + B.atk) * x + B.atk * y < (A.atk + B.atk) * y + A.atk * x;
}

void runprog() {
    scanf("%d", &n);
    ll sum = 0, ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &mon[i].hp, &mon[i].atk);
        sum += mon[i].atk;
        ll l = 1, r = mon[i].hp;
        while(l <= r) {
            ll mid = (l + r) >> 1;
            if((1 + mid) * mid / 2 >= mon[i].hp) {
                mon[i].cnt = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    sort(mon + 1, mon + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        int j = 1;
        ans += sum * mon[i].cnt;
        sum -= mon[i].atk;
    }

    static int T = 0;
    printf("Case #%d: %lld\n", ++ T, ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
