// Check this solution (Fenwick Tree + Euler Tour) to know how to use it:
// https://codeforces.com/contest/1891/submission/231327175

struct FenwickTree { // 0 based indexing implementation
    vector<int> bit;  // binary indexed tree
    int n;
 
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
 
    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
 
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
 
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
 
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
 
    void addRange(int l, int r, int x){
        add(l, x);
        add(r + 1, -x);
    }
 
    void setElement(int idx, int x){
        addRange(idx, idx, x - getElement(idx));
    }
 
    int getElement(int idx){
        return sum(idx);
    }
 
    void print(){
        // for (int i = 0; i < n; i++){
        //     cout << getElement(i) << " ";
        // }
        // cout << endl;
    }
};
