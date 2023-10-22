//Shadow's(IITB) template
class segtree {
 public:
	struct node {
		// don't forget to set default value (used for leaves)
		// not necessarily neutral element!
		int lar = -1e18; // Set identity element
		int add = 0; 
 
		void apply(int l, int r, int v) { // Value of a single node (used by build and update)
			lar = v;
			//sum += v; 
		}
		void push(int l, int r, int v) { // Lazy propogation (used by add)
			lar += v;
			add += v;
		}
	};
	node unite(const node &a, const node &b) const { // Set combination operation
		node res;
		res.lar = max(a.lar,b.lar);
		//res.sum = a.sum + b.sum; 
		return res;
	}
	inline void push(int x, int l, int r) {
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		if (tree[x].add != 0) {
			tree[x + 1].push(l, y, tree[x].add);
			tree[z].push(y + 1, r, tree[x].add);
			tree[x].add = 0;
		}
		
		// Don't forget to uncomment node.push
	}
	inline void pull(int x, int z) {
		tree[x] = unite(tree[x + 1], tree[z]);
	}
 
	int n;
	vector<node> tree;
	void build(int x, int l, int r) {
		if (l == r) {
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		build(x + 1, l, y);
		build(z, y + 1, r);
		pull(x, z);
	}
	template <typename M>
	void build(int x, int l, int r, const vector<M> &v) {
		if (l == r) {
			tree[x].apply(l, r, v[l]);
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		build(x + 1, l, y, v);
		build(z, y + 1, r, v);
		pull(x, z);
	}
	node find(int x, int l, int r, int lx, int rx) {
		if (lx <= l && r <= rx) {
			return tree[x];
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		node res{};
		if (rx <= y) {
			res = find(x + 1, l, y, lx, rx);
		} else {
			if (lx > y) {
			res = find(z, y + 1, r, lx, rx);
			} else {
			res = unite(find(x + 1, l, y, lx, rx), find(z, y + 1, r, lx, rx));
			}
		}
		pull(x, z);
		return res;
	}
	template <typename... M>
	void update(int x, int l, int r, int lx, int rx, const M&... v) {
		if (lx <= l && r <= rx) {
			tree[x].apply(l, r, v...);
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		if (lx <= y) {
			update(x + 1, l, y, lx, rx, v...);
		}
		if (rx > y) {
			update(z, y + 1, r, lx, rx, v...);
		}
		pull(x, z);
	}
	template <typename... M>
	void add(int x, int l, int r, int lx, int rx, const M&... v) {
		if (lx <= l && r <= rx) {
			tree[x].push(l, r, v...);
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		if (lx <= y) {
			add(x + 1, l, y, lx, rx, v...);
		}
		if (rx > y) {
			add(z, y + 1, r, lx, rx, v...);
		}
		pull(x, z);
	}
	int find_first_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
		if (l == r) {
			return l;
		}
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res;
		if (f(tree[x + 1])) {
			res = find_first_knowingly(x + 1, l, y, f);
		}
		else {
			res = find_first_knowingly(z, y + 1, r, f);
		}
		pull(x, z);
		return res;
	}
	int find_first(int x, int l, int r, int lx, int rx, const function<bool(const node&)> &f) {
		if (lx <= l && r <= rx) {
			if (!f(tree[x]))return -1;
			return find_first_knowingly(x, l, r, f);
		}
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res = -1;
		if (lx <= y) {
			res = find_first(x + 1, l, y, lx, rx, f);
		}
		if (rx > y && res == -1) {
			res = find_first(z, y + 1, r, lx, rx, f);
		}
		pull(x, z);
		return res;
	}
	int find_last_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
		if (l == r)return l;
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res;
		if (f(tree[z]))res = find_last_knowingly(z, y + 1, r, f);
		else res = find_last_knowingly(x + 1, l, y, f);
		pull(x, z);
		return res;
	}
	int find_last(int x, int l, int r, int lx, int rx, const function<bool(const node&)> &f) {
		if (lx <= l && r <= rx) {
			if (!f(tree[x]))return -1;
			return find_last_knowingly(x, l, r, f);
		}
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res = -1;
		if (rx > y) {
			res = find_last(z, y + 1, r, lx, rx, f);
		}
		if (lx <= y && res == -1) {
			res = find_last(x + 1, l, y, lx, rx, f);
		}
		pull(x, z);
		return res;
	}
	segtree(int _n) : n(_n) {
		assert(n > 0);
		tree.resize(2 * n - 1);
		build(0, 0, n - 1);
	}
	template <typename M>
	segtree(const vector<M> &v) {
		n = v.size();
		assert(n > 0);
		tree.resize(2 * n - 1);
		build(0, 0, n - 1, v);
	}
	node find(int p) { // value at index p
		assert(0 <= p && p <= n - 1);
		return find(0, 0, n - 1, p, p);
	}
	template <typename... M>
	void update(int lx, int rx, const M&... v) {
		assert(0 <= lx && lx <= rx && rx <= n - 1);
		update(0, 0, n - 1, lx, rx, v...);
	}
	void add(int i, int v){
		assert(i >= 0 && i < n);
		add(i,i,v);
	}
	// All functions below
	void update(int i, int v){ // Sets value at index i to v
		assert(i >= 0 && i < n);
		update(i,i,v);
	}
	template <typename... M>
	void add(int lx, int rx, const M&... v) { // adds v to a[lx to rx]
		assert(0 <= lx && lx <= rx && rx <= n - 1);
		add(0, 0, n - 1, lx, rx, v...);
	}
	node find(int lx, int rx) { // value of lx to rx
		assert(0 <= lx && lx <= rx && rx <= n - 1);
		return find(0, 0, n - 1, lx, rx);
	}
	// find_first and find_last call all FALSE elements
	// to the left (right) of the sought position exactly once
	int find_first(int lx, int rx, const function<bool(const node&)> &f) {
		assert(0 <= lx && lx <= rx && rx <= n - 1);
		return find_first(0, 0, n - 1, lx, rx, f);
	}
	int find_last(int lx, int rx, const function<bool(const node&)> &f) {
		assert(0 <= lx && lx <= rx && rx <= n - 1);
		return find_last(0, 0, n - 1, lx, rx, f);
	}
};


//===============================================================================================
//===============================================================================================
//SirBRuce's template
template <typename T>
class SegTree {
public:
    vector<T> tree;
    T zero; // Neutral element

    SegTree (int sz) {
        tree.resize(4*sz+1);
    }

    T combine (T &a, T &b) {
        return a + b; // Combine function
    }

    void build (int id, int segl, int segr, vector<T> &v) {
        if (segl == segr) {
            tree[id] = v[segl];
            return;
        }
        int mid = (segl + segr)/2;
        build(2*id + 1, segl, mid, v);
        build(2*id + 2, mid+1, segr, v);
        tree[id] = combine(tree[2*id+1], tree[2*id+2]);
    }

    void modify (int pos, T val, int id, int segl, int segr) {
        if (segl == segr) {
            tree[id] = val;
            return;
        }
        int mid = (segl + segr)/2;
        if (pos>mid) {
            modify(pos, val, 2*id+2, mid+1, segr);
        }
        else {
            modify(pos, val, 2*id+1, segl, mid);
        }
        tree[id] = combine(tree[2*id+1], tree[2*id+2]);
    }

    T query (int l, int r, int id, int segl, int segr) {
        if (l>segr || segl>r) {
            return zero;
        }
        if (segl>=l && segr<=r) {
            return tree[id];
        }
        int mid = (segl + segr)/2;
        T leftVal = query(l, r, 2*id+1, segl, mid);
        T rightVal = query(l, r, 2*id+2, mid+1, segr);
        return combine(leftVal, rightVal);
    }
};



//===============================================================================================
//===============================================================================================
//SharmaHariSam's template - the one i liked the most so far, and the one im using.

//select T and identity_element carefully after some thought.
template<class T>
struct Segtree{
    vector<T>st;
    ll n;
    T identity_element;

    Segtree(ll n, T identity_element) {
        this->n = n;
        this->identity_element = identity_element;
        st.assign(4*n,identity_element);
    }
    
    T combine(T l, T r) {
        // change this function as required.
        T ans = l + r;
        return ans;
    }
//Build Package===================================================
    void buildUtil(ll v, ll tl, ll tr, vector<T>&a) {
        if(tl == tr) {
        //Setting up the bottom layer of the segtree. 
        //[the default one is just keeping the array elements as the bottom layer]
            st[v] = a[tl];
            return;
        }
        
        ll tm = (tl + tr)>>1;
        buildUtil(2*v + 1, tl, tm,a);
        buildUtil(2*v + 2,tm+1,tr,a);
        st[v] = combine(st[2*v + 1], st[2*v + 2]);
    }
    void build(vector<T>a) {
        assert(sz(a) == n);
        buildUtil(0,0,n-1,a);
    }
//===============================================================
//Query Package==================================================
    T queryUtil(ll v, ll tl, ll tr, ll l, ll r) {
        if(l > r)return identity_element;
        if(r < tl or l > tr) {
            return identity_element;
        }
        if(tl >= l and tr <= r) {
            return st[v];
        }
        ll tm = (tl + tr)>>1;
        return combine(queryUtil(2*v+1,tl,tm,l,r), queryUtil(2*v+2,tm+1,tr,l,r));
    }
    T query(ll l, ll r) {
        return queryUtil(0,0,n-1,l,r);
    }
//================================================================
//Update package==================================================
    T apply(T curr, T val) {
        // change this function if update is of some other kind.
        T ans = curr;
        ans = val;
        return ans;
    }
    void updateUtil(ll v, ll tl, ll tr, ll ind, T val) {
        if(tl == tr) {
            st[v] = apply(st[v],val);
            return;
        }        
        ll tm = (tl + tr)>>1;

        if(ind <= tm) {
            updateUtil(2*v+1,tl,tm,ind,val);
        } else {
            updateUtil(2*v+2,tm+1,tr,ind,val);
        }
        st[v] = combine(st[2*v + 1], st[2*v+2]);
    }
    void update(ll ind, T val) {
        updateUtil(0,0,n-1,ind,val);
    }
//==============================================================
};



//===============================================================================================
//===============================================================================================
// template
