#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

const int maxn = 100005;
const int maxa = 1000000;
const int maxp = 1000;

vector<int> prime;
bool is_prime[maxp+5];

int N;
int A[maxn];
vector<pii> E;
unordered_map<int, vector<pii>> member;

int p[maxn];
int r[maxn];
int s[maxn];
int counter = 0;
int record[maxn];
void reset() {
  counter = 0;
  memset(record, 0, sizeof(record));
}
int find(int x) {
  if (record[x] != counter) {
    p[x] = x;
    r[x] = 0;
    s[x] = 1;
    record[x] = counter;
  }
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}
void link(int x, int y) {
  x = find(x), y = find(y);
  if (x == y) return;
  if (r[x] == r[y]) r[x]++;
  if (r[x]  < r[y]) {
    p[x] = y;
    s[y] += s[x];
  }
  else {
    p[y] = x;
    s[x] += s[y];
  }
}


int main(int argc, char *argv[]) {

  memset(is_prime, true, sizeof(is_prime));
  for (int i = 2; i*i <= maxp; ++i) if (is_prime[i])
    for (int j = i*i; j <= maxp; j += i) is_prime[j] = false;
  for (int i = 2; i <= maxp; ++i) if (is_prime[i])
    prime.push_back(i);

  scanf("%d", &N);
  for (int i = 1; i <= N; ++i)
    scanf("%d", &A[i]);
  for (int i = 1; i < N; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    E.push_back(make_pair(u, v));
  }

  set<int> candidates;
  for (auto e : E) {
    int gcd = __gcd(A[e.first], A[e.second]);

    for (auto p : prime) {
      if (p > gcd) break;
      if (gcd % p == 0) {
        member[p].push_back(e);
        candidates.insert(p);
        while (gcd % p == 0) gcd /= p;
      }
    }

    if (gcd != 1) {
      member[gcd].push_back(e);
      candidates.insert(gcd);
    }
  }

  int ans = 0;
  for (int i = 1; i <= N; ++i)
    if (A[i] != 1) ans = 1;

  reset();

  for (auto p : candidates) {

    ++counter;

    int tans = 0;
    for (auto edge : member[p]) {
      link(edge.first, edge.second);
      tans = max(tans, s[find(edge.first)]);
    }

    ans = max(ans, tans);
  }

  printf("%d\n", ans);
  
  return 0;
}
