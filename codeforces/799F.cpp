#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, m;
pair<ll, ll> all_sum;
pair<ll, ll> vals[N], s[N];
pair<ll, ll> lef[N], rig[N];
ll ans;
int vis[N];
ll f[N];

int main() {
    srand(76122);
    scanf("%d%d", &n, &m);
    for(int i = 1, l, r ; i <= n ; ++ i) {
        scanf("%d%d", &l, &r);
        vals[i] = make_pair((ll) rand() * rand(), (ll) rand() * rand());
        
        all_sum.first ^= vals[i].first;
        all_sum.second ^= vals[i].second;
        
        lef[r].first ^= vals[i].first;
        lef[r].second ^= vals[i].second;

        rig[l].first ^= vals[i].first;
        rig[l].second ^= vals[i].second;

        s[l].first ^= vals[i].first;
        s[l].second ^= vals[i].second;
        
        s[r + 1].first ^= vals[i].first;
        s[r + 1].second ^= vals[i].second;

        // printf("seg[%d] = %lld\n", i, vals[i]);

        vis[l] ++, vis[r + 1] --;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        f[i] = f[i - 1] + (ll) i * (i + 1) / 2;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        vis[i] += vis[i - 1];
    }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int j = 1 ; j < i ; ++ j) {
    //         assert(vals[i] != vals[j]);
    //     }
    // }

    for(int i = 1 ; i <= m ; ++ i) {
        lef[i].first ^= lef[i - 1].first;
        lef[i].second ^= lef[i - 1].second;
    }
    for(int i = m ; i >= 1 ; -- i) {
        rig[i].first ^= rig[i + 1].first;
        rig[i].second ^= rig[i + 1].second;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        s[i].first ^= s[i - 1].first;
        s[i].second ^= s[i - 1].second;
    }

    for(int i = 1 ; i <= m ; ) {
        if(vis[i]) {
            ++ i;
        } else {
            int j = i;
            while(j + 1 <= m && !vis[j + 1]) {
                ++ j;
            }
            // printf("%d %d\n", i, j);
            ans -= f[j - i + 1];
            i = j + 1;
        }
    }

    for(int i = 1 ; i <= m ; ++ i) {
        s[i].first ^= s[i - 1].first;
        s[i].second ^= s[i - 1].second;
    }
    map<pair<ll, ll>, ll> cnt, thes;
    for(int i = 1 ; i <= m ; ++ i) {
        pair<ll, ll> ins = make_pair(lef[i - 1].first ^ s[i - 1].first, lef[i - 1].second ^ s[i - 1].second);
        cnt[ins] ++;
        thes[ins] += 1 - i;

        pair<ll, ll> qr = make_pair(all_sum.first ^ rig[i + 1].first ^ s[i].first, all_sum.second ^ rig[i + 1].second ^ s[i].second);
        ans += i * cnt[qr] + thes[qr];
    }

    // for(int l = 1 ; l <= m ; ++ l) {
    //     for(int r = l ; r <= m ; ++ r) {
    //         // if((all_sum ^ rig[r + 1] ^ s[r]) == (lef[l - 1] ^ s[l - 1])) {
    //         if((all_sum.first ^ lef[l - 1].first ^ rig[r + 1].first) == (s[r].first ^ s[l - 1].first)
    //         &&
    //            (all_sum.second ^ lef[l - 1].second ^ rig[r + 1].second) == (s[r].second ^ s[l - 1].second)
    //             ) {
    //             ans += r - l + 1;
    //             printf("check [%d, %d]\n", l, r);
    //         }
    //     }
    // }

    printf("%lld\n", ans);
}
