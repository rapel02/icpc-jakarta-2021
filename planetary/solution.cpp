#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const ll INF     = 1e18;
const double PI  = acos(-1);
const double EPS = 1e-10;

struct planet {
    ll r, t;
    int a;
};

struct point {
    double x, y;
};

vector<planet> planets;
vector<point> points;

double result = INF;

void upd_ans(point p, point q) {
    double dx = p.x - q.x;
    double dy = p.y - q.y;

    result = min(result, sqrt(dx * dx + dy * dy));
}

bool cmpy(const point &a, const point &b) { return a.y < b.y; }

vector<point> tmp;

void closest_pair(int l, int r) {
    if (r - l <= 10) {
        for (int i = l; i < r; i++) {
            for (int j = i + 1; j < r; j++) upd_ans(points[i], points[j]);
        }
        sort(points.begin() + l, points.begin() + r, cmpy);
        return;
    }
    int mid     = (l + r) / 2;
    double midx = points[mid].x;

    closest_pair(l, mid);
    closest_pair(mid, r);

    merge(points.begin() + l, points.begin() + mid, points.begin() + mid, points.begin() + r,
          tmp.begin(), cmpy);
    copy(tmp.begin(), tmp.begin() + r - l, points.begin() + l);

    int idx = 0;
    for (int i = l; i < r; ++i) {
        if (fabs(points[i].x - midx) < result) {
            for (int j = idx - 1; j >= 0 && points[i].y - tmp[j].y < result; j--)
                upd_ans(points[i], tmp[j]);
            tmp[idx++] = points[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.setf(ios::showpoint), cout.precision(10);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        planet p;
        cin >> p.r >> p.a >> p.t;
        planets.push_back(p);
    }
    sort(planets.begin(), planets.end(),
         [](const planet &l, const planet &r) { return l.r < r.r; });

    for (int i = 0; i < n - 1; i++) {
        if (planets[i].t == planets[i + 1].t) continue;
        result = min(result, 1.0 * (planets[i + 1].r - planets[i].r));
    }

    for (int i = 0; i < n; i++) {
        double deg = PI * planets[i].a / 1000.0 / 180.0;
        points.push_back({planets[i].r * cos(deg), planets[i].r * sin(deg)});
    }

    sort(points.begin(), points.end(), [](const point &A, const point &B) {
        if (A.x + EPS < B.x) return true;
        if (fabs(A.x - B.x) < EPS) {
            if (A.y + EPS < B.y) return true;
            return false;
        }
        return false;
    });

    tmp.resize(n);

    closest_pair(0, n);

    cout << result << endl;
}
