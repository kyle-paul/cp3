#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    #endif 
}

const double EPS = 1e-9;

int cmp(double x, double y){
    return (x < y - EPS) ? - 1 : (x > y + EPS);
}

struct Point {
    double x, y;
    Point(double _x=0, double _y=0) : x(_x), y(_y) {}
    int cmp(const Point& p) const {
        if (x != p.x) return ::cmp(x, p.x);
        return ::cmp(y, p.y);
    }

    #define op(x) bool operator x (const Point& p) const { return cmp(p) x 0; }
    op(>) op(<) op(==) op(>=) op(<=) op(!=)
    #undef op

    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    Point operator*(double k) const {
        return Point(x*k, y*k);
    }

    Point operator/(double k) const {
        return Point(x/k, y/k);
    }

    double dot(const Point& p) const {
        return x * p.x + y * p.y;
    }

    double cross(const Point& p) const {
        return x * p.y - y * p.x;
    }

    double norm() {
        return x*x + y*y;
    }

    double len() {
        return sqrt(norm());
    }

    Point rotate(double alpha) {
        double cosA = cos(alpha), sinA = sin(alpha);
        return Point(x*cosA - y*sinA, x*sinA + y*cosA);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a).cross(c-a), 0);
}

Point pivot;
using Points = vector<Point>; 

bool compare(const Point& p, const Point& q) {
    int temp = ccw(pivot, p, q);
    if (temp > 0) return true;
    return (temp == 0 && (p - pivot).norm() < (q - pivot).norm());
}

// Graham's scan
void convexHull(Points& points) {
    pivot = points[0];
    for (int i=1; i < points.size(); i++){
        if (pivot.y > points[i].y || (pivot.y == points[i].y && pivot.x > points[i].x)) {
            pivot = points[i];
        }
    }
    sort(points.begin(), points.end(), compare);
    if (points.size() < 3) return;

    int n=0;
    for (int i=0; i < points.size(); i++) {
        while (n > 1 && ccw(points[n-2], points[n-1], points[i]) <= 0) n--;
        points[n++] = points[i];
    }
    points.resize(n);
}

int main() {
    init();
    int n; cin >> n;
    Points points(n);
    for (int i=0; i<n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    convexHull(points);
    for (auto point : points) {
        cout << point.x << " " << point.y << endl;
    }
}


/*
input
10
2 1
5 1
9 2
8 4
4 6
6 3
4 3
5 4
2 5
1 3

output
2 1
5 1
9 2
8 4
4 6
2 5
1 3
*/
