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
 
// to do
 
ll T, p;
 
ll pw(ll a, ll n, ll p) {
    ll ret = 1;
    while(n) {
        if(n & 1) ret = ret * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ret;
}
 
ll phi(ll x) {
    ll ret = x;
    for(ll i = 2 ; i * i <= x ; ++ i) {
        if(x % i == 0) {
            ret = ret / i * (i - 1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) ret = ret / x * (x - 1);
    return ret;
}
 
ll f(ll p) {
    if(p == 1) return 0;
    ll ph = phi(p);
    return pw(2, f(ph) + ph, p);
}
 
int main() {
    read(T);
    while(T --) {
        read(p);
        printf("%lld\n", f(p));
    }
    return 0;
}
