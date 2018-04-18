#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
typedef long long ll;
 
const int MAX_N = 60000;
 
int n, tot, l, r, q[MAX_N];
ll x[MAX_N], y[MAX_N], f[MAX_N];
struct PLACE{ll x, y;}place[MAX_N];
 
ll solve(int i, int j){
    return f[j] + y[j + 1] * x[i];
}
 
double slop(int k, int j){
    return (f[j] - f[k]) * 1.0 / (y[k + 1] - y[j + 1]);
}
 
bool cmp(PLACE a, PLACE b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
 
int main(){
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++){
        scanf("%lld%lld", &place[i].x, &place[i].y);
    }
    sort(place + 1, place + 1 + n, cmp);
    for(int i = 1 ; i <= n ; i++){
        while(tot && place[i].y >= y[tot]){
            tot--;
        }
        x[++tot] = place[i].x;
        y[tot] = place[i].y;
    }
    for(int i = 1 ; i <= tot ; i++){
        while(l < r && slop(q[l], q[l + 1]) < x[i]){
            l++;
        }
        f[i] = solve(i, q[l]);
        while(l < r && slop(q[r], i) < slop(q[r - 1], q[r])){
            r--;
        }
        q[++r] = i;
    }
    printf("%lld\n",f[tot]);
}
