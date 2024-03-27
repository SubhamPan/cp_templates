    // zero based indexing of nodes,  copy this template and put it in void solve().
    vector<vector<int>> adj(n);
    vector<int> colouring(n);
    auto bipartite = [&]() -> bool {
        bool bip = true;

        for(int i = 0; i < n; i++) {colouring[i] = -1;}

        queue<int> q;
        q.push(0);
        colouring[0] = 0;

        while(q.empty() == false) {
            int v = q.front();
            q.pop();

            for(auto x : adj[v]) {
                if(colouring[x] == -1) {
                    colouring[x] = colouring[v] ^ 1;
                    q.push(x);
                } else {
                    bip = bip & (colouring[x] != colouring[v]);
                }
            }
        }

        return bip;
    };
