// DSU dsu(n+1);
class DSU {
public:
    int n; // check whether you inputted n or n+1 as argument in dsu.
    //p is parents vector, sz is size vector
    vector<int> p, sz;

    //constructor initializing DSU object with given number of elements '_n'
    DSU(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0); //p vector is now: 0 1 2 3 4 ... n-1
        //so effectively intializing each element as its own parent
        sz.resize(n, 1);
    }

    int get_top(int x) {
        if(x==p[x]) return x;
        return p[x] = get_top(p[x]);
    }

    void merge(int a, int b) {
        int c = get_top(a);
        int d = get_top(b);
        if(d!=c) {
            if(sz[c] < sz[d]) swap(c,d);

            p[d] = c;
            sz[c] += sz[d];
        } else{
            //you made a cycle by including this edge a-b.
        }
    }

    bool same(int x, int y) {
        return get_top(x)==get_top(y);
    }

    int size(int x) {
        return sz[get_top(x)];
    }

};
