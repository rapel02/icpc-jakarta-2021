#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;
const int EPS = 1e-9;

struct tplanet { int R, theta, T; };
struct tpoint { double x, y; };

int N;
tplanet planets[maxn];
tpoint points[maxn];

double distance(const tpoint a, const tpoint b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

double closest_pair(int L, int R) {
  double ret = 1e20;
  if (L >= R) return ret;

  int mid = (L + R) >> 1;
  ret = min(ret, closest_pair(L, mid));
  ret = min(ret, closest_pair(mid+1, R));

  vector<tpoint> A, B;
  for (int i = L; i <= mid; ++i) {
    if (points[mid].x-points[i].x <= ret+EPS) {
      A.push_back(points[i]);
    }
  }
  for (int j = mid+1; j <= R; ++j) {
    if (points[j].x-points[mid+1].x <= ret+EPS) {
      B.push_back(points[j]);
    }
  }
  sort(A.begin(), A.end(), [](const tpoint &a, const tpoint &b){ return a.y < b.y; });
  sort(B.begin(), B.end(), [](const tpoint &a, const tpoint &b){ return a.y < b.y; });

  for (int i = 0, j = 0; i < A.size(); ++i) {
    while (j < B.size() && A[i].y-B[j].y > ret+EPS) ++j;
    for (int k = 0; k < 8 && j+k < B.size(); ++k) {
      ret = min(ret, distance(A[i], B[j+k]));
    }
  }

  return ret;
}


int main(int argc, char *argv[]) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d %d %d", &planets[i].R, &planets[i].theta, &planets[i].T);
  }

  for (int i = 0; i < N; ++i) {
    points[i].x = planets[i].R * cos(planets[i].theta * M_PI / 180000.0);
    points[i].y = planets[i].R * sin(planets[i].theta * M_PI / 180000.0);
  }

  sort(points, points+N, [](const tpoint &a, const tpoint &b){ return a.x < b.x; });

  double ans = closest_pair(0, N-1);

  sort(planets, planets+N, [](const tplanet &a, const tplanet &b){ return a.R < b.R; });

  for (int i = 0; i+1 < N; ++i) {
    if (planets[i].T == planets[i+1].T) continue;
    ans = min(ans, (double)planets[i+1].R-planets[i].R);
  }

  printf("%.9lf\n", ans);

  return 0;
}
