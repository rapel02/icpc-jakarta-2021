#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

long long powmod(long long b, long long p) {
  long long r = 1;
  for (; p; p >>= 1, b = b * b % mod)
    if (p & 1) r = r * b % mod;
  return r;
}

vector<long long> fac, inv;
long long C(int n, int k) {
  if (n < k || k < 0) return 0LL;
  return (fac[n] * inv[k] % mod) * inv[n - k] % mod;
}

long long calc_a_le_b(int n, int m, int a, int len, bool can_a_eq_b = false) {
  int rmin = max(len, a), rmax = min(a + len - 1, n);
  if (rmax < rmin) return 0;
  int bstart = a;
  if ((m & 1) == 0) ++bstart;
  if (bstart == a && !can_a_eq_b) {
    bstart += 2;
  }
  long long cmin = C((m + bstart - a - 3) / 2, len - 1);
  long long ans  = 0;
  int from = rmin, til = from + 2 * ((rmax - from) / 2);
  if ((from - bstart) & 1) {
    --from, --til;
  }
  from = max(from, bstart);
  if (from <= til) {
    assert(((m + til - a + 1) & 1) == 0);
    assert(((m + from - a - 1) & 1) == 0 && (m + from - a - 1) >= 0);
    til           = (m + til - a + 1) / 2;
    from          = (m + from - a - 1) / 2;
    long long cnt = til - from;
    ans           = (ans + C(til, len) - C(from, len)) % mod;
    ans           = (ans - cnt * cmin) % mod;
  }
  if (rmin < rmax) {
    from = rmin + 1, til = from + 2 * ((rmax - from) / 2);
    if ((from - bstart) & 1) {
      --from, --til;
    }
    from = max(from, bstart);
    if (from <= til) {
      assert(((m + til - a + 1) & 1) == 0);
      assert(((m + from - a - 1) & 1) == 0 && (m + from - a - 1) >= 0);
      til           = (m + til - a + 1) / 2;
      from          = (m + from - a - 1) / 2;
      long long cnt = til - from;
      ans           = (ans + C(til, len) - C(from, len)) % mod;
      ans           = (ans - cnt * cmin) % mod;
    }
  }
  ans %= mod;
  if (ans < 0) ans += mod;
  return ans;
}

long long calc(int n, int m, int a, int len) {
  long long ans = calc_a_le_b(n, m, a, len, true) + calc_a_le_b(n, m, n + 1 - a, len, false);
  ans %= mod;
  if (ans < 0) ans += mod;
  return ans;
}

int main() {
  int n, m, a;
  scanf("%d %d %d", &n, &m, &a);
  if (m == 1) {
    puts("1");
    return 0;
  }
  fac.resize(n + m);
  inv.resize(fac.size());
  fac[0] = inv[0] = 1;
  for (int i = 1; i < (int)fac.size(); ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = powmod(fac[i], mod - 2);
  }
  long long ans = 0;
  for (int len = 2; len <= min(n, m); ++len) {
    ans = (ans + calc(n, m, a, len)) % mod;
  }
  if (ans < 0) ans += mod;
  printf("%lld\n", ans);
  return 0;
}
