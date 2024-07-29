#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    #endif 
}

/*
test case 1:
5 10
3 1
2 5
6 3
2 3
5 7

5 7
2 3
2 5
Total weight: 9
Total profit: 15

test case 2:
4 12
5 7
3 3
6 2
4 1

4 1
3 3
5 7
Total weight: 12
Total profit: 11
*/

int n, w;
vector<int> weight;
vector<int> profit;
vector<vector<int>> dp;

void knapsack() {
    for (int j = 0; j <= w; j++) {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= w; j++){
            dp[i][j] = dp[i - 1][j]; // do not take item i
            if (j >= weight[i - 1] && dp[i][j] < dp[i - 1][j - weight[i - 1]] + profit[i - 1]) {
                dp[i][j] = dp[i - 1][j - weight[i - 1]] + profit[i - 1];
            }
        }
    }
}

void trace(){
    int total_weight = 0, total_profit = 0;
    int current_n = n, current_w = w; // Use temporary variables to preserve n and w
    while (current_n > 0 && current_w > 0) {
        if (weight[current_n - 1] <= current_w && dp[current_n][current_w] == dp[current_n - 1][current_w - weight[current_n - 1]] + profit[current_n - 1]) {
            cout << weight[current_n - 1] << " " << profit[current_n - 1] << endl;
            total_weight += weight[current_n - 1];
            total_profit += profit[current_n - 1];
            current_w -= weight[current_n - 1];
        }
        current_n--;
    }
    cout << "Total weight: " << total_weight << endl;
    cout << "Total profit: " << total_profit << endl;
}   

int main() {
    init();
    cin >> n >> w;
    weight.resize(n);
    profit.resize(n);
    dp.assign(n + 1, vector<int>(w + 1, 0));

    for (int i = 0; i < n; i++){
        cin >> weight[i] >> profit[i];
    }

    knapsack();
    trace();
}
