//dfs based topological sort
vector<int> toposort(vector<vector<int>> &adj) {
    int V = adj.size();
    stack<int> Stack;
    vector<bool> visited(V, false);

    //dfs based topological sort
    function<void(int)> toposort = [&](int v) -> void {
        visited[v] = true;
        for(auto i : adj[v]) {
            if(visited[i]==false) {
                toposort(i);
            }
        }

        Stack.push(v);
    };

    for(int i = 0; i<V; i++) {
        if(visited[i]==false) toposort(i);
    }

    vector<int> ans;
    while(Stack.empty()==false) {
        ans.push_back(Stack.top());
        Stack.pop();
    }

    return ans;
}
// check out cyclicCheck.cpp from the repo as well, might want to use it before using toposort.
//=====================================================================================
