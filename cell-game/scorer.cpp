#include <bits/stdc++.h>
using namespace std;

constexpr int kNumColor = 26;
constexpr char kStartColor = 'z' - kNumColor + 1;
constexpr int kUnassignedParity = -1;

int ac() {
  puts("AC");
  return 0;
}

int wa(string message) {
  fprintf(stderr, "%s\n", message.c_str());
  puts("WA");
  return 0;
}

int main(int argc, char *argv[])
{
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "r");  // Judge's
  FILE *con = fopen(argv[3], "r");

  int R, C;
  fscanf(in, "%d %d", &R, &C);
  vector<int> cnt(kNumColor, 0);
  for (int i = 0; i < R; ++i) {
    fscanf(in, "\n");
    for (int j = 0; j < C; ++j) {
      char c;
      fscanf(in, "%c", &c);
      if (c != '.') {
        ++cnt[c - kStartColor];
      } 
    }
  }

  int R_judge, C_judge, R_con, C_con;
  fscanf(out, "%d %d", &R_judge, &C_judge);
  if (fscanf(con, "%d %d", &R_con, &C_con) != 2) {
    return wa("Unexpected EOF.");
  }

  if (static_cast<long long>(R_judge) * C_judge !=
      static_cast<long long>(R_con) * C_con) {
    return wa("Contestant's board size differs with judge's board size.");
  }

  vector<int> parities(kNumColor, kUnassignedParity);
  for (int i = 0; i < R_con; ++i) {
    fscanf(con, "\n");
    for (int j = 0; j < C_con; ++j) {
      char c;
      if (fscanf(con, "%c", &c) != 1) {
        return wa("Unexpected EOF.");
      }
      c = std::tolower(c);
      if (c != '.') {
        if (kStartColor <= c && c < kStartColor + kNumColor) {
          int current_parity = (i + j) & 1;
          int &parity = parities[c - kStartColor];
          if (parity != kUnassignedParity && parity != current_parity) {
            return wa("Parity of a color differs among pieces.");
          }
          parity = current_parity;
          --cnt[c - kStartColor];
          if (cnt[c - kStartColor] < 0) {
            return wa("A color appears more than the input occurences");
          }
        } else {
          return wa("Invalid character.");
        }
      }
    }
  }

  if (any_of(cnt.begin(), cnt.end(), [] (int x) { return x > 0; })) {
    return wa("A color appears less than the input occurences");
  }

  fscanf(con, "\n");
  char dummy;
  if (fscanf(con, "%c", &dummy) == 1) {
    return wa("Expected EOF.");
  }

  return ac();
}
