#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <ctime>
#include <cctype>
#include <cfloat>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cmath>
 
using namespace std;
 
#ifdef ONLINE_JUDGE
    #define debug
    #define log(message)
#else
    #define debug printf("passing [%s] in line %d\n", __FUNCTION__, __LINE__)
    #define log(message) puts(message)
#endif
 
#define INF 0x3f3f3f3f
 
#define INFLL 0x3f3f3f3f3f3f3f3fLL
 
void closeSync() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
 
template<class T> void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while(ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ '0'), ch = getchar();
    x = f ? -x : x;
}
 
typedef long long ll;
 
// to do
 
ll f[110000][20], p, w, ans;
 
int T, n, k;
 
int main() {
    read(T);
    f[0][0] = 1;
    while(T --) {
        read(n), read(k), read(p);
        if(k == 1) ans = 1;
        else {
            ans = 0;
            w = (ll)n * (k - 1);
            for(int i = 1 ; i <= w ; ++ i) {
                for(int j = 1 ; j < k ; ++ j) {
                    if(i >= j) {
                        f[i][j] = (f[i - j][j] + f[i - j][j - 1]) % p;
                    }
                    if(i >= n + 1) {
                        f[i][j] = (f[i][j] - f[i - 1 - n][j - 1]) % p;
                    }
                    f[i][j] = (f[i][j] % p + p) % p;
                }
            }
            for(int i = 1 ; i <= w ; ++ i) {
                for(int j = 1 ; j < k ; ++ j) {
                    ans = (ans + f[i][j] * f[i][k - j]) % p;
                }
            }
            for(int i = 1 ; i <= w ; ++ i) {
                for(int j = 1 ; j < k - 1 ; ++ j) {
                    ans = (ans + f[i][j] * f[i][k - j - 1]) % p;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

