#pragma GCC optimize(2)
// #pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")


#include "dwa.hpp"
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
int a[int(2e5) + 10];

int rel[110][110], rev[int(2e5) + 10];

struct RANGE {
    int l, r;
};

struct QRYS {
    int id, x, y;
};

void bfs(int n) {
    vector<RANGE> qnow;

    qnow.push_back((RANGE) { 0, n - 1 });

    while(qnow.size()) {
        vector<RANGE> ran;
        vector<int> vals;
        vector<QRYS> qrys;
        vector<vector<int> > res;

        for(int i = 0 ; i < qnow.size() ; ++ i) {
            int l = qnow[i].l, r = qnow[i].r;
            if(l >= r) continue;
            int val = a[rand() % (r - l + 1) + l];
            int id = ran.size();
            ran.push_back((RANGE) { l, r });
            vals.push_back(val);
            res.push_back(vector<int> ());
            for(int j = l ; j <= r ; ++ j) {
                if(a[j] != val) {
                    qrys.push_back((QRYS) { id, a[j], val });
                }
            }
        }

        vector<int> ids;
        vector<pair<int, int> > nek;
        for(int i = 0 ; i < qrys.size() ; ++ i) {
            if(nek.size() < 70) {
                ids.push_back(qrys[i].id);
                nek.push_back({ qrys[i].x, qrys[i].y });
            }
            if(nek.size() == 70 || i + 1 == qrys.size()) {
                vector<int> R = ask(nek);
                for(int j = 0 ; j < ids.size() ; ++ j) {
                    res[ids[j]].push_back(R[j]);
                }
                ids.clear();
                nek.clear();
            }
        }

        vector<RANGE> qnxt;

        for(int i = 0 ; i < ran.size() ; ++ i) {
            int l = ran[i].l, r = ran[i].r;
            int val = vals[i];
            vector<int> lef, rig;
            for(int j = l, t = 0 ; j <= r ; ++ j) {
                if(a[j] != val) {
                    if(res[i][t] == 1) {
                        lef.push_back(a[j]);
                    } else {
                        rig.push_back(a[j]);
                    }
                    ++ t;
                }
            }
            int top = l - 1;
            for(int x: lef) {
                a[++ top] = x;
            }
            a[++ top] = val;
            int split = top;
            for(int x: rig) {
                a[++ top] = x;
            }
            qnxt.push_back((RANGE) { l, split - 1 });
            qnxt.push_back((RANGE) { split + 1, r });
        }

        qnow = qnxt;
    }
}

vector<int> work(int n) {
    srand(1294872);
    for(int i = 0 ; i < n ; ++ i) {
        a[i] = i;
    }
    bfs(n);
    vector<int> res(n);
    for(int i = 0 ; i < n ; ++ i) {
        res[a[i]] = i;
    }
    return res;
}
