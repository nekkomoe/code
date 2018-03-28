//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int M = 10000;

int f[1010][1010], n, k, sum;

/*
  f[i][j] : 用数字1~i组成了j个逆序对
  假设已经求出了f[i - 1][w]，考虑i的位置，会发现i无论放到哪里，在它后面的数字全部都比它小，那么数字i的贡献就是在它右面的数字，换而言之，这个数字可以形成1~i-1个逆序对
  f[i][j] = sum{f[i - 1][j - w]}
  前缀和优化
*/

int main() {
    cin >> n >> k;
    f[0][0] = 1;
    for(int i = 1 ; i <= n ; i ++) {
        sum = 0;
        for(int j = 0 ; j <= k ; j ++) {
            if(j - i >= 0) {
                sum = sum - f[i - 1][j - i] + M;
                sum = sum % M;
            }
            sum = sum + f[i - 1][j];
            sum = sum % M;
            f[i][j] = sum;
        }
    }
    cout << f[n][k] << endl;
}
