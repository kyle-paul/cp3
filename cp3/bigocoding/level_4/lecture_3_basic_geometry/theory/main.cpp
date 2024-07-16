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

struct Line {
    double a, b, c;
    Point A, B;
    Line(double a, double b, double c) : a(a), b(b), c(c) {}
    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    Line(Point P, double k) {
        a = -k;
        b = 1;
        c = k * P.x - P.y;
    }

    double f(Point A) {
        return a * A.x + b * A.y + c;
    }
};

bool areParallel(Line l1, Line l2) {
    return compare(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1, l2) 
    && compare(l1.b * l2.c, l1.c * l2.b)
    && compare(l1.a * l2.c, l1.c * l2.a);
}

bool areIntersect(Line l1, Line l2, Point& p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b * l2.c - l1.c * l2.b;
    double dy = l1.c * l2.a - l2.c * l1.a;
    double d = l1.a * l2.b - l2.a * l1.b;
    p = Point(dx / d, dy / d);
    return true;
}

double distToLine(Point p, Point a, Point b, Point& c) {
    Point ap = p - a, ab = b - a;
    double k = ap.dot(ab) / ab.norm();
    c = a + (ab * k);
    return (p - c).len();
}

struct Circle : Point{
    double r;

    Circle(double x=0, double y=0, double r=0) : Point(x,y), r(r) {}
    Circle(Point p, double r) : Point(p), r(r) {}
    bool contains(Point p) {
        return Point(*this - p).len() <= r + EPS;
    }
};


int main()
{
    init();
    int x,y,r;
    cin >> x >> y >> r;
    Circle circle(x, y, r);
    Point p(2, 3);
    cout << circle.contains(p);
}