#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int N       = 2e5;
const ll MIN_INT = -1e18;

struct node {
    ll val;
    node *left, *right;
};

node *ST[4 * N + 5];

int _k, _d;
int bn;
ll offset;
int happiness[N + 5];
int t[N + 5];

node *make_node() {
    node *cur = new node();
    cur->left = cur->right = nullptr;
    cur->val               = MIN_INT;
    return cur;
}

node *build2D(node *cur, int l, int r) {
    cur = make_node();
    if (l == r) return cur;
    int mid    = (l + r) / 2;
    cur->left  = build2D(cur->left, l, mid);
    cur->right = build2D(cur->right, mid + 1, r);
    return cur;
}

void build(int idx, int l, int r) {
    ST[idx] = build2D(ST[idx], 0, _k - 1);
    if (l == r) return;
    int mid = (l + r) / 2;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
}

void setValue2D(node *cur, int l, int r, int tar, ll val) {
    if (l == r) {
        cur->val = max(cur->val, val);
        return;
    }
    int mid = (l + r) / 2;
    if (tar <= mid)
        setValue2D(cur->left, l, mid, tar, val);
    else
        setValue2D(cur->right, mid + 1, r, tar, val);
    cur->val = max(cur->left->val, cur->right->val);
    return;
}

void setValue(int idx, int l, int r, int tar_x, int tar_y, int val) {
    setValue2D(ST[idx], 0, _k - 1, tar_y, val);
    if (l == r) return;
    int mid = (l + r) / 2;
    if (tar_x <= mid)
        setValue(2 * idx, l, mid, tar_x, tar_y, val);
    else
        setValue(2 * idx + 1, mid + 1, r, tar_x, tar_y, val);
}

ll query2D(node *cur, int l, int r, int xl, int xr) {
    if (r < xl || xr < l) return MIN_INT;
    if (xl <= l && r <= xr) return cur->val;
    int mid = (l + r) / 2;
    return max(query2D(cur->left, l, mid, xl, xr), query2D(cur->right, mid + 1, r, xl, xr));
}

ll query(int idx, int l, int r, int xl, int xr, int yl, int yr) {
    if (r < xl || xr < l || xl > xr || yl > yr) return MIN_INT;
    if (xl <= l && r <= xr) return query2D(ST[idx], 0, _k - 1, yl, yr);
    int mid = (l + r) / 2;
    return max(query(2 * idx, l, mid, xl, xr, yl, yr),
               query(2 * idx + 1, mid + 1, r, xl, xr, yl, yr));
}

ll querySquare(int l, int t) {
    ll res = MIN_INT;
    int r  = l + t;

    int pl = (l + _k) / _k * _k;
    pl--;
    if (pl > r) pl = r;
    // query first column
    res = query(1, 0, bn, l / _k, pl / _k, l % _k, pl % _k) - offset;

    if (pl != r) {
        int pr = r / _k * _k;
        // query last column
        if(r % _k >= l % _k) {
            ll rl = query(1, 0, bn, pr / _k, r / _k, 0, l % _k - 1) - offset + _d;
            ll rr = query(1, 0, bn, pr / _k, r / _k, l % _k, r % _k) - offset;
            res   = max(res, max(rl, rr));
        } else {
            ll rl = query(1, 0, bn, pr / _k, r / _k, 0, r % _k) - offset + _d;
            res = max(res, rl);
        }
        pr--;
        pl++;
        if (pl <= pr) {
            // query rectangle
            ll rl = query(1, 0, bn, pl / _k, pr / _k, 0, l % _k - 1) - offset + _d;
            ll rr = query(1, 0, bn, pl / _k, pr / _k, l % _k, _k - 1) - offset;
            res   = max(res, max(rl, rr));
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n, k, d;
    cin >> n >> k >> d;
    _k = k;
    _d = d;
    for (int i = 0; i < n; i++) cin >> happiness[i];
    for (int i = 0; i < n - 1; i++) cin >> t[i];

    int new_n = n;
    while (new_n % k != 0) new_n++;

    bn = new_n / k - 1;

    build(1, 0, bn);

    offset = 0;
    setValue(1, 0, bn, (n - 1) / k, (n - 1) % k, happiness[n - 1] + offset);
    if ((n - 1) % k == 0) offset += d;

    ll res;
    for (int i = n - 2; i >= 0; i--) {
        res = querySquare(i, t[i]) + happiness[i];
        setValue(1, 0, bn, i / k, i % k, res + offset);
        if (i % k == 0) offset += d;
    }
    cout << res << endl;
}
