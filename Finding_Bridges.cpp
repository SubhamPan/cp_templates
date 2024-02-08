// Shadow IITB orz.

vector<pair<int, int>> find_bridges(vector<vector<pair<int, int>>> &adj) {
    // adj is a zero-based indexed graph (undir / dir). It stores wt in the (.second) term.
    int n = adj.size();
    vector<bool> vis(n, false);
    
    vector<int> tin(n, -1);
    vector<int> low(n, -1);
 
    int timer = 0;
    vector<pair<int, int>> bridges;
 
    function<void(int, int)> dfs = [&](int v, int par) {
        vis[v] = true;
        tin[v] = low[v] = timer;
        timer++;
        for(auto [x, wt] : adj[v]) {
            if(x == par) continue;
            if(vis[x] == true) {
                    // ofc cant be a bridge; you got to the same node in 2 different ways (or more).
                    // just check if low[v] can be further reduced using low[x] and get the fk out
                    low[v] = min(low[v], low[x]);
 
            } else {
 
                    dfs(x, v);
                    // v: oh you have come back to me, showme ur low and lemme see if its of any use to me
                    low[v] = min(low[v], low[x]);
 
                    // now hmmm, can v -- x edge be a bridge?
                    if(low[x] <= tin[v]) {
                            // if the low[] of next node is less than the one which calls dfs for it, 
                            // then there is a other node through which that node can be reached,
                            // and which appeared before the one which calls the dfs.
 
                            // not a bridge
 
                    } else {
                            // low[x] > tin[v]
                            // it is a bridge.
                            bridges.push_back({v, x});
 
                    }
 
            }
        }
    };
 
    for(int i = 0; i < n; i++) {
        if(vis[i] == false) {
            dfs(i, -1);
        }
    }
    return bridges;
}
