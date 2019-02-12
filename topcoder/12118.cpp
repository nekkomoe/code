#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll c, a, t, n, len;
string S, T;
ll trans[500][500], stp[500][500];

namespace runprog {
    int lim;
    struct Mat {
        ll a[110][110];
        Mat() {
            memset(a, 0, sizeof a);
        }
        ll* operator [] (int x) {
            return a[x];
        }
        Mat operator * (Mat b) {
            Mat c;
            for(int i = 1 ; i <= lim ; ++ i) {
                for(int j = 1 ; j <= lim ; ++ j) {
                    for(int k = 1 ; k <= lim ; ++ k) {
                        c[i][j] = (c[i][j] + a[i][k] * b[k][j] % mod) % mod;
                    }
                }
            }
            return c;
        }
        void output() {
            for(int i = 1 ; i <= lim ; ++ i) {
                for(int j = 1 ; j <= lim ; ++ j) {
                    printf("%lld ", a[i][j]);
                }
                puts("");
            }
        }
    };
    Mat pw(Mat a, ll b) {
        Mat res;
        for(int i = 1 ; i <= lim ; ++ i) {
            res[i][i] = 1;
        }
        for( ; b ; b >>= 1, a = a * a) {
            if(b & 1) {
                res = res * a;
            }
        }
        return res;
    }
    struct cMP { int x, y, z; } sta[120];
    int tot;
    int rev[50][50][50], endsta[120];
    int val[50];
    Mat poly;
    Mat init_sta() {
        int arg[3] = { 0, 0, 0 };
        for(int i = 1 ; i <= len ; ++ i) {
            arg[stp[S[i]][T[i]]] ++;
        }
        Mat res;
        res[1][rev[arg[0]][arg[1]][arg[2]]] ++;
        if(arg[0] == len) {
            res[1][lim] ++;
        }
        return res;
    }
    ll sol() {
        for(int x = 0 ; x <= len ; ++ x) {
            for(int y = 0 ; y <= len ; ++ y) {
                int z = len - x - y;
                if(z >= 0) {
                    sta[++ tot] = (cMP) { x, y, z };
                    rev[x][y][z] = tot;
                    if(x == len) {
                        endsta[rev[x][y][z]] = 1;
                    }
                }
            }
        }
        lim = tot + 1;
        for(int x = 0 ; x <= len ; ++ x) {
            for(int y = 0 ; y <= len ; ++ y) {
                int z = len - x - y;
                if(z >= 0) {
                    int before_sta = rev[x][y][z];
                    int after_sta;
                    if(x - 1 >= 0) {
                        after_sta = rev[x - 1][y][z + 1];
                        poly[before_sta][after_sta] = x;

                        if(endsta[after_sta]) {
                            poly[before_sta][lim] = x;
                        }
                    }
                    if(y - 1 >= 0) {
                        after_sta = rev[x + 1][y - 1][z];
                        poly[before_sta][after_sta] = y;
                        if(endsta[after_sta]) {
                            poly[before_sta][lim] = y;
                        }
                    }
                    if(z - 1 >= 0) {
                        after_sta = rev[x][y + 1][z - 1];
                        poly[before_sta][after_sta] = z;

                        if(endsta[after_sta]) {
                            poly[before_sta][lim] = z;
                        }
                    }
                }
            }
        }
        poly[lim][lim] = 1;
        Mat base = init_sta();
        ll cnt = n;
        for(int i = 1 ; i <= len ; ++ i) {
            cnt -= trans[S[i]][T[i]];
        }
        if(cnt < 0) {
            return 0;
        }
        cnt /= c + a + t;
        cnt *= 3;
        for(int i = 1 ; i <= len ; ++ i) {
            cnt += stp[S[i]][T[i]];
        }
        Mat output = base * pw(poly, cnt);
        return output[1][lim];
    }
}
class ConversionMachine {
public:  
    int countAll(string inp_S, string inp_T, vector <int> inp_cost, int inp_n) {
        c = inp_cost[0], a = inp_cost[1], t = inp_cost[2];
        n = inp_n;
        trans['a']['b'] = c, stp['a']['b'] = 1;
        trans['b']['c'] = a, stp['b']['c'] = 1;
        trans['c']['a'] = t, stp['c']['a'] = 1;
        trans['a']['c'] = trans['a']['b'] + trans['b']['c'], stp['a']['c'] = 2;
        trans['b']['a'] = trans['b']['c'] + trans['c']['a'], stp['b']['a'] = 2;
        trans['c']['b'] = trans['c']['a'] + trans['a']['b'], stp['c']['b'] = 2;
        S = " " + inp_S;
        T = " " + inp_T;
        len = inp_S.length();
        return runprog :: sol();
    }
};
