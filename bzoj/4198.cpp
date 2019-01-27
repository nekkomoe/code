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
 
int n, k, nn;
 
ll ans;
 
struct nd {
    ll w;
    int len;
    bool operator < (nd a) const {
        return w == a.w ? len > a.len : w > a.w;
    }
};
 
priority_queue<nd> q;
 
int main() {
    read(n);
    read(k);
    nn = n;
    for(int i = 1 ; i <= n ; ++ i) {
        ll w;
        read(w);
        q.push((nd) {w, 1});
    }
    if((n - 1) % (k - 1)) nn += (k - 1) - ((n - 1) % (k - 1));
    for(int i = n + 1 ; i <= nn ; ++ i) {
        q.push((nd) {0, 1});
    }
    while(nn > 1) {
        ll s1 = 0;
        int s2 = 0;
        for(int i = 1 ; i <= k ; ++ i) {
            nd x = q.top();
            q.pop();
            s1 += x.w;
            s2 = max(s2, x.len);
        }
        nn -= k - 1;
        ans += s1;
        q.push((nd) {s1, s2 + 1});
    }
    printf("%lld\n%d\n", ans, q.top().len - 1);
    return 0;
}
