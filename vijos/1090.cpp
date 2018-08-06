// 前缀和 数论 模运算

/*
  sum[l,r] % k == 0 <=> (sum(r) - sum(l - 1)) % k == 0 <=> sum(r) % k == sum(l - 1) % k
  与处理完所有前缀和模k的余数,假设这个数组叫做cnt.
  cnt[i]的含义就是所有的前缀和模k的点的个数(位置),根据乘法原理,最左边的那个点可以找到cnt[i]-1个点使得上面那个等式成立，诸如此类,余数i的贡献为cnt[i]*(cnt[i]-1)/2.
  最终答案需要再统计上cnt[0].
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 500010;

const int M = 2000010;

int n;

long long m, cnt[M], sum[N], ans;

int main() {
    scanf("%d%lld", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &sum[i]);
        sum[i] += sum[i - 1];
        sum[i] %= m;
        ++ cnt[sum[i]];
    }
    for(int i = 0 ; i < m ; ++ i) {
        ans += cnt[i] * (cnt[i] - 1) / 2;
    }
    (ans += cnt[0]) %= 1234567;
    printf("%lld\n", ans);
}
