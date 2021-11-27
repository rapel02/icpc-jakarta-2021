#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int INF = 2e9;

vector<vector<int>> bit;

int n, k, d;
int h[N];
int t[N];

int dp[N];

void read() {
    scanf("%d %d %d", &n, &k, &d);
    for (int i = 0 ; i < n ; i++) {
        scanf("%d", &h[i]);
    }
    for (int i = 0 ; i+1 < n ; i++) {
        scanf("%d", &t[i]);
    }
}

void prepare() {
    bit.resize(n / k + 5);
    for (int i = 0 ; i < bit.size() ; i++) {
        bit[i].resize(k+5);
        for (int &x : bit[i]) {
            x = -INF;
        }
    }
}

void update(int r, int c, int v) {
    for (; r < bit.size() ; r += r & -r) {
        for (int cc = c ; cc < bit[r].size() ; cc += cc & -cc) {
            bit[r][cc] = max(bit[r][cc], v);
        }
    }
}

int query(int r, int c) {
    int ret = -INF;
    while (r > 0) {
        int cc = c;
        while (cc > 0) {
            ret = max(bit[r][cc], ret);
            cc -= cc & -cc;
        }
        r -= r & -r;
    }
    return ret;
}

pair<int, int> getPos(int x) {
    return {(x / k) + 1, (x % k) + 1};
}

int work() {
    {
        dp[n-1] = h[n-1];
        pair<int, int> pos = getPos(n-1);
        update(pos.first, pos.second, dp[n-1] - (n-1) / k * d);
    }

    for (int i = n-2 ; i >= 0 ; i--) {
        int en = i + t[i];
        pair<int, int> enPos = getPos(en);

        int ret = -INF;
        ret = max(ret, query(enPos.first, enPos.second));
        ret = max(ret, query(enPos.first-1, k));

        int lastRow = enPos.first;
        int lastCol = (i % k) + 1;
        if (lastCol > 1) {
            lastCol--;
            if (lastCol > enPos.second) {
                ret = max(ret, query(lastRow, enPos.second) + d);
                lastRow--;
            }
            ret = max(ret, query(lastRow, lastCol) + d);
        }

        dp[i] = ret + h[i] + i / k * d;
        // printf("i %d dp %d\n", i, dp[i]);
        pair<int, int> pos = getPos(i);
        update(pos.first, pos.second, dp[i] - i / k * d);
    }

    return dp[0];
}

int naive() {
    vector<int> dp(n+1);
    dp[n-1] = h[n-1];
    for (int i = n-2 ; i >= 0 ; i--) {
        dp[i] = -INF;
        for (int j = i+1 ; j <= i + t[i] ; j++) {
            dp[i] = max(dp[i], h[i] - (j - i) / k * d + dp[j]);
        }
        printf("naive dp i %d val %d\n", i, dp[i]);
    }
    return dp[0];
}

int main() {
    read();
    prepare();
    int ret = work();
    printf("%d\n", ret);
    // int naiv = naive();
    // printf("naive %d\n", naiv);
    return 0;
}
