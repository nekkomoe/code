#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cctype>
#include <bitset>
#include <cmath>
#include <numeric>
 
using namespace std;
 
typedef long long ll;
 
int c[7010][610], f[10010][610], a[10010];
 
int n, k, ans, mx;
 
void modify(int x, int y, int z) {
    for(int i = x ; i <= k + mx ; i += i & -i)
        for(int j = y ; j <= k + 1 ; j += j & -j)
            c[i][j] = max(c[i][j], z);
}
 
int query(int x, int y) {
    int res = 0;
    for(int i = x ; i ; i -= i & -i)
        for(int j = y ; j ; j -= j & -j)
            res = max(res, c[i][j]);
    return res;
}
 
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), mx = max(mx, a[i]);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = k ; ~ j ; -- j) {
            ans = max(ans, f[i][j] = query(a[i] + j, j + 1) + 1);
            modify(a[i] + j, j + 1, f[i][j]);
        }
    }
    printf("%d\n", ans);
}
