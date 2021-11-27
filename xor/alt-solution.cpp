#include <iostream>
#include <set>
using namespace std;

typedef long long ll;

ll calc(ll n) {
    if (n == 1) return 0;
    ll total = 0;
    int cur  = 2;
    while (cur <= n) {
        if (2 * cur > n) {
            ll m = n - cur;
            total += m * (m + 1);
        } else {
            ll m = cur - 1;
            total += m * (m + 1);
        }
        cur *= 2;
    }
    return total;
}

ll pcalc(ll n) {
    ll cur = 1;
    while (cur <= n) cur *= 2;
    cur /= 2;
    return (n - cur) * 2;
}

int main() {
    int n, m;
    cin >> n >> m;
    ll result = calc(n);

    set<int> st;

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        if (st.find(x) != st.end() || x > n) continue;
        st.insert(x);
        result -= pcalc(x);
    }
    cout << result << endl;
}
