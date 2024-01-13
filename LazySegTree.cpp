// tageter2004's lazy segtree template:
// lsegtree<ll> sg(array)
template<typename T>
class lsegtree{
	public:
	struct node{
		int val; int cnt;
		int lazy = -1; // contents
		void merge(const node& l,const node& r){ 
			lazy = -1;
			cnt = l.cnt + r.cnt;
			val = l.val + r.val; 
		};
		void apply(){
			val = lazy*cnt;
			lazy = -1;
		};
	};
	int base = 1;
	vector<node> tree;
	lsegtree(vector<T> a){
		int _n = (int)a.size();
		while(base < _n) base*=2;
		tree.resize(2*base);
		for(int i = 0; i < _n; i++) {
			tree[base+i] = node{a[i],1};    // leaf values
		}
		for(int i = _n; i < base; i++) {
			tree[base+i] = node{0,1};    // default leaf values
		}
		for(int i = base-1;i>=1;i--) {
			tree[i].merge(tree[2*i],tree[2*i + 1]);
		}
	};
	// update in [q_l,q_r]
	void update(int id, int l, int r, int q_l, int q_r, int sett){
		if(tree[id].lazy != -1){ // lazy condition
			l==r ? :tree[2*id].lazy = tree[id].lazy;
			l==r ? :tree[2*id + 1].lazy = tree[id].lazy;
			tree[id].apply();
		}
		if(l > q_r or r < q_l) {
			return;
		}
		if(q_l <= l and q_r >= r) {
			l==r ? :tree[2*id].lazy = sett ;
			l==r ? :tree[2*id + 1].lazy = sett;
			tree[id].val = sett*tree[id].cnt; // normal updates
			return;
		}
		int m = (l + r)/2;
		update(2*id, l, m, q_l, q_r, sett);
		update(2*id + 1, m + 1, r, q_l, q_r, sett);
		tree[id].merge(tree[2*id],tree[2*id + 1]);
	};
	// get from [q_l,q_r]
	node get(int id , int l, int r, int q_l, int q_r){
		if(tree[id].lazy != -1){ // lazy condition
			l==r ? :tree[2*id].lazy = tree[id].lazy;
			l==r ? :tree[2*id + 1].lazy = tree[id].lazy;
			tree[id].apply();
		}
		if(q_l <= l and q_r >= r) {
			return tree[id];
		}
		int m = (l + r)/2;
		if(m + 1 > q_r)
			return get(2*id, l, m, q_l, q_r);
		else if(m < q_l)
			return get(2*id + 1, m+1, r, q_l, q_r);
		node newnode;
		newnode.merge(get(2*id, l, m, q_l, q_r),get(2*id + 1, m+1, r, q_l, q_r));
		return newnode;
	};
	void update(int q_l, int q_r, int sett){
		update(1, 0, base-1, q_l, q_r, sett);
	}
	node get(int q_l, int q_r){
		return get(1, 0, base-1, q_l, q_r);
	}
};




//======================================================================================




 
template<class T, class U>
// T -> node, U->update.
struct Lsegtree{
    vector<T>st;
    vector<U>lazy;
    ll n;
    ll identity_element;
    ll identity_update;
    Lsegtree(ll n, T identity_element, U identity_update)
    {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(4*n,identity_element);
        lazy.assign(4*n, identity_update);
    }
    T combine(T l, T r)
    {
        // change this function as required.
        T ans = (l + r);
        return ans;
    }
    void buildUtil(ll v, ll tl, ll tr, vector<T>&a)
    {
        if(tl == tr)
        {
            st[v] = a[tl];
            return;
        }
        ll tm = (tl + tr)>>1;
        buildUtil(2*v + 1, tl, tm,a);
        buildUtil(2*v + 2,tm+1,tr,a);
        st[v] = combine(st[2*v + 1], st[2*v + 2]);
    }

    // change the following 2 functions, and you're more or less done.
    T apply(T curr, U upd, ll tl, ll tr)
    {
        T ans =  (tr-tl+1)*upd;
        return ans;
    }
    U combineUpdate(U old_upd, U new_upd, ll tl, ll tr)
    {
        U ans = old_upd;
        ans=new_upd;
        return ans;
    }  


    void push_down(ll v, ll tl, ll tr)
    {
        if(lazy[v] == identity_update)return;
        st[v] = apply(st[v], lazy[v], tl, tr);
        if(2*v + 1 <= 4*n)
        {
            ll tm = (tl + tr)>>1;
            lazy[2*v + 1] = combineUpdate(lazy[2*v+1], lazy[v], tl, tm);
            lazy[2*v + 2] = combineUpdate(lazy[2*v+2], lazy[v], tm+1,tr);            
        }
        lazy[v] = identity_update;
    }
    T queryUtil(ll v, ll tl, ll tr, ll l, ll r)
    {
        push_down(v,tl,tr);
        if(l > r)return identity_element;
        if(tr < l or tl > r)
        {
            return identity_element;
        }
        if(l <= tl and r >= tr)
        {
            return st[v];
        }
        ll tm = (tl + tr)>>1;
        return combine(queryUtil(2*v+1,tl,tm,l,r), queryUtil(2*v+2,tm+1,tr,l,r));
    }
 
    void updateUtil(ll v, ll tl, ll tr, ll l, ll r, U upd)
    {
        push_down(v,tl,tr); 
        if(tr < l or tl > r)return;
        if(tl >=l and tr <=r)
        {
            lazy[v] = combineUpdate(lazy[v],upd,tl,tr);
            push_down(v,tl,tr);
        }
        else
        {
            ll tm = (tl + tr)>>1;
            updateUtil(2*v+1,tl,tm,l,r,upd);
            updateUtil(2*v+2,tm+1,tr,l,r,upd);
            st[v] = combine(st[2*v + 1], st[2*v+2]);
        }
    }
 
 
 
    void build(vector<T>a)
    {
        // assert(sz(a) == n);
        buildUtil(0,0,n-1,a);
    }
    T query(ll l, ll r)
    {
        return queryUtil(0,0,n-1,l,r);
    }
    void update(ll l,ll r, U upd)
    {
        updateUtil(0,0,n-1,l,r,upd);
    }
};
