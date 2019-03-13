#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 200000 + 10;

int ch[N * 35][2], n, tot;

void ins(int x) {
    int u = 1;
    for(int i = 30 ; ~ i ; -- i) {
        int bit = (x >> i) & 1;
        if(!ch[u][bit]) ch[u][bit] = ++ tot;
        u = ch[u][bit];
    }
}

int ask(int x) {
    int res = 0, u = 1;
    for(int i = 30 ; ~ i ; -- i) {
        int bit = (x >> i) & 1;
        if(ch[u][bit]) u = ch[u][bit];
        else u = ch[u][!bit], res |= 1 << i;
    }
    return res;
}

ll sol(vector<int> a, int bit) {
    if(a.empty() || bit < 0) return 0;
    vector<int> b[2];
    for(int x: a) b[(x >> bit) & 1].push_back(x);
    int res = 0x3f3f3f3f;
    for(int i = 0 ; i <= tot ; ++ i) ch[i][0] = ch[i][1] = 0; tot = 1;
    for(int x: b[0]) ins(x);
    for(int x: b[1]) res = min(res, ask(x));
    return sol(b[0], bit - 1) + sol(b[1], bit - 1) + (res == 0x3f3f3f3f ? 0 : res);
}

int main() {
    scanf("%d", &n);
    vector<int> x; for(int y ; n -- ; x.push_back(y)) scanf("%d", &y);
    printf("%lld\n", sol(x, 30));
}
