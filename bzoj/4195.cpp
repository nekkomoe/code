#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
const int N = 3100000;
 
int t, n;
 
struct Q {
    int x, y;
};
 
vector<Q> equ, unequ;
 
vector<int> num;
 
int fa[N];
 
int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}
 
int main() {
    scanf("%d", &t);
    while(t --) {
        scanf("%d", &n);
        equ.clear();
        unequ.clear();
        num.clear();
        for(int i = 1, x, y, z ; i <= n ; ++ i) {
            scanf("%d%d%d", &x, &y, &z);
            if(z == 1) {
                equ.push_back((Q) {x, y});
            } else {
                unequ.push_back((Q) {x, y});
            }
            num.push_back(x);
            num.push_back(y);
            fa[i] = i;
            fa[i + n] = i + n;
        }
        sort(num.begin(), num.end());
        num.erase(unique(num.begin(), num.end()), num.end());
        for(int i = 0 ; i < equ.size() ; ++ i) {
            equ[i].x = lower_bound(num.begin(), num.end(), equ[i].x) - num.begin() + 1;
            equ[i].y = lower_bound(num.begin(), num.end(), equ[i].y) - num.begin() + 1;
        }
        for(int i = 0 ; i < unequ.size() ; ++ i) {
            unequ[i].x = lower_bound(num.begin(), num.end(), unequ[i].x) - num.begin() + 1;
            unequ[i].y = lower_bound(num.begin(), num.end(), unequ[i].y) - num.begin() + 1;
        }
        for(int i = 0 ; i < equ.size() ; ++ i) {
            if(get(equ[i].x) != get(equ[i].y)) {
                fa[get(equ[i].x)] = get(equ[i].y);
            }
        }
        for(int i = 0 ; i < unequ.size() ; ++ i) {
            if(get(unequ[i].x) == get(unequ[i].y)) {
                puts("NO");
                goto nxt;
            }
        }
        puts("YES");
        nxt:;
    }
}

