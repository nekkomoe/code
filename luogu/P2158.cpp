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
#include <bitset>
 
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
 
const int N = 41000;
 
int n, ans, phi[N], prime[N], cnt, vis[N];
 
int main() {
    read(n);
    if(n == 1) return puts("0"), 0;
    phi[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            vis[i] = 1;
            prime[++ cnt] = i;
            phi[i] = i - 1;
        }
        for(int j = 1 ; j <= cnt ; ++ j) {
            if(prime[j] * i > n) break;
            vis[prime[j] * i] = 1;
            if(i % prime[j] == 0) {
                phi[prime[j] * i] = phi[i] * prime[j];
                break;
            } else {
                phi[prime[j] * i] = phi[i] * (prime[j] - 1);
            }
        }
    }
    for(int i = 1 ; i < n ; ++ i) ans += phi[i];
    printf("%d\n", ans * 2 + 1);
    return 0;
}
