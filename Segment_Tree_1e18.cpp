// https://atcoder.jp/contests/abc360/submissions/55082266

template <class S, S (*op)(S, S), S (*e)()> struct isegtree {
    long long MIN_BOUND = -1e18, MAX_BOUND = 1e18;

    isegtree() {}
    isegtree(long long small, long long big) : MIN_BOUND(small), MAX_BOUND(big) {}

    struct node {
        S val;
        int l, r;
    };
    vector<node> nodes = {{e(), -1, -1}};

    int create() {
        nodes.push_back({e(), -1, -1});
        return nodes.size() - 1;
    }  

    int _update(int v, long long tl, long long tr, long long pos, S val) {
        if (v < 0) v = create();
        if (tr - tl == 1) nodes[v].val = val;
        else {
            long long tm = tl + (tr - tl) / 2;
            if (pos < tm) nodes[v].l = _update(nodes[v].l, tl, tm, pos, val);
            else nodes[v].r = _update(nodes[v].r, tm, tr, pos, val);
            nodes[v].val = op(nodes[v].l < 0 ? e() : nodes[nodes[v].l].val, nodes[v].r < 0 ? e() : nodes[nodes[v].r].val);
        }
        return v;
    }

    S _query(int v, long long tl, long long tr, long long l, long long r) {
        if (v < 0 || r <= tl || tr <= l) return e();
        if (l <= tl && tr <= r) return nodes[v].val;
        long long tm = tl + (tr - tl) / 2;
        return op(_query(nodes[v].l, tl, tm, l, r), _query(nodes[v].r, tm, tr, l, r));
    }

    void set(long long pos, S val) {
        assert(MIN_BOUND <= pos && pos < MAX_BOUND);
        _update(0, MIN_BOUND, MAX_BOUND, pos, val);
    }

    S prod(long long l, long long r) {
        if (l >= r) return e();
        return _query(0, MIN_BOUND, MAX_BOUND, l, r);
    }

    S all_prod() {
        return nodes[0].val;
    }
};

using S = int;

S op(S a, S b) {
    return max(a, b);
}

S e() {
    return 0;
}

typedef isegtree<S, op, e> seg;
