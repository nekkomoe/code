// 位运算 数学

// 题意：给你一些数字，每次你可以选择两个同为奇数或者偶数的数字然后把它们加起来，然后删掉这两个数字并加入新产生的数字，问最后是否可以只剩下一个数字

// 思路：换句话说就是一堆奇数和偶数怎么搞成只有一个数字。首先偶数加偶数等于偶数，所以先不用管，因为只要全都是偶数就一定能弄成一个数字。奇数加奇数等于偶数，也就是说新产生的偶数只跟奇数的个数有关。如果有奇数个奇数的话会剩余一个奇数，那么就是输出NO了，否则输出YES。当然如果N=1的话直接输出YES就行，不过题里面说了N>=2所以可以不用考虑。

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, a, cnt;

int main() {
    scanf("%d", &n);
    while(n --)
        scanf("%d", &a), cnt ^= a & 1;
    if(cnt)
        puts("NO");
    else
        puts("YES");
}
