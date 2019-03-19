#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

struct P {
    ll x, y;
    P operator - (P p) {
        return (P) { x - p.x, y - p.y };
    }
    ll dot (P p) {
        return x * p.x + y * p.y;
    }
    ll operator * (P p) {
        return x * p.y - p.x * y;
    }
    bool operator == (P p) {
        return x == p.x && y == p.y;
    }
} p[5010];
ll sgn(ll x) {
    return x <= 0;
}

int n;
char str[5010];

namespace force {
    int a[5010];
    struct LINE {
        P a, b;
    };
    vector<LINE> ln;

    bool check_inj(LINE u, LINE v) {
        if(u.a == v.a || u.a == v.b) return 0;
        if(u.b == v.a || u.b == v.b) return 0;

        if(sgn((u.b - u.a) * (v.a - u.a)) == sgn((u.b - u.a) * (v.b - u.a))) return 0;
        swap(u, v);
        if(sgn((u.b - u.a) * (v.a - u.a)) == sgn((u.b - u.a) * (v.b - u.a))) return 0;
        return 1;
    }

    bool check_no_inj() {
        for(int i = 0 ; i < ln.size() ; ++ i) {
            for(int j = 0 ; j < i ; ++ j) {
                if(check_inj(ln[i], ln[j])) {
                    return 0;
                }
            }
        }
        return 1;
    }

    bool check() {
        for(int i = 2 ; i < n ; ++ i) {
            char c;
            if((p[a[i - 1]] - p[a[i]]) * (p[a[i + 1]] - p[a[i]]) >= 0) {
                c = 'R';
            } else {
                c = 'L';
            }
            if(c != str[i - 1]) {
                return 0;
            }
        }

        ln.clear();
        for(int i = 1 ; i < n ; ++ i) {
            ln.push_back((LINE) {
                p[a[i]],
                p[a[i + 1]]
            });
        }
        return check_no_inj();
    }

    void sol() {
        for(int i = 1 ; i <= n ; ++ i) a[i] = i;
        do {
            if(check()) {
                for(int i = 1 ; i <= n ; ++ i) {
                    printf("%d ", a[i]);
                }
                return ;
            }
        } while(next_permutation(a + 1, a + 1 + n));
    }

    int vis[5010];

    void dfs(int stp, int lst, int pos) {
        int flag = 1;
        vis[stp] = 1;
        a[pos + 1] = stp;
        for(int nxt = 1 ; nxt <= n ; ++ nxt) {
            if(!vis[nxt]) {
                flag = 0;
                if(lst && "LR"[(p[lst] - p[stp]) * (p[nxt] - p[stp]) >= 0] != str[pos]) {
                    continue ;
                }
                dfs(nxt, stp, pos + 1);
            }
        }
        vis[stp] = 0;
        if(flag && check()) {
            for(int i = 1 ; i <= n ; ++ i) {
                printf("%d ", a[i]);
            }
            exit(0);
        }
    }

    void JUSTDFS() {

        for(int i = 1 ; i <= n ; ++ i) {
            dfs(i, 0, 0);
        }
    }

