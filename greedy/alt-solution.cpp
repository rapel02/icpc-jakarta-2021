#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MAX_VAL = 100000;
const int INF = 1e9;
const int NO_CHANGE = -INF;

struct node {
    int minVal;
    int mins;

    int lazySet;
    int lazyAdd;

    node() {
        minVal = mins = 0;
        lazySet = NO_CHANGE;
        lazyAdd = NO_CHANGE;
    }

    void addLazy(int x) {
        if (lazySet != NO_CHANGE) {
            lazySet += x;
        } else {
            if (lazyAdd == NO_CHANGE) lazyAdd = x;
            else lazyAdd += x;
        }

        mins += x;
    }

    void setLazy(int x) {
        lazyAdd = NO_CHANGE;
        lazySet = x;
        mins = minVal + x;
    }

    node operator +(node other) const {
        node ret;
        ret.lazySet = ret.lazyAdd = NO_CHANGE;
        ret.minVal = min(minVal, other.minVal);
        ret.mins = min(mins, other.mins);
        return ret;
    }
};

int n;
long long m;
int w[N];
int v[N];

node stree[4 * N];

void read() {
    scanf("%d %lld", &n, &m);
    for (int i = 1 ; i <= n ; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 1 ; i <= n ; i++) {
        scanf("%d", &v[i]);
    }
}

void init(int id, int l, int r) {
    if (l == r) {
        stree[id].minVal = w[l];
        stree[id].mins = w[l];
        stree[id].lazyAdd = stree[id].lazySet = NO_CHANGE;
    } else {
        int mid = (l + r) / 2;
        int chld = id << 1;
        init(chld, l, mid);
        init(chld+1, mid+1, r);
        stree[id] = stree[chld] + stree[chld+1];
    }
}

void propagate(int id) {
    int chld = id << 1;
    for (int i = 0 ; i < 2 ; i++) {
        if (stree[id].lazySet != NO_CHANGE) {
            stree[chld+i].setLazy(stree[id].lazySet);
        } else if (stree[id].lazyAdd != NO_CHANGE) {
            stree[chld+i].addLazy(stree[id].lazyAdd);
        }
    }

    stree[id].lazyAdd = NO_CHANGE;
    stree[id].lazySet = NO_CHANGE;
}

void updateSet(int id, int l, int r, int x, int y, int val) {
    if (x <= l && r <= y) {
        stree[id].setLazy(val);
    } else {
        int mid = (l + r) / 2;
        int chld = id << 1;

        propagate(id);
        if (x <= mid)   updateSet(chld, l, mid, x, y, val);
        if (y > mid)    updateSet(chld+1, mid+1, r, x, y, val);
        stree[id] = stree[chld] + stree[chld+1];
    }
}

int getLowest(int id, int l, int r) {
    if (l == r) {
        return l;
    }

    int mid = (l + r) / 2;
    int chld = id << 1;

    propagate(id);
    if (stree[id].mins == stree[chld].mins) {
        return getLowest(chld, l, mid);
    }
    return getLowest(chld+1, mid+1, r);
}

long long work() {
    init(1, 1, n);
    vector<int> taken;
    long long total = 0;

    long long start = max(0ll, m - MAX_VAL);
    long long left = start;
    for (int i = 1 ; i <= n ; i++) {
        if (left >= w[i]) {
            taken.push_back(i);
            total += v[i];
            left -= w[i];
            updateSet(1, 1, n, i, i, INF);
        } else {
            updateSet(1, 1, n, i, i, -left);
        }
    }

    long long ret = total;
    for (long long i = start+1 ; i <= m ; i++) {
        stree[1].addLazy(-1);
        if (stree[1].mins > 0) {
            continue;
        }

        int newIdx = getLowest(1, 1, n);
        updateSet(1, 1, n, newIdx, newIdx, INF);
        if (newIdx < n) {
            updateSet(1, 1, n, newIdx+1, n, 0);
        }

        {
            while(!taken.empty() && taken.back() > newIdx) {
                total -= v[taken.back()];
                taken.pop_back();
            }
            taken.push_back(newIdx);
            total += v[newIdx];
        }

        // printf("i %lld newIdx %d:", i, newIdx);
        // for (int x : taken) printf(" %d", x);
        // puts("");

        ret = max(ret, total);
    }

    return ret;
}

int main() {
    read();
    long long ret = work();
    printf("%lld\n", ret);
    return 0;
}
