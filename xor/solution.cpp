#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int maxn = 100005;

int N, M;
int S[maxn];

int one(int n) {
  int msb, x = n;
  while (x != 0) {
    msb = x;
    x &= x - 1;
  }
  return (n ^ msb) * 2;
}


int main(int argc, char *argv[]) {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < M; ++i) {
    scanf("%d", &S[i]);
  }

  ll ans = 0;
  for (int i = 1; i <= N; ++i) {
    ans += one(i);
  }

  set<int> done;
  for (int i = 0; i < M; ++i) {
    if (done.count(S[i]) == 0 && S[i] <= N) {
      ans -= one(S[i]);
      done.insert(S[i]);
    }
  }

  printf("%lld\n", ans);

  return 0;
}
