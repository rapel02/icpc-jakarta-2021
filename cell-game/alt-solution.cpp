#include <bits/stdc++.h>
using namespace std;

constexpr int kNumColor = 26;
constexpr char kStartColor = 'z' - kNumColor + 1;

int main() {
  int R, C;
  scanf("%d %d", &R, &C);
  vector<int> cnt(kNumColor, 0);
  for (int i = 0; i < R; ++i) {
    scanf("\n");
    for (int j = 0; j < C; ++j) {
      char c;
      scanf("%c", &c);
      if (c != '.') {
        ++cnt[c - kStartColor];
      } 
    }
  }

  vector<pair<int, int>> need(R * C + 1, make_pair(INT_MAX, 0));
  function<void (int, int, int, int)> dfs = [&]
      (int color, int mask, int sum_zero, int sum_one) {
    if (color == kNumColor) {
      need[sum_zero] = min(need[sum_zero], make_pair(sum_one, mask));
      return;
    }
    dfs(color + 1, mask, sum_zero + cnt[color], sum_one);
    dfs(color + 1, mask | (1 << color), sum_zero, sum_one + cnt[color]);
  };
  dfs(0, 0, 0, 0);
  for (int i = 0; i < R * C; ++i) {
    need[i + 1] = min(need[i + 1], need[i]);
  }

  vector<pair<int, int>> possible_boards;
  for (int i = R; i <= 2 * R; ++i) {
    for (int j = C; i * j <= 2 * R * C; ++j) {
      possible_boards.push_back(make_pair(i, j));
    }
  }
  sort(possible_boards.begin(), possible_boards.end(), [] (auto a, auto b) {
    return a.first * a.second < b.first * b.second;
  });
  for (auto possible_board : possible_boards) {
    int r = possible_board.first;
    int c = possible_board.second;
    int less = (r * c) >> 1;
    int more = (r * c) - less;
    if (need[less].first <= more) {
      vector<pair<int, int>> less_cells, more_cells;
      for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
          if ((i + j) & 1) {
            less_cells.push_back(make_pair(i, j));
          } else {
            more_cells.push_back(make_pair(i, j));
          }
        }
      }
      assert(less_cells.size() == less && more_cells.size() == more);
      vector<string> answer(r, string(c, '.'));
      for (int i = 0; i < kNumColor; ++i) {
        if (need[less].second & (1 << i)) {
          for (int j = 0; j < cnt[i]; ++j) {
            answer[more_cells.back().first][more_cells.back().second] =
                i + kStartColor;
            more_cells.pop_back();
          }
        } else {
          for (int j = 0; j < cnt[i]; ++j) {
            answer[less_cells.back().first][less_cells.back().second] =
                i + kStartColor;
            less_cells.pop_back();
          }
        }
      }
      printf("%d %d\n", r, c);
      for (int i = 0; i < r; ++i) {
        printf("%s\n", answer[i].c_str());
      }
      return 0;
    }
  }
  assert(false);
}
