// put in void solve():
    // vector<vector<int>> tree(n+1) -> above this template
    // -------------------------------------------------------------------------------------------
    // everything is 1-based.
    // LCA, dist, depth, st_sz stuff
    vector<int> depth(n+1, 0);
    vector<int> st_sz(n+1, 0); // subtree size

    vector<int> tin(n+1, 0), tout(n+1, 0); int timer = 0; // timer shit

    const int LG = 20; // assuming there will be at max (2^20) levels in the tree. (2^20 > 100,000).
    vector<vector<int>> ancestor(n+1, vector<int>(LG, 0));
    

    // fills up depth, st_sz, and timer stuff. fills up ancestor too.
    function<void(int, int)> dfs_util = [&](int v, int par) {
        depth[v] = depth[par] + 1;
        st_sz[v] = 1;
        tin[v] = timer++;

        // fills up ancestor:------
        ancestor[v][0] = par;
        for(int i = 1; i < LG; i++) {
            ancestor[v][i] = ancestor[ancestor[v][i-1]][i-1];
        }
        // ------------------------
 
        for(auto x : tree[v]) {
            if(x == par) continue;
            dfs_util(x, v);
            st_sz[v] += st_sz[x];
        }

        tout[v] = timer++;
    };
    dfs_util(1, 1); // par = 1 makes it work, par = 0 messes up ancestor, idk why.
    

    // checks if a is ancestor of b.
    auto is_ancestor = [&](int a, int b) -> bool {
        return (tin[a] <= tin[b] && tout[b] <= tout[a]);
    };

    // keeps going up 'a', until it is about to become an ancestor of b
    // returns the highest (uppermost / farthest above from 'a') ancestor that is NOT an ancestor of b.
    auto go_up = [&](int a, int b) -> int {
        for(int i = LG - 1; i >= 0; i--) {
            if(is_ancestor(ancestor[a][i],b) == false) {
                a = ancestor[a][i];
            }
        }
        return a;
    };


    // returns lca node of a and b.
    auto givelca = [&](int a, int b) -> int {
        int result = -1;

        if(is_ancestor(a,b) == true) {
            result = a;
        } else if (is_ancestor(b,a) == true) {
            result = b;
        } else {
            result = ancestor[go_up(a, b)][0];
            // direct parent of (the uppermost ancestor of 'a' (that is NOT an ancestor of b)).
        }
        return result;
    };
    
    // returns distance between nodes u and v.
    auto dist = [&](int u, int v) -> int {
        // i want u to have more depth than v
        if(depth[u] < depth[v]) {
            // swap(u,v)
            int temp = u; u = v; v = temp;
        }
 
        return (depth[u] + depth[v] - 2 * depth[givelca(u, v)]);
    };

    // --------------------------------
    // e.g.
    // find the number of nodes (v) s.t. dist(a,v) == dist(b,v) [for given a and b].
    auto query = [&](int a, int b) -> int {

        int l = givelca(a,b);
        int res = -1;

        if(a == b) {
            res = n;
        } else if (dist(a,b) % 2 == 1) {
            res = 0;
        } else if (dist(a,l) == dist(b,l)) {
            int aa = go_up(a,l);
            int bb = go_up(b,l);

            res = n - st_sz[aa] - st_sz[bb];
        } else {
            if(depth[a] <= depth[b]) {
                swap(a,b);
            }

            int x = a;
            int dab = dist(a,b);

            dab /= 2;

            // get to the [uppermost ancestral node(x)] of 'a' such that dist(a,x) < dist
            // 1 1 1 1 1 1 0 0 0 0 0 [similar to bs on ans, get to the rightmost 1, 
            // and then do +1 at the end by doing anc[][0] (going to the direct parent of the node x.)]
            for(int i = LG - 1; i >= 0; i--) {
                if(dist(a, ancestor[x][i]) < dab) {
                    x = ancestor[x][i];
                }
            }

            int mid = ancestor[x][0]; // the +1(go to the direct parent of x) at the end

            res = st_sz[mid] - st_sz[x];

        }

        return res;
    };

    // ====================================================================================================



