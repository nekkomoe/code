#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int N = 310000;
typedef long long ll;
int n, q;
ll a[N], globalTag, localTag[N], fa[N];
vector<ll> num[N];
int get(int x) {return x == fa[x] ? x : fa[x] = get(fa[x]);}
struct heap {
    priority_queue<ll> val, del;
    void push(ll x) {val.push(x);}
    void pop(ll x) {del.push(x);}
    ll top() {while(del.size() && val.top() == del.top()) val.pop(), del.pop(); return val.top();}
} globalMx, localMx[N];
char op[5];
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        fa[i] = i;
        num[i].push_back(i);
        localMx[i].push(a[i]);
        globalMx.push(a[i]);
    }
    scanf("%d", &q);
    for(int i = 1, x, y, v ; i <= q ; ++ i) {
        scanf("%s", op);
        if(op[0] == 'U') {
            scanf("%d%d", &x, &y), x = get(x), y = get(y);
            if(x != y) {
                if(num[x].size() < num[y].size()) swap(x, y);
                globalMx.pop(localMx[y].top() + localTag[y]);
                globalMx.pop(localMx[x].top() + localTag[x]);
                for(int j = 0 ; j < num[y].size() ; ++ j) {
                    int id = num[y][j];
                    fa[id] = x;
                    a[id] = a[id] + localTag[y] - localTag[x];
                    num[x].push_back(id);
                    localMx[x].push(a[id]);
                }
                num[y].clear();
                globalMx.push(localMx[x].top() + localTag[x]);
            }
        } else if(op[0] == 'A' && op[1] == '1') {
            scanf("%d%d", &x, &v);
            globalMx.pop(localMx[get(x)].top() + localTag[get(x)]);
            localMx[get(x)].pop(a[x]);
            localMx[get(x)].push(a[x] += v);
            globalMx.push(localMx[get(x)].top() + localTag[get(x)]);
        } else if(op[0] == 'A' && op[1] == '2') {
            scanf("%d%d", &x, &v);
            globalMx.pop(localMx[get(x)].top() + localTag[get(x)]);
            localTag[get(x)] += v;
            globalMx.push(localMx[get(x)].top() + localTag[get(x)]);
        } else if(op[0] == 'A' && op[1] == '3') {
            scanf("%d", &v);
            globalTag += v;
        } else if(op[0] == 'F' && op[1] == '1') {
            scanf("%d", &x);
            printf("%lld\n", a[x] + localTag[get(x)] + globalTag);
        } else if(op[0] == 'F' && op[1] == '2') {
            scanf("%d", &x);
            printf("%lld\n", localMx[get(x)].top() + localTag[get(x)] + globalTag);
        } else if(op[0] == 'F' && op[1] == '3') {
            printf("%lld\n", globalMx.top() + globalTag);
        }
    }
}

