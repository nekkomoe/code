#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
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
 
inline int read() {
    static int f,ret;
    static char c;
    ret = 0, f = 1;
    c = getchar();
    while(c > '9' || c < '0'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') ret = (ret << 1) + (ret << 3) + c - '0', c = getchar();
    return f == 1 ? ret : -ret;
}
 
typedef long long ll;
 
// to do
 
const int N = 500010;
 
int n, ans, pos, maxRight, rl[N], q[N], cur = 1;
 
char str[N];
 
set<int> s;
 
bool cmp(int a, int b) {
    return (a - rl[a]) < (b - rl[b]);
}
 
int main() {
    scanf("%d", &n);
    scanf("%s", str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        if(maxRight >= i) rl[i] = min(maxRight - i, rl[2 * pos - i]);
        else rl[i] = 0;
        while(str[i - rl[i]] == str[i + rl[i] + 1]) ++ rl[i];
        if(rl[i] + i > maxRight) maxRight = rl[i] + i, pos = i;
        q[i] = i;
    }
    sort(q + 1, q + 1 + n, cmp);
    for(int i = 1 ; i <= n ; ++ i) {
        while(cur <= n && q[cur] - rl[q[cur]] <= i) s.insert(q[cur ++]);
        set<int> :: iterator it = s.upper_bound(i + rl[i] / 2);
        if(it != s.begin()) ans = max(ans, (* -- it - i) * 4);
    }
    printf("%d\n", ans);
    return 0;
}
