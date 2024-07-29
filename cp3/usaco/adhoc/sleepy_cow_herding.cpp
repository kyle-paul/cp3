#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    // freopen("herding.in", "r", stdin);
    // freopen("herding.out", "w", stdout);
    #endif 
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    
    vector<long long> cows(3,0);
    for (int i=0; i<3; i++) {
        cin >> cows[i];
    }

    if (cows[1] - cows[0] == 1 && cows[2] - cows[1] == 1) {
        cout << "0" << endl << "0";
        return 0;
    }

    if (cows[1] - cows[0] == 2 || cows[2] - cows[1] == 2) {
        cout << "1" << endl;
        cout << max(cows[1] - cows[0] - 1, cows[2] - cows[1] - 1);
    } 
    else {
        cout << "2" << endl;
        cout << max(cows[1] - cows[0] - 1, cows[2] - cows[1] - 1);
    }
}

/*
1 6 11

1 2 3 4 5 6 7 8 9 10 11
1 1 0 0 0 1 0 0 0 0  0

th1: liền kề nhau

min -> {1,2}

th1: 1 0 1 -> distance = 2
th2: luôn có min = 2

*/