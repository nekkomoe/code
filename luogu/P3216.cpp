#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int mod;

__int128 mul(__int128 x, __int128 y) {
    return (__int128) (x % mod) * (y % mod) % mod;
}

__int128 pw(__int128 a, __int128 b) {
    assert(b >= 0);
    a %= mod;
    __int128 r = 1;
    for( ; b ; b >>= 1, a = mul(a, a)) {
        if(b & 1) {
            r = mul(r, a);
        }
    }
    return r;
}

struct Mat {
    __int128 a[3][3];
    Mat() {
        memset(a, 0, sizeof a);
    }
    __int128 *operator [](int x) {
        return a[x];
    }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 3 ; ++ i) {
            for(int j = 0 ; j < 3 ; ++ j) {
                for(int k = 0 ; k < 3 ; ++ k) {
                    c[i][j] = (c[i][j] + mul(a[i][k], b[k][j])) % mod;
                }
            }
        }
        return c;
    }
    void output() {
        for(int i = 0 ; i < 3 ; ++ i) {
            for(int j = 0 ; j < 3 ; ++ j) {
                printf("%lld ", (ll) a[i][j]);
            }
            puts("");
        }
        puts("");
    }
};
Mat pw(Mat a, __int128 b) {
    Mat r;
    for(int i = 0 ; i < 3 ; ++ i) {
        r[i][i] = 1;
    }
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            r = r * a;
        }
    }
    return r;
}

__int128 getinv(__int128 n) {
    return pw(n, mod - 2);
}

__int128 ans;
__int128 L, A, B;
__int128 log10(__int128 x) {
    // printf("log(%lld) = %lld\n", (ll) x, (ll) (log(x) / log(10)));
    // cout << log(x) << endl;
    // cout << log(10) << endl;
    // return log(x) / log(10) + 1;
    __int128 res = 0;
    if(x == 0) return 1;
    while(x) {
        x /= 10;
        ++ res;
    }
    return res;
}

int main() {
    ll _L, _A, _B;
    _A = 1, _B = 1;
    cin >> _L >> mod;
    L = _L - 1, A = _A, B = _B;
    ans = 0;

    // +B ~ +LB
    for(__int128 i = 0 ; i <= L ; ) {

        // printf("begin\n");

        __int128 len = log10(A + (__int128) i * B);
        __int128 j = i, l = i, r = L;
        while(l <= r) {
            __int128 mid = (l + r) >> 1;
            __int128 nl = log10(A + mid * B);
            if(nl <= len) { // 实际上只有==
                j = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        // printf("%lld, %lld\n", (ll) i, (ll) j);

        // [i, j] 中转移都是 * 10^len
        __int128 l10 = pw(10, len);
        Mat base, coef;
        // (A+iB)(A+(i+1)B)(A+(i+2)B)...(A+jB)
        
        base[0][0] = (A + mul(i, B)) % mod, base[0][1] = 0, base[0][2] = 1;

        coef[0][0] = 1, coef[0][1] = 1, coef[0][2] = 0;
        coef[1][0] = 0, coef[1][1] = l10, coef[1][2] = 0;
        coef[2][0] = B, coef[2][1] = 0, coef[2][2] = 1;

        // printf("pw = %lld\n", (ll) (j - i + 1));
        // printf("%lld\n", (ll) len);
        // printf("%lld\n", (ll) (len * (j - i + 1)));
        base = base * pw(coef, j - i + 1);

        // printf("res = %lld\n", (ll) base[0][1]);
        ans = (mul(ans, pw(10, len * (j - i + 1))) + base[0][1]) % mod;

        i = j + 1;
        // printf("end\n");
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
