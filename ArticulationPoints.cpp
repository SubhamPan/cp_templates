// https://codeforces.com/contest/1949/submission/253101104

class ArticulationPoints {
public:
    int n; // number of nodes
    vector<vector<int>> adj; // adjacency list of graph
 
    vector<bool> visited;
    vector<int> tin, low;
    int timer;
 
    set <pii> cutpoints;
    set <pii> not_cutpoints;
 
    ArticulationPoints() {
        recalculate();
    }
 
    void recalculate() {
        n = r * c;
        adj.resize(n);
        cutpoints.clear();
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(init[i][j] != '*') continue;
                not_cutpoints.insert({i, j});
                for(int k = 0; k < 4; k++) {
                    int x = i + dir[k][0];
                    int y = j + dir[k][1];
                    if(in_bounds(x, y) && init[x][y] == '*') {
                        adj[i * c + j].push_back(x * c + y);
                    }
                }
            }
        }
        find_cutpoints();
    }
 
    void IS_CUTPOINT(int node) {
        int x = node / c;
        int y = node % c;
        cutpoints.insert({x, y});
        not_cutpoints.erase({x, y});
    }
 
    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        int children=0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p!=-1)
                    IS_CUTPOINT(v);
                ++children;
            }
        }
        if(p == -1 && children > 1)
            IS_CUTPOINT(v);
    }
 
    void find_cutpoints() {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs (i);
        }
    }
};
