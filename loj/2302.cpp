#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
const int N = 1e6 + 10;
int n;
ui inc[N], DEC[N];

set<int> st;

void run(ui *inc, ui a, ui b) {
    ui p = b / 32, q = b % 32;
    ui rig = a << q, lef = a >> (31 - q); lef >>= 1;
    ui lst = inc[p]; inc[p] += rig; lef += lst > inc[p];
    if(:: inc[p] != :: DEC[p]) {
        st.insert(p);
    } else if(st.count(p)) {
        st.erase(p);
    }
    ++ p;
    while(lef) {
        lst = inc[p]; inc[p] += lef; lef = lst > inc[p];
        if(:: inc[p] != :: DEC[p]) {
            st.insert(p);
        } else if(st.count(p)) {
            st.erase(p);
        }
        ++ p;
    }
}

int sol(int pos) {
    int p = pos / 32, q = pos % 32;
    int vi = inc[p] % (1 << q);
    int vd = DEC[p] % (1 << q);
    int bit = ((inc[p] >> q) & 1) ^ ((DEC[p] >> q) & 1);
    if(vi < vd) {
        return !bit;
    } else if(vi > vd || st.empty() || p <= *st.begin()) {
        return bit;
    } else {
        int x = * -- st.lower_bound(p);
        return bit ^ (inc[x] <= DEC[x]);
    }
}

signed main() {
    scanf("%d%*d%*d%*d", &n);
    while(n --) {
        int op, a, b, p;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &a, &b);
            if(a > 0) {
                run(inc, a, b);
            } else {
                run(DEC, -a, b);
            }
        } else {
            scanf("%d", &p);
            printf("%d\n", sol(p));
        }
    }
}
