class DSUwithRollback {
  private:
      vector<int> p, sz;
      // stores previous unites
      vector<pair<int &, int>> history;
 
  public:
      DSUwithRollback(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
 
      int find(int x) { return x == p[x] ? x : find(p[x]); }
 
      bool merge(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) { return false; }
            if (sz[a] < sz[b]) { swap(a, b); }
 
            // save this merge operation
            history.push_back({sz[a], sz[a]});
            history.push_back({p[b], p[b]});
 
            p[b] = a;
            sz[a] += sz[b];
 
            return true;
      }
 
      int snapshot() { return history.size(); }
 
      void rollback(int until) {
            while (snapshot() > until) {
                  history.back().first = history.back().second;
                  history.pop_back();
            }
      }
 
      int getSize(int x) {
            return sz[find(x)];
      }
};

// https://codeforces.com/contest/1681/submission/159596854
// https://codeforces.com/contest/1681/submission/265639005 -> [my submission for the saame question]
