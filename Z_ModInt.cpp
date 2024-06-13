//==================================================================

//modular arithmetic for MOD type questions code below:




int P = 1000000007;
// assume -P <= x < 2P
template<class T>
T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}

    // Ensure x is always within the range [0, P-1]
    static int norm(int x) {
        if (x < 0) {
            x %= P;
            x += P;
            x %= P;
        }
        if (x >= P) x %= P;
        return x;
    }

    int val() const {
        return norm(x);
    }

    Z operator-() const {
        return Z(norm(P - x));
    }

    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }

    Z &operator*=(const Z &rhs) {
        x = norm(ll(x) * rhs.x % P);
        return *this;
    }

    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }

    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }

    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }

    Z &operator%=(const Z &rhs) {
        x = norm(x % rhs.x);
        return *this;
    }

    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }

    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }

    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }

    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }

    friend Z operator%(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res %= rhs;
        return res;
    }

    friend bool operator==(const Z &lhs, const Z &rhs) {
        return lhs.val() == rhs.val();
    }

    friend bool operator!=(const Z &lhs, const Z &rhs) {
        return lhs.val() != rhs.val();
    }

    friend bool operator<(const Z &lhs, const Z &rhs) {
        return lhs.val() < rhs.val();
    }

    friend bool operator>(const Z &lhs, const Z &rhs) {
        return lhs.val() > rhs.val();
    }

    friend istream &operator>>(istream &is, Z &a) {
        ll v;
        is >> v;
        a = Z(v);
        return is;
    }

    friend ostream &operator<<(ostream &os, const Z &a) {
        return os << a.val();
    }
};


//Z ans;
// or
//Z fact[100005];
//u get the point ig, Z is a new datatype like int.
//if u do Z%2, be sure to change P to 1000000000.
// CHANGE P and NN whenever required!!!!
//===========================================================
const int NN = 300005; //3e5
Z fac[NN];

Z NcR(int n, int r) {
    if(n<r) {return 0;}
    if(r==0) {return 1;}

    //fill factorial array

    return fac[n]/(fac[r]*fac[n-r]);
}

// dont go for the factorial array method in this question,
// since we may require a factorial of a very big number. Do this instead:
Z NcR_slow(int n, int r) {
    if(n < r) {return 0;}
    Z prod = 1;
    for(int i = 0; i < r; i++) {
        prod *= (n-i);
        prod /= (i+1);
    }
    return prod;
}

    //put this in int main
    fac[0] = 1; fac[1] = 1; fac[2] = 2;
    for(int i = 3; i < NN; i++) {
        fac[i] = fac[i-1]*i;
    }
//===========================================================
