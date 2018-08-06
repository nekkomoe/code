// 贪心 线性基

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1010;

int n;

ll bs[100], ans;

struct T {
    ll id, val;
} a[N];

bool cmp(T a, T b) {
    return a.val > b.val;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &a[i].id, &a[i].val);
    }
    sort(a + 1, a + 1 + n, cmp);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 60 ; ~ j ; -- j) {
            if((a[i].id >> j) & 1) {
                if(!bs[j]) {
                    bs[j] = a[i].id;
                    ans += a[i].val;
                    break;
                }
                a[i].id ^= bs[j];
            }
        }
    }
    printf("%lld\n", ans);
}