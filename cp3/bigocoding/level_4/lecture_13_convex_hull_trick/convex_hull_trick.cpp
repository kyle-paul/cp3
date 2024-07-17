#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    #endif 
}

struct Line {
    double a, b;
    Line(double a=0, double b=0) : a(a), b(b) {}

    bool operator < (const Line& line) const {
        if (a != line.a) return a < line.a;
        return b > line.b;
    }

    double intersectX(const Line& line) const {
        return (line.b - b) / (a - line.a);
    }

    double eval(double x) const {
        return a*x + b;
    }
};

vector<Line> buildConvex(const vector<Line>& lines){
    vector<Line> res;
    int n = 0;
    for (int i=0; i < lines.size(); i++) {
        while (res.size() >= 2 && 
               res[n-2].intersectX(res[n-1]) >= res[n-1].intersectX(res[i])) 
        {
            res.pop_back();
            n--;
        }
        res.push_back(lines[i]);
        n++;
    }
    return res;
}

double query(const vector<Line>& lines, double x) {
    int left = 0;
    int right = lines.size() - 1;
    double res = lines[right].eval(x);

    while (left < right) {
        int mid = (left + right) / 2;
        double intersect = lines[mid].intersectX(lines[mid+1]);
        if (x <= intersect) {
            res = lines[mid].eval(x);
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return res;
}

int main() {
    init();
    int n, q;
    cin >> n >> q;
    vector<Line> lines(n);
    for (int i=0; i < n; i++) {
        cin >> lines[i].a >> lines[i].b;
    }
    sort(lines.begin(), lines.end());
    lines = buildConvex(lines);

    double x;
    for (int i=0; i < q; i++) {
        cin >> x;
        cout << query(lines, x) << endl;
    }
}


/*
input
5 3
0.5 1
0 2 
-0.5 2
-1.25 0
0.1 -0.5
-3
-1
4

output
3.75
2.5
3
*/