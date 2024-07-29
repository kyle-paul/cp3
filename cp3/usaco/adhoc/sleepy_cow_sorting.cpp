#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    // freopen("sleep.in", "r", stdin);
    // freopen("sleep.out", "w", stdout);
    #endif 
}

int n;

int find_first_true(vector<int> &a) {
    int i = (int)a.size() - 1;
    while(i > 0 && a[i-1] < a[i]) {
        i--;
    }
    return i;
}

void update_index(vector<int> &index) {
    for (auto &x:index) {
        x+= 1;
    }
}

bool check_sorted(vector <int> &a, vector<int> &index) {
    for (int i=0; i<n-1; i++) {
        if (a[index[i+1]] < a[index[i]]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    
    cin >> n;
    vector<int> a(n, 0);
    vector<int> index(n, 0);
    vector<bool> sorted(n, 0);
    for (int i=0; i<n; i++) {
        cin >> a[i];
        index[i] = i;
    }
    sorted[n-1] = true;

    int first_true = find_first_true(a);
    
    int i=0;
    while (!check_sorted(a, index)) {
        int j = first_true;
        while(a[i] > a[j]) j++;
        a.push_back(0);
        for (int k=(int)a.size()-1; k>j; k--) {
            a[k] = a[k-1];
        }
        a[j] = a[i];
        i++;
        update_index(index);
    }
    cout << i;
}

/*

f f f f t t t t t
1 4 2 5 1 2 3 4 5
0 1 2 3 4 5 6 7 8

index
0 1 2 3 4
1 2 3 4 5
4 5 6 7 8


j = 4 -> first_true = j = 4
j = 6 -> 

O(n x (n-k))

Tư tưởng:

- Với số đầu tiên ta cần đưa số space k thì ta sẽ muốn số này nằm trên (n-k) đoạn đã được sorted
  và số đầu của (n-k) số sorted phải > số mà ta muốn đưa xuống
- 

1 2 4 3

step 1
2 4 1 3

step 2
4 1 2 3

step 3
1 2 3 4


1 4 2 5 3

step 1
4 2 5 1 3

step 2
2 5 1 3 4

step 3
5 1 2 3 4

step 4
1 2 3 4 5


5 1 2 4 3

step 1
1 2 4 3 5

step 2
2 4 1 3 5

step 3
4 1 2 3 5

step 4
1 2 3 4 5

*/