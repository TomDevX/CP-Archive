#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>

#define all(x) x.begin(), x.end()

struct Point {
    int x, y;
};

using namespace std;

bool ccw(Point A, Point B, Point C) {
    return 1LL*(B.x - A.x)*(C.y - A.y) - 1LL*(B.y - A.y)*(C.x - A.x) >= 0;
}

bool cmp(Point &A, Point &B){
    if(A.x == B.x) return A.y < B.y;
    return A.x < B.x;
}
vector<Point> convex_hull_standard_ccw(vector<Point>& a, int n) {
    if(n <= 2) return a;
    
    vector<Point> hull;

    for(int i = 0; i < n; i++) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), a[i])) {
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }

    int lower_hull_size = hull.size();
    for(int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_hull_size && ccw(hull[hull.size() - 2], hull.back(), a[i])) {
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }

    hull.pop_back();
    return hull;
}

bool cmp2(Point &A, Point &B){
    return A.x == B.x && A.y == B.y;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("CONVEXHULL.INP", "r", stdin);
    freopen("CONVEXHULL.OUT", "w", stdout);

    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(all(a),cmp);

    vector<Point> hull = convex_hull_standard_ccw(a, n);
    int m = hull.size();

    cout << m << '\n';

    long double s = 0;
    if(m >= 3) {
        for (int i = 0; i < m; i++) {
            s += 1LL*hull[i].x * hull[(i + 1) % m].y - 1LL*hull[(i + 1) % m].x * hull[i].y;
        }
    }
    cout << fixed << setprecision(1) << abs(s/2.0) << '\n';

    int d = 0;
    for (int i = 1; i < m; ++i) {
        if (hull[i].y < hull[d].y || (hull[i].y == hull[d].y && hull[i].x < hull[d].x)) {
            d = i;
        }
    }

    for(int i = d; i >= 0; i--){
        cout << hull[i].x << ' ' << hull[i].y << '\n';
    }
    for(int i = m-1; i > d; --i){
        cout << hull[i].x << ' ' << hull[i].y << '\n';
    }
}