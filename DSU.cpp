// DSU dsu(n+1);
class DSU {
public:
    int n;
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
 
    bool merge(int a, int b) { // returns false if a cycle will get created; returns true if normal merge took place.
        int c = find(a);
        int d = find(b);
        if(d!=c) {
            if(sz[c] < sz[d]) swap(c,d);
 
            p[d] = c;
            sz[c] += sz[d];
            // sz[d] = 0; -> not sure if this will work
            return true;
        } else{
            //you made a cycle by including this edge a-b.
            return false;
        }
    }
 
    bool isSame(int x, int y) {
        return find(x)==find(y);
    }
 
    int getSize(int x) {
        return sz[find(x)];
    }
 
};
