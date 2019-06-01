#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000000007;

// #define DEFAFA

// #ifdef DEFAFA

// #define printf printf
// #define puts puts

// #else

// #define printf
// #define puts

// #endif

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

const int N = 2e5 + 10;
char A[N], B[N];
int q_a, q_b, q_c, q_d;
ll fac[N], invfac[N];
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}

int check(char *s) {
    int n = strlen(s + 1);
    // a = 子串“00” 的数量，b = 子串 “01” 的数量，c = 子串 “10” 的数量，d = 子串 “11” 的数量。
    int a = 0, b = 0, c = 0, d = 0;

    for(int i = 2 ; i <= n ; ++ i) {
        if(s[i - 1] == '0' && s[i] == '0') {
            a ++;
        } else if(s[i - 1] == '0' && s[i] == '1') {
            b ++;
        } else if(s[i - 1] == '1' && s[i] == '0') {
            c ++;
        } else if(s[i - 1] == '1' && s[i] == '1') {
            d ++;
        } else {
            // assert(0);
        }
    }

    return q_a == a && q_b == b && q_c == c && q_d == d;
}

int check_same(int a, int b, int c, int d) {
    return q_a == a && q_b == b && q_c == c && q_d == d;
}

int all_le(int a, int b, int c, int d) {
    return a <= q_a && b <= q_b && c <= q_c && d <= q_d;
}

void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

ll f(int x, int p) {
    // x个元素分成p段
    if(x < p || x < 0) {
        return 0;
    } else if(x == p && x == 0) {
        return 1;
    } else {
        return C(x - 1, p - 1);
    }
}

