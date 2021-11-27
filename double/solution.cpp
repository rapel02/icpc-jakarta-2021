#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);
  long double small = 1e100;
  long double large = -1e100;
  long double sum = 0;
  for (int i = 0; i < N; ++i) {
    long double a, b;
    scanf("%Lf %Lf", &a, &b);
    small = min(small, a / b);
    large = max(large, a / b);
    sum += a / b;
  }
  printf("%.11Lf %.11Lf %.11Lf\n", small, large, sum);
}
