#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 10;

int n, z;

struct data {
    int d, a, id;
} dt[N];

typedef long long ll;

ll ans;

vector<data> e1, e2;

bool cmp1(data x, data y) {
    return x.d < y.d;
}

bool cmp2(data x, data y) {
    return x.a > y.a;
}

int main() {
    scanf("%d%lld", &n, &ans);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &dt[i].d, &dt[i].a);
        dt[i].id = i;
        if(dt[i].d <= dt[i].a) {
            e1.push_back(dt[i]);
        } else {
            e2.push_back(dt[i]);
        }
    }
    sort(e1.begin(), e1.end(), cmp1);
    for(int i = 0 ; i < e1.size() ; ++ i) {
        ans -= e1[i].d;
        if(ans <= 0) return puts("NIE"), 0;
        ans += e1[i].a;
    }
    sort(e2.begin(), e2.end(), cmp2);
    for(int i = 0 ; i < e2.size() ; ++ i) {
        ans -= e2[i].d;
        if(ans <= 0) return puts("NIE"), 0;
        ans += e2[i].a;
    }
    puts("TAK");
    for(int i = 0 ; i < e1.size() ; ++ i) printf("%d ", e1[i].id);
    for(int i = 0 ; i < e2.size() ; ++ i) printf("%d ", e2[i].id);
}