ll calc_0_odd(int a, int b, int c, int d, int L) {
    if(a >= 0 && b >= 0 && c >= 0 && d >= 0) {
        int p = b + 1;
        int x = a + b + 1;
        if(p >= 1 && x >= 1 && c == p - 1 && d == L - x - p + 1) {
            return f(x, p) * f(L - x, p - 1) % mod;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

ll calc_0_even(int a, int b, int c, int d, int L) {
    if(a >= 0 && b >= 0 && c >= 0 && d >= 0) {
        int p = b;
        int x = a + b;
        if(p >= 1 && x >= 1 && c == p - 1 && d == L - x - p) {
            return f(x, p) * f(L - x, p) % mod;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

ll calc_1_odd(int a, int b, int c, int d, int L) {
    // printf("abcd: %d %d %d %d\n", a, b, c, d);
    if(a >= 0 && b >= 0 && c >= 0 && d >= 0) {
        int p = b + 1;
        int x = L - a - p + 1;
        if(x >= 1 && p >= 1 && c == p - 1 && d == x - p) {
            // printf("%d 个元素分成 %d 段\n", x, p);
            // printf("%d 个元素分成 %d 段\n", L - x, p - 1);
            return f(x, p) * f(L - x, p - 1) % mod;
        } else {
            // puts("failed 1");
            return 0;
        }
    } else {
        // puts("failed 2");
        return 0;
    }
}

ll calc_1_even(int a, int b, int c, int d, int L) {
    if(a >= 0 && b >= 0 && c >= 0 && d >= 0) {
        int p = b + 1;
        int x = L - a - p;
        if(x >= 1 && p >= 1 && c == p && d == x - p) {
            return f(x, p) * f(L - x, p) % mod;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

ll sol(char *s) {
    int n = strlen(s + 1);
    // a = 子串“00” 的数量，b = 子串 “01” 的数量，c = 子串 “10” 的数量，d = 子串 “11” 的数量。
    int a = 0, b = 0, c = 0, d = 0;
    ll res = 0;
    int hasled = 0;

    for(int i = 1 ; i <= n ; ++ i) {
        if(s[i] == '1') {
            // 这一位强制填0
            // 也就是 [1, i - 1] 是和 s 前缀相同的
            // 第 i 位为0
            // [i+1, n] 可以填 00000 ~ 11111

            int tmpa = a;
            int tmpb = b;
            int tmpc = c;
            int tmpd = d;

            int len = n - i;
            int ex_00 = i - 1 >= 1 && s[i - 1] == '0' && hasled;
            int ex_10 = i - 1 >= 1 && s[i - 1] == '1' && hasled;
            a += ex_00, c += ex_10;
            if(len == 0) {
                if(hasled) {
                    upd(res, check_same(a, b, c, d));
                }
            } else {
                // 00000 ~ 11111

                // 1 ... 0 (000~111)

                if(hasled) {
                    // puts("in 1");
                    if(all_le(a, b, c, d)) {
                        int tar_a = q_a - a;
                        int tar_b = q_b - b;
                        int tar_c = q_c - c;
                        int tar_d = q_d - d;
                        
                        // 第一个位置必须放0
                        // 00
                        upd(res, calc_0_odd(tar_a - 1, tar_b, tar_c, tar_d, len));
                        upd(res, calc_0_even(tar_a - 1, tar_b, tar_c, tar_d, len));

                        // 第一个位置必须放1
                        // 01
                        upd(res, calc_1_odd(tar_a, tar_b - 1, tar_c, tar_d, len));
                        upd(res, calc_1_even(tar_a, tar_b - 1, tar_c, tar_d, len));
                    }
                } else {
                    // 0000 ... 0 1 (000 ~ 111)
                    int tarlen = len;
                    for(int t = tarlen ; t >= 1 ; -- t) {
                        int len = t;
                        if(len >= 1) {
                            -- len;

                            // puts("in 2");
                            // printf("i = %d\n", i);
                            // printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
                            // printf("len = %d\n", len);

                            if(len == 0) {
                                upd(res, check_same(a, b, c, d));
                            } else {
                                int tar_a = q_a - a;
                                int tar_b = q_b - b;
                                int tar_c = q_c - c;
                                int tar_d = q_d - d;

                                // printf("tar: (%d, %d, %d, %d)\n", tar_a, tar_b, tar_c, tar_d);

                                // 第一个位置必须放0
                                // 10
                                upd(res, calc_0_odd(tar_a, tar_b, tar_c - 1, tar_d, len));
                                upd(res, calc_0_even(tar_a, tar_b, tar_c - 1, tar_d, len));

                                // 第一个位置必须放1
                                // 11
                                upd(res, calc_1_odd(tar_a, tar_b, tar_c, tar_d - 1, len));
                                upd(res, calc_1_even(tar_a, tar_b, tar_c, tar_d - 1, len));    
                            }
                        }
                    }
                }
            }

            a = tmpa;
            b = tmpb;
            c = tmpc;
            d = tmpd;
        }

        if(s[i] == '1') {
            hasled = 1;
        }

        // 这一位也顶格
        if(i - 1 >= 1) {
            if(s[i - 1] == '0' && s[i] == '0') {
                a ++;
            } else if(s[i - 1] == '0' && s[i] == '1') {
                b ++;
            } else if(s[i - 1] == '1' && s[i] == '0') {
                c ++;
            } else if(s[i - 1] == '1' && s[i] == '1') {
                d ++;
            } else {
                // assert(0);
            }
        }
    }

    // printf("res = %d\n", res);
    upd(res, check_same(a, b, c, d));

    return res;
}

int main() {

    init(N - 1);

    scanf("%s%s", A + 1, B + 1);

    scanf("%d%d%d%d", &q_a, &q_b, &q_c, &q_d);

    // cout << sol(A) << endl;
    // return 0;

    // cout << sol(B) << endl;
    // cout << sol(A) << endl;
    // cout << check(A) << endl;
    // return 0;

    // #undef printf

    ll ans = sol(B) - sol(A) + check(A);
    printf("%lld\n", (ans % mod + mod) % mod);
    // if(ans) {
    //     cerr << ans << endl;
    //     system("sleep 1");
    //     while(1);
    // }
}