// ===============================================================================================================================================
// ===============================================================================================================================================
// Using (modified) the above LCA template to find the max-weighted edge between any two nodes (say u and v)
// max weighted edge between u and v = max(max_weight_edge(u, lca(u,v)), max_weight_edge(v, lca(u,v))
// and we can write the max_weight_edge function used on the RHS using binary lifting and LCA.

      // vector<vector<int>> tree(n+1) -> above this template; 
      // lite here i modified 'tree' below to g.
    // -------------------------------------------------------------------------------------------
    // everything is 1-based.
    // LCA, dist, depth, st_sz stuff
    vector<int> depth(n+1, 0);
    vector<int> st_sz(n+1, 0); // subtree size
 
    vector<int> tin(n+1, 0), tout(n+1, 0); int timer = 0; // timer shit
 
    const int LG = 20; // assuming there will be at max (2^20) levels in the tree. (2^20 > 100,000).
    vector<vector<int>> ancestor(n+1, vector<int>(LG, 0));
    vector<vector<int>> mx(n+1, vector<int>(LG, 0));
    
    // notice how i am preprocessing mx as well simulataneously
    // fills up depth, st_sz, and timer stuff. fills up ancestor too.
    function<void(int, int, int)> dfs_util = [&](int v, int par, int k = 0) {
        depth[v] = depth[par] + 1;
        st_sz[v] = 1;
        tin[v] = timer++;
 
        // fills up ancestor:------
        ancestor[v][0] = par;
        mx[v][0] = k; // edge weight between v and par.
        for(int i = 1; i < LG; i++) {
            // i == (2^ith) parent level.
            ancestor[v][i] = ancestor[ancestor[v][i-1]][i-1];
            mx[v][i] = max(mx[v][i-1], mx[ancestor[v][i-1]][i-1]);
        }
        // ------------------------
 
        for(auto x : g[v]) {
            if(x[0] == par) continue;
            dfs_util(x[0], v, x[1]); // passing the weight of the [edge {v, x[0]}] as the third parameter (x[1]).
            st_sz[v] += st_sz[x[0]];
        }
 
        tout[v] = timer++;
    };
    dfs_util(1, 1, 0); // par = 1 makes it work, par = 0 messes up ancestor, idk why.
    
 
    // checks if a is ancestor of b.
    auto is_ancestor = [&](int a, int b) -> bool {
        return (tin[a] <= tin[b] && tout[b] <= tout[a]);
    };
 
    // keeps going up 'a', until it is about to become an ancestor of b
    // returns the highest (uppermost / farthest above from 'a') ancestor that is NOT an ancestor of b.
    auto go_up = [&](int a, int b) -> int {
        for(int i = LG - 1; i >= 0; i--) {
            if(is_ancestor(ancestor[a][i],b) == false) {
                a = ancestor[a][i];
            }
        }
        return a;
    };
 
 
    // returns lca node of a and b.
    auto givelca = [&](int a, int b) -> int {
        int result = -1;
 
        if(is_ancestor(a,b) == true) {
            result = a;
        } else if (is_ancestor(b,a) == true) {
            result = b;
        } else {
            result = ancestor[go_up(a, b)][0];
            // direct parent of (the uppermost ancestor of 'a' (that is NOT an ancestor of b)).
 
 
            // behind the scenes yeh chal rha hai:
            // for(int i = LG - 1; i >= 0; i--) {
            //       if(ancestor[a][i] > 0 && is_ancestor(ancestor[a][i], b) == false) {
            //             a = ancestor[a][i];
            //       }
            // }
            // result = ancestor[a][0];
        }
 
        return result;
    };
 
      auto heaviest_edge = [&](int a, int b) -> int {
            if(a == b) return 0;
            int result = 0;
 
            for(int i = LG - 1; i >= 0; i--) {
                  if(ancestor[a][i] > 0 && is_ancestor(ancestor[a][i], b) == false) {
                        result = max(result, mx[a][i]);
                        a = ancestor[a][i];
                  }
            }
 
            result = max(result, mx[a][0]);
            return result;
      };


    // required ans = max(heaviest_edge(u, L), heaviest_edge(v, L)); [where L = LCA(u,v)]




