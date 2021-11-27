#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const ll N  = 2e5;
const int M = 18;
ll new_locations[2 * N + 5];

ll time_quarantine[2 * N + 5];

vector<int> spectators;

vector<pair<ll, ll>> intervals;

void construct_interval(int k, int n, ll length) {
    int l          = 0;
    int r          = 0;
    int last_valid = 0;
    for (int i = 0; i < k; i++) {
        while (new_locations[l] + length < new_locations[spectators[i]] || time_quarantine[l % n])
            l++;

        if (last_valid < new_locations[spectators[i]]) last_valid = spectators[i];
        if (r < spectators[i]) r = spectators[i];

        while (r != 2 * n && new_locations[spectators[i]] + length >= new_locations[r]) {
            if (time_quarantine[r % n] == 0) last_valid = r;
            r++;
        }

        ll left_loc  = new_locations[l];
        ll right_loc = new_locations[last_valid];
        intervals.push_back({left_loc, right_loc});
    }

    for (int i = 0; i < k; i++) {
        while (new_locations[l] + length < new_locations[spectators[i] + n] ||
               time_quarantine[l % n])
            l++;

        if (last_valid < new_locations[spectators[i] + n]) last_valid = spectators[i] + n;
        if (r < spectators[i] + n) r = spectators[i] + n;

        while (r != 2 * n && new_locations[spectators[i] + n] + length >= new_locations[r]) {
            if (time_quarantine[r % n] == 0) last_valid = r;
            r++;
        }

        ll left_loc  = new_locations[l];
        ll right_loc = new_locations[last_valid];
        intervals.push_back({left_loc, right_loc});
    }
}

int sparse[M + 1][2 * N + 5];

void build_sparse_table(int k) {
    int ptr = 0;
    for (int i = 0; i < 2 * k; i++) {
        while (ptr != 2 * k && intervals[ptr].first <= intervals[i].second) ptr++;
        sparse[0][i] = ptr;
    }
    sparse[0][2 * k] = 2 * k;

    for (int i = 1; i <= M; i++) {
        for (int j = 0; j <= 2 * k; j++) {
            sparse[i][j] = sparse[i - 1][sparse[i - 1][j]];
        }
    }
}

int traverse(int cur, int tar) {
    int st = cur;
    if (cur >= tar) return 0;
    int total = 0;
    for (int i = M; i >= 0; i--) {
        if (sparse[i][cur] >= tar) continue;
        cur = sparse[i][cur];
        total += (1 << i);
    }
    total++;
    cur = sparse[0][cur];
    if (cur < tar) {
        // this is impossible
        return -1;
    }
    return total;
}

int getMinInterval(int k) {
    int res = 2 * k;
    for (int i = 0; i < k; i++) {
        res = min(res, traverse(i, i + k));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m, k, p;
    cin >> n >> m >> k >> p;
    for (int i = 0; i < m; i++) {
        int loc;
        cin >> loc;
        loc--;
        cin >> time_quarantine[loc];
    }

    for (int i = 0; i < k; i++) {
        int spectator_location;
        cin >> spectator_location;
        spectator_location--;
        spectators.push_back(spectator_location);
    }
    sort(spectators.begin(), spectators.end());

    ll new_array_length = 0;
    for (int i = 0; i < n; i++) {
        new_array_length++;
        new_array_length += time_quarantine[i];
    }

    ll cur_location = 0;
    for (int i = 0, idx = 0; i < 2 * n; i++, idx++) {
        if (idx >= n) idx -= n;
        new_locations[i] = cur_location;
        cur_location++;
        cur_location += time_quarantine[idx];
    }

    ll low = 0;
    ll hi  = cur_location;
    ll res = 0;
    while (low <= hi) {
        ll mid = (low + hi) / 2;

        intervals.clear();
        construct_interval(k, n, mid);
        build_sparse_table(k);

        if (getMinInterval(k) > p)
            low = mid + 1;
        else {
            hi  = mid - 1;
            res = mid;
        }
    }
    cout << res << endl;
}
