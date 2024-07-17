#include <bits/stdc++.h>
using namespace std;

void init(){
    #ifndef ONLINE_JUDGE
    freopen("D:/Documents/Cpp/cp3/io/input.txt", "r", stdin);
    freopen("D:/Documents/Cpp/cp3/io/output.txt", "w", stdout);
    #endif 
}

typedef pair<int, int> pii;
int n, m, s, t;
vector<int> parent;

int bfs(int s, int t) {
    parent.assign(n, -1);
    parent[s] = -2;
    queue<pii> q;

    q.push({s, INF});
    while(!q.empty()) {
        int u = q.front().first;
        int f = q.front().second;
        q.pop();

        for (int v:graph[u]) {
            if (parent[v] == -1 && cap[u][v] > flow[u][v]) {
                int newFlow = min(f, cap[u][v] - flow[u][v]);
                if (v == t) return newFlow;
                q.push({v, newFlow});
            }
        }
    }
    return 0;
}

int edmondsKarp(vector<vector<int>>& graph, int s, int t) {
    int newFlow, sumFlow = 0;
    int cnt = 0;
    while(true) {
        newFlow = BFS(s,t);
        if (newFlow == 0) break;
        sumFlow += newFlow;

        int prev, cur = t;
        while (cur != s) {
            prev = parent[cur];
            flow[prev][cur] += newFlow;
            flow[cur][prev] -= newFlow;
            cur = prev;
        }
    }
    return sumFlow;
}


int main() {
    init();
    cin >> n >> m >> s >> t;
    vector<vector<int>> graph(n, vector<int>());
    vector<vector<int>> cap(n, vector<int>(n, 0));

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        cap[u][v] = w;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << edmondsKarp(graph, s, t);
}

/*
6 8 1 6
1 2 7
1 3 10
2 4 15
2 5 5
3 4 5
3 5 2
4 6 9
5 6 7
*/