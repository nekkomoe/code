#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, a;
    cin >> n >> a;

    set<pair<ll, ll> > st;
    st.emplace(a - 1, 0);
    ll lst = a;
    for(int i = 1 ; i < n ; ++ i) {
        cin >> a;
        if(a >= lst) {
            continue;
        }
        lst = a;
        vector<pair<ll, ll> > tmp;
        while(st.size()) {
            auto t = * -- st.end();
            if(t.first < a) {
                break;
            }
            tmp.push_back(t);
            st.erase(-- st.end());
        }
        if(tmp.size()) {
            ll mx = 0;
            for(auto t: tmp) {
                mx = max(mx, t.second + (ll) i * (t.first - t.first % a - a));
                st.emplace(t.first % a, t.second + (ll) i * (t.first - t.first % a));
            }
            st.emplace(a - 1, mx);
        }
    }

    ll ans = 0;
    for(auto e: st) {
        ans = max(ans, (ll) n * e.first + e.second);
    }
    cout << ans << endl;
}
