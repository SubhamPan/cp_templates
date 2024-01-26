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

    int find(int x) {
        if(x==p[x]) return x;
        return p[x] = find(p[x]);
    }

    void merge(int a, int b) {
        int c = find(a);
        int d = find(b);
        if(d!=c) {
            if(sz[c] < sz[d]) swap(c,d);

            p[d] = c;
            sz[c] += sz[d];
        } else{
            //you made a cycle by including this edge a-b.
        }
    }

    bool same(int x, int y) {
        return find(x)==find(y);
    }

    int size(int x) {
        return sz[find(x)];
    }

};
