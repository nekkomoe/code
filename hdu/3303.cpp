#include <bits/stdc++.h>
using namespace std;
const int P = 3000, inf = 0x3f3f3f3f;

int q, mx; set<pair<int, int> > st;

pair<int, int> mn[P + 10]; 

void sol() {
    static int tot = 0;
    int cnt = 0;
    if(tot) cout << endl;
    cout << "Case " << ++ tot << ":" << endl;
    st.clear(); for(int i = 1 ; i <= P ; ++ i) mn[i] = make_pair(inf, inf); mx = -1;
    for(int i = 1, x ; i <= q ; ++ i) {
        char op[10]; cin >> op >> x;
        if(op[0] == 'B') {
            ++ cnt;
            mx = max(mx, x);
            st.insert(make_pair(x, -cnt));
            for(int j = 1 ; j <= P ; ++ j) mn[j] = min(mn[j], make_pair(x % j, -cnt));
        } else {
            if(st.empty()) {
                cout << -1 << endl;
            } else if(x <= P) {
                cout << -mn[x].second << endl;
            } else {
                pair<int, int> ans = make_pair(inf, -1);
                for(int y = 0 ; y <= mx ; y += x) {
                    pair<int, int> a = make_pair(y, -inf);
                    set<pair<int, int> > :: iterator it = st.lower_bound(a);
                    if(it == st.end()) continue;
                    pair<int, int> res = *it;
                    res.first %= x;
                    ans = min(ans, res);
                }
                cout << -ans.second << endl;
            }
        }
    } 
}

int main() {
//    freopen("data.in", "r", stdin);
    ios :: sync_with_stdio(0);
    while(cin >> q && q) sol(); 
}
