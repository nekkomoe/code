#define ll __int128
inline ll sub_f(ll a, ll b, ll c, ll n) {
    if(n <= 0) return 0;
    return
        n * (n - 1) / 2 * (a / c)
      + n * (b / c)
      + sub_f(c, (a * n + b) % c, a % c, (a % c * n + b % c) / c);
}
inline ll f(ll a, ll b, ll c, ll n) {
    if(c < 0) {
        c = -c;
        a = -a, b = -b;
        return f(a, b, c, n);
    }
    if(a < 0) {
        a = -a;
        return f(a, b - a * (n - 1), c, n);
    }
    if(b < 0) {
        b = -b;
        ll k = b / c + (b % c != 0);
        return f(a, k * c - b, c, n) - k * n;
    }
    return sub_f(a, b, c, n);
}
#undef ll
