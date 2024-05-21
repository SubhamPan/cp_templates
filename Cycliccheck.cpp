// shadow's version:
//This detects cycle in a ***directed graph***
bool isCyclic(vector<vector<int>> &adj){
	int V = adj.size();
	vector<bool> visited(V);
	vector<bool> recStack(V);
	for(int i = 0; i < V; i++){
		visited[i] = false;
		recStack[i] = false;
	}
	function<bool(int)> cycle = [&](int v){
			if(visited[v] == false){
				visited[v] = true;
				recStack[v] = true;
				for(int i : adj[v]){
					if (!visited[i] && cycle(i))return true;
					else if (recStack[i])return true;
				}
			}
			recStack[v] = false;
			return false;
	};
	for(int i = 0; i < V; i++){
		if(cycle(i))return true;
	}
	return false;
}



// AshishGup's version: --------------------------------------------------------------------
// put this in void solve(). Remember to change n+m to n or graph's size (number of nodes) wherever required.
    // =================================================================================
    // for directed graphs:
    vector<ll> vis(n + m, 0);
    // graph vector<vector<int>> g(n + m).
    function<bool(int)> findLoop = [&](int v) -> bool {
        if(vis[v] == 1) {return true;}
        if(vis[v] == 2) {return false;}
 
        vis[v] = 1;
        for(auto& x : g[v]) {
            if(findLoop(x)) {return true;}
        }
 
        vis[v] = 2; // i am done exploring for cycles/loops with this node. signing off.
        return false;
    };
 
    // --------------------------------------------------------
 
    auto checkLoop = [&]() -> bool {
        fill(vis.begin(), vis.end(), 0LL);
        for(ll i = 0; i < n + m; i++) { // there are n+m nodes in this graph (might want to change it to n)
            if(vis[i] == 0 && findLoop(i)) {return true;}
        }
        return false;
    };
    
