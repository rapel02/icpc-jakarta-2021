#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;

int N, M;
string S[maxn];

int main(int argc, char *argv[]) {
  cin >> N >> M;
  for (int i = 0; i < N; ++i)
    cin >> S[i];

  int ans = 0;
  for (int j = 0; j < M; ++j) {
    map<char, int> m;
    for (int i = 0; i < N; ++i)
      ++m[S[i][j]];
    int hi = 0;
    for (auto p : m)
      hi = max(hi, p.second);
    ans += N - hi;
  }

  cout << ans << endl;
  
  return 0;
}
