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
