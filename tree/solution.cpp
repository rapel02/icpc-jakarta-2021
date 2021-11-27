#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N;
    scanf("%d", &N);

    vector<vector<int>> adj(N);
    for (int i = 1; i < N; ++i) {
        int P;
        scanf("%d", &P);
        adj[--P].push_back(i);
    }

    vector<int> C(N);
    for (int i = 0; i < N; ++i) scanf("%d", &C[i]);

    vector<int> heights(N);
    for (int u = N - 1; u >= 0; --u) {
        for (int v : adj[u]) {
            heights[u] = max(heights[u], heights[v] + 1);
        }
    }

    vector<int> parities(N);
    for (int u = 0; u < N; ++u) {
        if (C[u]) {
            parities[heights[u]] ^= 1;
        }
    }

    if (any_of(parities.begin(), parities.end(), [](int p) { return p; })) {
        printf("First\n");
    } else {
        printf("Second\n");
    }
}

int main() {
    solve();
    return 0;
}
