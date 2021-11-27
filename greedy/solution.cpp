#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MAX_VAL = 100000;

int n;
long long m;
int w[N];
int v[N];


void read() {
    scanf("%d %lld", &n, &m);
    for (int i = 1 ; i <= n ; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 1 ; i <= n ; i++) {
        scanf("%d", &v[i]);
    }
}

long long work() {
    priority_queue<pair<long long, pair<int, long long>>> pq;
    int initLength = min(m, MAX_VAL * 1ll);
    pq.push({m, {initLength, 0}});

    long long ret = 0;
    for (int i = 1 ; i <= n ; i++) {
        vector<pair<long long, pair<int, long long>>> upd;

        while (!pq.empty() && pq.top().first >= w[i]) {
            auto cur = pq.top();
            pq.pop();

            long long nval = cur.second.second + v[i];
            ret = max(ret, nval);

            long long en = cur.first;
            int len = cur.second.first;
            long long st = en - len + 1;

            if (st > w[i]) {
                upd.push_back({en-w[i], {len, nval}});
            } else {
                // split
                if (en > w[i]) {
                    upd.push_back({en-w[i], {en-w[i], nval}});
                }
                if (st < w[i]) {
                    upd.push_back({w[i]-1, {w[i]-st, cur.second.second}});
                }
            }
        }

        for (auto x : upd) {
            pq.push(x);
        }
    }

    return ret;
}

int main() {
    read();
    long long ret = work();
    printf("%lld\n", ret);
    return 0;
}
