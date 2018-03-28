#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 2e5 + 10;

int len[N], ch[N][30], pre[N], tot = 1, last = 1;

ll ans;

int nd(int l) {
    tot ++;
    len[tot] = l;
    memset(ch[tot], 0, sizeof ch[tot]);
    pre[tot] = 0;
    return tot;
}

struct fallback {
    int *a, pos, val;
    void run() {
        a[pos] = val;
    }
};

vector<fallback> vec;

stack<vector<fallback> > sta;

stack<int> last_sta, tot_sta;

stack<ll> ans_sta;

int val(int p) { return len[p] - len[pre[p]]; }

void add(int c) {
    int p, np, q, nq;

    ans_sta.push(ans);
    last_sta.push(last);
    tot_sta.push(tot);
    vec.clear();

    pre[np = last = nd(len[p = last] + 1)] = 1;
    ans += val(np);
    while(p && !ch[p][c]) {
        vec.push_back((fallback) { ch[p], c, ch[p][c] });
        ch[p][c] = np;
        p = pre[p];
    }

    if(p) {
        ans -= val(np);
        pre[np] = q = ch[p][c];
        ans += val(np);
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            memcpy(ch[nq], ch[q], sizeof ch[q]);

            vec.push_back((fallback) { pre, q, pre[q] });

            pre[nq] = pre[q];
            ans += val(nq);

            ans -= val(q) + val(np);
            pre[q] = pre[np] = nq;
            ans += val(q) + val(np);

            while(p && ch[p][c] == q) {
                vec.push_back((fallback) { ch[p], c, ch[p][c] });
                ch[p][c] = nq;
                p = pre[p];
            }

        }
    }

    sta.push(vec);
}

void rollback() {
    ans = ans_sta.top(); ans_sta.pop();
    tot = tot_sta.top(); tot_sta.pop();
    last = last_sta.top(); last_sta.pop();
    vector<fallback> &vec = sta.top();
    for(vector<fallback> :: iterator it = vec.begin() ; it != vec.end() ; ++ it) {
        it -> run();
    }
    sta.pop();
}

char s[N];

int main() {
    scanf("%s", s + 1);
    for(int i = 1 ; s[i] ; ++ i) {
        if(s[i] == '-') rollback();
        else add(s[i] - 'a');
        printf("%lld\n", ans);
    }
}

