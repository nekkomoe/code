// 题意：n个串的最长公共子串
// 题解：建立n-1个后缀自动机，然后用第一个串在上面跑，并用最小的长度更新答案。证明：后缀自动机上的状态相当于以当前字符串为后缀的最长匹配
// 标签：后缀数组，后缀树，后缀自动机

#include <bits/stdc++.h>

using namespace std;

const int N = 2000 * 5 * 2 + 10;

struct SAM {
    int ch[N][40], pre[N], len[N], sz[N], cnt, last;
    SAM() { cnt = last = 1; }
    int nd(int l) {
        return len[++ cnt] = l, cnt;
    }
    void ins(int c) {
        int p, np, q, nq;
        pre[np = last = nd(len[p = last] + 1)] = 1;
        sz[np] = 1;
        while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
        if(p) {
            pre[np] = q = ch[p][c];
            if(len[p] + 1 != len[q]) {
                nq = nd(len[p] + 1);
                pre[nq] = pre[q], pre[q] = pre[np] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
            }
        }
    }
} sam[10];

string s[10];

int n, ans;

int main() {

    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    cin >> n;
    
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> s[i];
        for(int j = 0 ; j < s[i].length() ; ++ j) {
            sam[i].ins(s[i][j] - 'a');
        }
    }
    
    if(n == 1) printf("%d\n", s[1].length());
    else {
        int sts[6] = { 0, 1, 1, 1, 1, 1 }, lens[6] = { 0, 0, 0, 0, 0, 0 }, len = s[1].length();
        for(int i = 0 ; i < s[1].length() ; ++ i) {
            
            int c = s[1][i] - 'a';
            
            len = s[1].length();
            
            for(int j = 2 ; j <= n ; ++ j) {
                if(sam[j].ch[sts[j]][c]) {
                    ++ lens[j];
                    sts[j] = sam[j].ch[sts[j]][c];
                } else {
                    while(sts[j] && !sam[j].ch[sts[j]][c]) {
                        sts[j] = sam[j].pre[sts[j]];
                    }
                    if(sts[j]) {
                        lens[j] = sam[j].len[sts[j]] + 1;
                        sts[j] = sam[j].ch[sts[j]][c];
                    } else {
                        sts[j] = 1;
                        lens[j] = 0;
                    }
                }
                len = min(len, lens[j]);
            }
            ans = max(ans, len);
        }
    }
    
    printf("%d\n", ans);
}