    bool cmp(P a, P b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    void newdfs(int stp, int lst, int pos) {
        // printf("stp = %d\n", stp);
        int flag = 1;
        vis[stp] = 1;
        a[pos + 1] = stp;
        int cho = -1;
        for(int nxt = 1 ; nxt <= n ; ++ nxt) {
            if(!vis[nxt]) {
                flag = 0;
                if(lst && (p[lst] - p[stp]) * (p[nxt] - p[stp]) >= 0) {
                    continue ;
                }
                // newdfs(nxt, stp, pos + 1);
                if(cho == -1) cho = nxt;
                else {
                    if((p[nxt] - p[stp]) * (p[cho] - p[stp]) >= 0) {
                        cho = nxt;
                    }
                }
            }
        }

        if(cho != -1) {
            newdfs(cho, stp, pos + 1);
        }

        vis[stp] = 0;
        if(flag && check()) {
            for(int i = 1 ; i <= n ; ++ i) {
                printf("%d ", a[i]);
            }
            exit(0);
        }
    }

    void allL() {
        for(int i = 1 ; i <= n ; ++ i) {
            newdfs(i, 0, 0);
        }
    }

    void LRdfs(int stp, int lst, int pos) {
        // printf("pos = %d\n", pos + 1);
        vis[stp] = 1;
        a[pos + 1] = stp;
        int cho = -2;
        int tot = 0;
        for(int nxt = 1 ; nxt <= n ; ++ nxt) {
            if(!vis[nxt]) {
                if(cho == -2) cho = -1;
                if(lst && "LR"[(p[lst] - p[stp]) * (p[nxt] - p[stp]) >= 0] != str[pos]) {
                    continue ;
                }
                ln.clear();
                for(int i = 1 ; i <= pos ; ++ i) {
                    ln.push_back((LINE) {
                        p[a[i]],
                        p[a[i + 1]]
                    });
                }
                ln.push_back((LINE) { p[stp], p[nxt] });

                if(check_no_inj()) {
                    if(cho == -1) cho = nxt;
                    else {
                        // if((p[nxt] - p[stp]) * (p[cho] - p[stp]) >= 0) {
                        //     cho = nxt;
                        // }

                        if(str[pos] == 'L') {
                            if((p[nxt] - p[stp]) * (p[cho] - p[stp]) >= 0) {
                                cho = nxt;
                            }
                        } else {
                            if((p[nxt] - p[stp]) * (p[cho] - p[stp]) <= 0) {
                                cho = nxt;
                            }
                        }
                    }
                }
            }
        }

        if(cho >= 1) {
            LRdfs(cho, stp, pos + 1);
        }

        vis[stp] = 0;

        if(pos + 1 == n) {
            ln.clear();
            for(int i = 1 ; i < n ; ++ i) {
                ln.push_back((LINE) {
                    p[a[i]],
                    p[a[i + 1]]
                });
            }
            cout << check_no_inj() << endl;
            for(int i = 1 ; i <= n ; ++ i) {
                printf("%d ", a[i]);
            }
            exit(0);
        }
    }

    void newLRdfs(int stp, int lst, int pos) {
        // printf("stp = %d\n", stp);
        int flag = 1;
        vis[stp] = 1;
        a[pos + 1] = stp;
        int cho = -1;
        for(int nxt = 1 ; nxt <= n ; ++ nxt) {
            if(!vis[nxt]) {
                flag = 0;
                if(lst && "LR"[(p[lst] - p[stp]) * (p[nxt] - p[stp]) >= 0] != str[pos]) {
                    continue ;
                }
                if(cho == -1) cho = nxt;
                else {
                    if(str[pos] == 'L') {
                        if((p[nxt] - p[stp]) * (p[cho] - p[stp]) <= 0) {
                            cho = nxt;
                        }
                    } else {
                        if((p[nxt] - p[stp]) * (p[cho] - p[stp]) >= 0) {
                            cho = nxt;
                        }
                    }
                }
            }
        }

        if(cho != -1) {
            newLRdfs(cho, stp, pos + 1);
        }

        vis[stp] = 0;
        if(flag && check()) {
            for(int i = 1 ; i <= n ; ++ i) {
                printf("%d ", a[i]);
            }
            exit(0);
        }
    }

    void LR() {
        // srand((unsigned long long) new char);
        // srand(19260817);
        // for(int i = 2 ; i <= n ; ++ i) {
        //     swap(p[rand() % (i - 1) + 1], p[i]);
        // }
        // random_shuffle(p + 1, p + 1 + n);
        for(int i = 1 ; i <= n ; ++ i) {
            LRdfs(i, 0, 0);
            newLRdfs(i, 0, 0);
        }
    }

    int allL_check() {
        for(int i = 1 ; i <= n ; ++ i) {
            if(str[i] == 'R') {
                return 0;
            }
        }
        return 1;
    }

    void getcheck() {
        a[1] = 1;
        a[2] = 6;
        a[3] = 5;
        a[4] = 4;
        a[5] = 2;
        a[6] = 7;
        a[7] = 3;
        a[8] = 8;
        printf("check res: %d\n", check());


        for(int i = 2 ; i < n ; ++ i) {
            char c;
            if((p[a[i - 1]] - p[a[i]]) * (p[a[i + 1]] - p[a[i]]) >= 0) {
                c = 'R';
            } else {
                c = 'L';
            }
            if(c != str[i - 1]) {
                printf("wa because when i = %d, c = %c, str = %c\n", i, c, str[i - 1]);
            }
            cout << c;
        }
        cout << endl;

        ln.clear();
        for(int i = 1 ; i < n ; ++ i) {
            ln.push_back((LINE) {
                p[a[i]],
                p[a[i + 1]]
            });
        }
        printf("check no inj: %d\n", check_no_inj());

        for(int i = 0 ; i < ln.size() ; ++ i) {
            for(int j = 0 ; j < i ; ++ j) {
                if(check_inj(ln[i], ln[j])) {
                    printf("inj: (%lld,%lld)-(%lld,%lld) with (%lld,%lld)-(%lld,%lld)\n", ln[i].a.x, ln[i].a.y, ln[i].b.x, ln[i].b.y, ln[j].a.x, ln[j].a.y, ln[j].b.x, ln[j].b.y);
                }
            }
        }
    }
}

int ans[5010], top, vis[5010];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
    }
    scanf("%s", str + 1);

    int id = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        if(p[i].x > p[id].x) {
            id = i;
        }
    }

    ans[++ top] = id, vis[id] = 1;
    for(int i = 1 ; i <= n - 2 ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(!vis[j]) {
                id = j;
                break;
            }
        }
        for(int j = id + 1 ; j <= n ; ++ j) {
            if(!vis[j]) {
                if(((p[id] - p[ans[i]]) * (p[j] - p[ans[i]]) > 0) != (str[i] == 'L')) {
                    id = j;
                }
            }
        }
        ans[++ top] = id;
        vis[id] = 1;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        if(!vis[i]) {
            ans[++ top] = i;
            break;
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", ans[i]);
    }
}
