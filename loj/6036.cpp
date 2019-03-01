#include <bitset>
#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 5e5 + 10;
int n;

namespace NEKO_N2 {
    #define N int(4e6 + 10)
    char str[int(5e5) + 10];
    int tot = 1, ch[N][2], vcnt, top;
    #define sta(i) ch[i][0]
    bitset<N> aped;
//    vector<int> g[N];
typedef unsigned long long ull;
    map<ull, int> hs;
    int head[N], rest[N], to[N];
    void lk(int u, int v) {
        static int tot = 0;
//        g[u].push_back(v);
        to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
    }

    int dfn[N], low[N], clk, cnt;
    vector<int> vec[N];
    vector<pair<int, int> > val[N];
    #define ins aped
    #define endpos aped
    void dfs(int u) {
        dfn[u] = low[u] = ++ clk;
        sta(++ top) = u;
        ins[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if(ins[v]){
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]) {
            cnt ++;
            int v;
            do {
                v = sta(top --);
                ins[v] = 0;
                vec[cnt].push_back(v);
            } while(u != v);
        }
    }

    void insert() {
        int has_wen = 0;
        for(int i = 1 ; str[i] ; ++ i) {
            if(str[i] == '?') {
                has_wen = 1;
                break;
            }
        }
        int u = 1;
        for(int i = 1 ; str[i] ; ++ i) {
            int c = str[i] == '?' ? 0 : str[i] - '0';
            if(!ch[u][c]) ch[u][c] = ++ tot;
            u = ch[u][c];
        } endpos[u] = 1;
        int v0 = ++ vcnt, v1 = ++ vcnt;
        val[u].push_back(make_pair(v0, v1));

        int op[2] = { v0, v1 };

        u = 1;
        for(int i = 1 ; str[i] ; ++ i) {
            int c = str[i] == '?' ? 1 : str[i] - '0';
            if(!ch[u][c]) ch[u][c] = ++ tot;
            u = ch[u][c];
        } endpos[u] = 1;
        v0 = ++ vcnt, v1 = ++ vcnt;
        val[u].push_back(make_pair(v0, v1));

        lk(op[1], v0);
        lk(v1, op[0]);
        lk(op[0], v1);
        lk(v0, op[1]);
    }

    pair<int, int> gosubtree(int u) {
        int r0 = ++ vcnt, r1 = ++ vcnt;
        for(int i = 0 ; i < 2 ; ++ i) {
            if(ch[u][i]) {
                pair<int, int> st = gosubtree(ch[u][i]);
                lk(r0, st.first);
                lk(r1, st.second);
            }
        }
        if(!endpos[u]) return make_pair(r0, r1);

        int ano0 = ++ vcnt, ano1 = ++ vcnt;
        lk(ano0, r0), lk(ano1, r1);

        for(pair<int, int> tmp: val[u]) {
            lk(tmp.second, r0);
            lk(ano0, r0), lk(ano1, r1);
            lk(ano0, tmp.first), lk(ano1, tmp.second);
        }

        return make_pair(ano0, ano1);
    }

    void gotoptree(int u, pair<int, int> tp) {

        if(endpos[u]) {
            int ano0 = ++ vcnt, ano1 = ++ vcnt;
            lk(ano0, tp.first), lk(ano1, tp.second);
            for(pair<int, int> tmp: val[u]) {
                lk(tmp.second, tp.first);
                lk(ano0, tmp.first), lk(ano1, tmp.second);
            }
            tp = make_pair(ano0, ano1);
        }
        for(int i = 0 ; i < 2 ; ++ i) {
            if(ch[u][i]) {
                gotoptree(ch[u][i], tp);
            }
        }
    }

    void runprog() {
        const ull base = 233;
        for(int i = 1 ; i <= n ; ++ i) {
            ull val = 0;
            scanf("%s", str + 1);
            for(int j = 1 ; str[j] ; ++ j) {
                val = val * base + str[j];
            }
            ++ hs[val];
            if(hs[val] >= 3) {
                puts("NO");
                return ;
            }
            insert();
        }
        gosubtree(1);
        gotoptree(1, make_pair(++ vcnt, ++ vcnt));

        for(int i = 1 ; i <= tot ; ++ i) {
            if(endpos[i]) {
                for(int T = 1 ; T <= 2 ; ++ T) {
                    int pre0 = ++ vcnt, pre1 = ++ vcnt;
                    for(int j = 0 ; j < val[i].size() ; ++ j) {
                        int v0 = val[i][j].first, v1 = val[i][j].second;
                        lk(v1, pre0);
                        int newpre0 = ++ vcnt, newpre1 = ++ vcnt;
                        lk(newpre0, pre0), lk(newpre1, pre1);
                        lk(newpre0, v0), lk(newpre1, v1);
                        pre0 = newpre0, pre1 = newpre1;
                    }
                    reverse(val[i].begin(), val[i].end());
                }
            }
        }
        aped = 0;
        for(int i = 1 ; i <= vcnt ; ++ i) if(!dfn[i]) dfs(i);
        aped = 0;
        for(int i = 1 ; i <= cnt ; ++ i) {
            for(int u: vec[i]) aped[u] = 1;
            for(int u: vec[i]) {
                int v = u & 1 ? u + 1 : u - 1;
                if(aped[v]) { puts("NO"); return ; }
            }
            for(int u: vec[i]) aped[u] = 0;
        }
        puts("YES");
    }

}

int main() {
    scanf("%d", &n);
    NEKO_N2 :: runprog();
}
