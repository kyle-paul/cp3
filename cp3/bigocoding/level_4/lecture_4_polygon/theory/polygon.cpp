#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    #endif 
}

const double EPS = 1e-9;

int compare(double x, double y){
    return (x < y - EPS) ? - 1 : (x > y + EPS);
}

struct Point {
    double x, y;
    Point(double _x=0, double _y=0) : x(_x), y(_y) {}
    int compare(const Point& p) const {
        if (x != p.x) return ::compare(x, p.x);
        return ::compare(y, p.y);
    }

    #define op(x) bool operator x (const Point& p) const { return compare(p) x 0; }
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


using Polygon = vector<Point>;

double singedArea(const Polygon& polygon) {
    double area = 0;
    for (int j, i=0; i < polygon.size(); i++) {
        j = (i + 1) % polygon.size();
        area += polygon[i].cross(polygon[j]);
    }

    return area / 2.0;
}

double area(const Polygon& polygon) {
    return fabs(singedArea(polygon));
}

int ccw(Point a, Point b, Point c) {
    return compare((b-a).cross(c-a), 0);
}

int isConvex(const Polygon& polygon) {
    int sz = polygon.size();
    if (sz < 3) return false;
    int turn = ccw(polygon[0], polygon[1], polygon[2]);
    for (int i=1; i < sz; i++) {
        if (ccw(polygon[i], polygon[(i+1) % sz] , polygon[(i+2) % sz]) * turn < 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    init();
}