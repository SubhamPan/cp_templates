

// kactl version:

vector<ll> val, comp, z, cont;
ll Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    ll low = val[j] = ++Time;
    ll x;
    z.push_back(j);
    for(auto e : g[j]) if (comp[e] < 0) {
        low = min(low, val[e] ?: dfs(e,g,f));
    }

    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j) ;
        f(cont);
        cont.clear();
        ncomps++;
    }
    return val[j] = low;
}

template<class G, class F> void scc(G& g, F f) {
    ll n = sz(g);
    val.assign(n, 0);
    comp.assign(n, -1);
    Time = ncomps = 0;
    for(ll i = 0; i < n; i++) {
        if(comp[i] < 0) {
            dfs(i, g, f);
        }
    }
}

// void solve() {
//     ll n, m; cin >> n >> m;
//     vector<vector<ll>> dg(n);
//     for(ll i = 0; i < m; i++) {
//         ll u, v; cin >> u >> v; u--; v--;
//         dg[u].push_back(v);
//     }
 
//     scc(dg, [](vector<ll>& v){});
 
//     cout << ncomps << endl;
//     for(auto x : comp) {cout << x+1 << " ";}
//     cout << endl;
// }
// -----------------
// // Output SCCs
//     scc(graph, [](vector<int>& component) {
//         cout << "SCC: ";
//         for (int x : component) {
//             cout << x << " ";
//         }
//         cout << endl;
//     });


// ==================================================================================
