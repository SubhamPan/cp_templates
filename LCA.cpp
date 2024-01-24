// put in void solve():

    // vector<vector<int>> tree(n+1) // adjacency matrix; replace tree with adj / g.
    vector<int> depth(n+1, 0);
    vector<vector<int>> ancestor(n+1, vector<int>(20, 0)); // assuming there will be (2^20) levels in the tree.
 
    function<void(int, int)> depthassign = [&](int v, int par) {
        depth[v] = depth[par] + 1;
 
        for(auto x : tree[v]) {
            if(x == par) continue;
            depthassign(x, v);
        }
    };
    depthassign(1, 0);
 
    function<void(int, int)> makeanc = [&](int v, int par) {
        if(par >= 1) {
            ancestor[v][0] = par;
            for(int i = 1; i < 20; i++) {
                ancestor[v][i] = ancestor[ancestor[v][i-1]][i-1];
            }
        }
 
        for(auto x : tree[v]) {
            if(x == par) continue;
            makeanc(x, v);
        }
    };
    makeanc(1, 0);
 
    auto givelca = [&](int a, int b) -> int {
        if(depth[a] < depth[b]) {
            // swap(a,b)
            int temp = a; a = b; b = temp;
        }
 
        for(int i = 19; i >= 0; i--) {
            if(depth[a] - (1LL << i) >= depth[b]) {
                a = ancestor[a][i];
            }
        }
 
        if(a == b) return a;
 
        for(int i = 19; i >= 0; i--) {
            if(ancestor[a][i] != ancestor[b][i]) {
                a = ancestor[a][i];
                b = ancestor[b][i];
            }
        }
 
        return ancestor[a][0];
    };
 
    auto dist = [&](int u, int v) -> int {
        // i want u to have more depth than v
        if(depth[u] < depth[v]) {
            // swap(u,v)
            int temp = u; u = v; v = temp;
        }
 
        return (depth[u] - depth[v]);
    };

