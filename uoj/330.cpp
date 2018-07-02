#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cctype>
using namespace std;


#define FOR 1

#define END 2

#define VT_O1 1

#define VT_On 2

#define VT_O0 3

struct YuJu {
    int type;
    char va;
    int valType;
} yj[110];

int pos;

int think_time; // O(n^w)

int calc_time, mx_time, mul;

int stk[110], p, flag;

int T, L;

char tm[110], str[110];

int vis[310];

void init() {
    memset(yj, 0, sizeof yj);
    memset(vis, 0, sizeof vis);
    memset(str, 0, sizeof str);
    memset(tm, 0, sizeof tm);
    p = flag = pos = think_time = calc_time = mx_time = 0;
    mul = 1;
}

void work() {
    if(pos > L) return;
    int cur = pos, lastmul = mul, val = 0;

    if(yj[cur].valType == VT_O0) mul = 0;
    
    if(yj[cur].valType == VT_On) val = 1;
    
    calc_time += mul * val;
    mx_time = max(mx_time, calc_time);
    ++ pos;
    while(yj[pos].type == FOR) work();
    ++ pos;
    calc_time -= mul * val;
    mul = lastmul;
}


int main() {
    
    scanf("%d", &T);
    while(T --) {
        // ³õÊ¼»¯ 
        init();
        // ¶ÁÈë 
        scanf("%d%s", &L, tm + 1);
        if(tm[3] == '1') think_time = 0;
        else {
            int x = 0;
            for(int i = 5 ; isdigit(tm[i]) ; ++ i) {
                x = x * 10 + tm[i] - '0';
            }
            think_time = x;
        }
        // Ô¤´¦Àí 
        for(int i = 1 ; i <= L ; ++ i) {
            scanf("%s", str + 1);
            if(str[1] == 'F') {
                yj[i].type = FOR;
                stk[++ p] = i;
                scanf("%s", str + 1);
                char va = str[1];
                yj[i].va = va;
                if(vis[va]) {flag = 1;}if(flag) {scanf("%s", str + 1); scanf("%s", str + 1); continue;}
                vis[va] = 1;
                int xn = 0, yn = 0, x = 0, y = 0;
                scanf("%s", str + 1);
                for(int j = 1 ; str[j] ; ++ j) x = x * 10 + str[j] - '0';
                xn = str[1] == 'n';
                scanf("%s", str + 1);
                for(int j = 1 ; str[j] ; ++ j) y = y * 10 + str[j] - '0';
                yn = str[1] == 'n';
                if(xn == 0 && yn == 0) {
                    // x <= y O(1)
                    // x > y O(0)
                    if(x <= y) yj[i].valType = VT_O1;
                    else yj[i].valType = VT_O0;
                } else if(xn != 0 && yn == 0) {
                    // O(0)
                    yj[i].valType = VT_O0;
                } else if(xn == 0 && yn != 0) {
                    // O(n)
                    yj[i].valType = VT_On;
                } else if(xn != 0 && yn != 0) {
                    // O(1)
                    yj[i].valType = VT_O1;
                }
            } else if(str[1] == 'E') {
                yj[i].type = END;
                if(!p) {flag = 1;}if(flag) {continue;}
                vis[yj[stk[p --]].va] = 0;
            }
        }
        
        if(p) {flag = 1;}
        if(flag) {
            puts("ERR");
            goto nxt;
        }
        // Ö´ÐÐ
        pos = 1;
        while(pos <= L) work();
        if(mx_time == think_time) puts("Yes");
        else puts("No");
        nxt:;
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

