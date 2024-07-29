#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    // freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    // freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);
    #endif 
}

struct DataTrung
{
    int value, index_res, index_m;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();


    int n, m, k;
    bool flag_mot_trong_m = false;
    bool flag_trung = false;
    cin >> n >> m >> k;
    vector<int>res(n+1,0);
    vector<int>vector_m;
    vector<pair<int, int>>vector_trung;
    vector<bool>in_m(101, false);
    vector<bool>in_k(101, false);
    vector<int> vector_index_m(101, 0);

    for (int i=0; i<m; i++) {
        int x; cin >> x;
        if (x == 1) flag_mot_trong_m = true;
        in_m[x] = true;
        vector_m.push_back(x);
        vector_index_m[x] = i;
    }

    // Nhập vào các ki
    for (int i=0; i<k; i++) {
        int u,v; cin >> u >> v;

        // Kiểm tra trường hợp 1
        if (u == 1) {
            cout << v;
            return 0;
        }
        // Sắp k vào dãy trước
        res[v] = u;

        // Kiểm tra m_i trùng k_i
        if (in_m[u]) {
            flag_trung=true;
            in_k[u] = true;
            vector_trung.push_back({u, v});
        }
    }

    int i=0;
    int j=0;

    // kiểm tra trường hợp 2 -> 1 có trong m
    if (flag_mot_trong_m) {

        // trường hợp m_i không trùng k_i
        if (!flag_trung) {
            int i = 0;
            for (int j=1; j<=n; j++) {
                if (res[j] == 0) {

                    // kiểm tra đã sắp đến 1 vào trống
                    if (vector_m[i] == 1) {
                        cout << j;
                        return 0;
                    }
                    res[j] = vector_m[i++];
                }
            }
        }

        // trường hợp m_i trùng k_i
        else {
            for (auto [value, index_res] : vector_trung) {

                int j = 0;
                for(int i=1; i<=n; i++) {
                    if (vector_m[j] == value) {
                        i=index_res; j++;
                    }
                    if (in_k[vector_m[j]] == true) {
                        j++;
                    }

                    if (res[i] == 0) {
                        if(!in_k[vector_m[j]]) {
                            res[i] = vector_m[j];
                        }
                        j++;

                        if (res[i] == 1) {
                            cout << i;
                            return 0;
                        }
                    }
                }
            }
        }
    }

    // kiểm tra trường hợp 3 -> 1 khon có trong m
    else {
        
        // trường hợp m_i không trùng k_i
        if (!flag_trung) {
            for (int i=1; i<=n; i++) {
                if (res[i] == 0) {
                    cout << i;
                    return 0;
                }
            }
        }
        
        // trường hợp m_i trùng k_i
        else {
            for (auto [value, index_res] : vector_trung) {
                int j = vector_index_m[value]; j--;

                // thực hiện lắp các thứ tự trước số trùng trong m vào res
                for (int i=index_res; i >= 1; i--) {
                    if (res[i] == 0 && in_k[vector_m[j]] == false) {
                        res[i] = vector_m[j--];
                        if (j < 0) break;
                    }
                }
            }
            for (int i=1; i<=n; i++){
                if (res[i] == 0){
                    cout << i; 
                    return 0;
                }
            }
        }
    }
    cout << 0;
    return 0;
}

/*
th1: 1 trong k -> cout 1
th2: 1 trong m 
    -> nếu k không trùng m
        -> sắp các biến cố định k vào trước
        -> còn lại các vị trí 0 --> sắp xếp dãy m vào với mong muốn luôn ở cao nhất có thể
    -> nếu k trùng m

th3: 1 không nằm trong k và m
    -> nếu k không trùng m
        -> sắp xếp các biến cố địnk vào k trước
        -> 1 sẽ là vị trí 0 đầu tiên vì sẽ luôn có thể sắp m chữ còn lại theo thứ tự
    -> nếu k trùng m
        -> sắp xếp các biến cố định k vào trước
        -> còn lại các vị trí 0 --> sắp xếp các biến tự do vào theo quy luật m
        và sắp xếp sao đó để chừa chỗ 
*/