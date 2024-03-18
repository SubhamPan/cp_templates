struct DisjointSetWithRollback {
	vector<int> par;
	vector<pair<int, int>> mods;
	DisjointSetWithRollback(int n) : par(n, -1) {}
	int get(int a) {
		while (par[a] >= 0) a = par[a];
		return a;
	}
	int getSize(int a) { return -par[get(a)]; } // O(log n)!
	bool join(int a, int b) {
		int pa = get(a), pb = get(b);
		if (pa == pb) return false;
		if (par[pa] > par[pb]) swap(pa, pb);
		mods.emplace_back(pa, par[pa]);
		mods.emplace_back(pb, par[pb]);
		// Make smaller pb a child of larger pa.
		par[pa] += par[pb];
		par[pb] = pa;
		return true;
	}
	int save() { return mods.size(); }
	void rollback(int savePoint) {
		while (mods.size() > savePoint) {
			auto& v = mods.back();
			par[v.first] = v.second;
			mods.pop_back();
		}
	}
};

// https://codeforces.com/contest/1681/submission/159596854
// https://codeforces.com/contest/1681/submission/252078939 -> [my submission for the saame question]
