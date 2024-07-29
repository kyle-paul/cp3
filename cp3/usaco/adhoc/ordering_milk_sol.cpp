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

int n, m, k;

// Kiểm tra có hợp lệ hay không
bool check(vector<int> &pos, vector<int> &hierarchy) {

    int i = 1; int j = 1;
    vector<int> cow_to_pos(n+1, 0);


    for (int i=1; i<=n; i++) {
        if (pos[i] != 0) {
            cow_to_pos[pos[i]] = i;
        }
    }

    while(i <= n && j <= m) {

        // Con bò có trùng
        if (cow_to_pos[hierarchy[j]] != 0) {

            // nếu mà i vượt quá vị trí cố định --> trước đó bị filled hết --> sai
            if (i > cow_to_pos[hierarchy[j]]) {
                return false;
            }

            // Cho i nhảy đến vị trí con bò bị trùng luôn
            i = cow_to_pos[hierarchy[j]];
            i++; j++;
        }
        // Con bò không có trùng
        else {
            while(i <= n && pos[i] != 0) {
                i++;
            }
            if (i == n) return false;
            cow_to_pos[hierarchy[j]] = i;
            i++; j++;
        }
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();

    cin >> n >> m >> k;
    vector<int> pos(n+1, 0);
    vector<int> hierarchy(m+1, 0);

    for (int i=1; i<=m; i++) {
        cin >> hierarchy[i];
    }

    // Xếp những con bò cố định vào
    int cow, position;
    for (int i=1; i<=k; i++) {
        cin >> cow >> position;
        pos[position] = cow;
    }

    // Xếp con bò 1 vào các vị trí trống
    for (int i=1; i<=n; i++) {
        if (pos[i] == 0) {
            pos[i] = 1;
            if (check(pos, hierarchy)){
                cout << i;
                return 0;
            }
            pos[i] = 0;
        }
    }
}


/*

Ý tưởng:
- Đầu tiên vẫn là xếp hết những con bò cố định vào
- Sau đó chỉ còn lại đúng một số chỗ trống nhất định cho i
    --> Ta sẽ cố gắng xếp con bò 1 vào các vị trí trống lần lượt đầu tiên
    --> Cứ mỗi lần xếp thì ta không biết hợp lệ hay không
    --> Ta cần check bằng việc xếp các con bò hierarchy còn lại
        --> Dùng hai con trỏ (đảm bảo hierarchy) --> sắp xếp lần lượt vào
        --> Điều kiện dừng --> con bò trùng bị lố vị trí 
                           --> không thể xếp đúng hierarchy 
*/