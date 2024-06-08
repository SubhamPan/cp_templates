// FXNS

// this file is a warehouse of functions commonly used in contests.
// i mainly use the Z (mint) template and the factorization functions from here. Most of the functions apart from them might be outdated.


//=========================================================
//Interactive questions
int ask(int r,int c) {
    cout<<"? "<<r<<" "<<c<<endl;
    cin>>r;
    return r;
}
void answer(int r,int c) {
    cout<<"! "<<r<<" "<<c<<endl;
    return;
}

//=========================================================
string decToBinary(int num) {
    string ans = "";
    for(int i = 10; i>=0; --i) {
        //check i upper limit according to question
        ans += to_string((num>>i)&1);
    }
    return ans;
}

    //removing the extra leading zeroes from finalAns binary string
    int count = 0;
    for(int i = 0; i<sz(finalAns); i++) {
        if(finalAns[i]=='1') {
            count = i;
            break;
        }
    }
    finalAns = finalAns.substr(count, sz(finalAns) - count);
    //we had to remove the leading zeroes before using stoi to convert it from binary to decimal
    cout<<stoi(finalAns, 0, 2)<<endl;
//=========================================================


int fact(int n)
{
    int res=1;
    for(int i=2;i<=n;i++)
    res*=i;
    return res;
}

// Function to find the nCr
ll NcR(int n, int r)
{
 
    // p holds the value of n*(n-1)*(n-2)...,
    // k holds the value of r*(r-1)...
    long long p = 1, k = 1;
 
    // C(n, r) == C(n, n-r),
    // choosing the smaller value
    if (n - r < r)
        r = n - r;
 
    if (r != 0) {
        while (r) {
            p *= n;
            k *= r;
 
            // gcd of p, k
            long long m = __gcd(p, k);
 
            // dividing by gcd, to simplify
            // product division by their gcd
            // saves from the overflow
            p /= m;
            k /= m;
 
            n--;
            r--;
        }
 
        // k should be simplified to 1
        // as C(n, r) is a natural number
        // (denominator should be 1 ) .
    }
 
    else
        p = 1;
 
    // if our approach is correct p = ans and k =1
    return p;
}



//==================================================================
//==================================================================

//modular arithmetic for MOD type questions code below:



constexpr int P = 1000000007;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
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
    // Z(ll x) : x(norm((int)(x % P))) {} //uncomment this line if there is no #define int long long
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = ll(x) * rhs.x % P;
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
        x = x % rhs.x;
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
        if(lhs.x == rhs.x) {
            return true;
        } else {
            return false;
        }
    }
    friend bool operator!=(const Z &lhs, const Z &rhs) {
        if(lhs.x != rhs.x) {
            return true;
        } else {
            return false;
        }
    }
    friend bool operator<(const Z &lhs, const Z &rhs) {
        if(lhs.x < rhs.x) {
            return true;
        } else {
            return false;
        }
    }
    friend bool operator>(const Z &lhs, const Z &rhs) {
        if(lhs.x > rhs.x) {
            return true;
        } else {
            return false;
        }
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
//===============================================================================

//Array of prime numbers (denoted by 1) till const int MAX. -> to be put globally.
int prime[MAX];

    //the following part is to be put into int main
    fill(prime, prime + MAX, 1);

    for(ll i = 2; i<MAX; i++) {
        if(!prime[i]) continue;
        for(ll j = i * 2; j<MAX; j+=i) {
            prime[j] = 0;
        }
    }

//============================================================
//Prime factorization
int x;
cin>>x;
map<int, int> pf;
for(int i = 2; i*i<=x; i++) {
    while(x%i==0) {
        pf[i]++;
        x/=i;
    }
}
if(x>1) {
    pf[x]++;
}

//============================================================


bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

//============================================================

//all factors list
//e.g.
//int a = 36
//vi fa = allfactorslist(a);
//print(fa);
    //output: 1 2 3 4 6 9 12 18 36

vector<int> allfactorslist(int x) {
    vector<int> temp;
    for(int i = 1; i*i<=x; i++) {
        if(x%i==0) {
            temp.push_back(i);
            if(x/i != i) {
                temp.push_back(x/i);
            }
        }
    }
    sort(temp.begin(), temp.end());
    return temp;
}


//============================================================
//============================================================


bool vis[100001] = {false};
 
void dfs (vector <int> g[], int at){
    if (vis[at]) return;
    vis[at] = true;
    for (auto x: g[at]){
        dfs (g, x);
    }
}
 

list <int> q;
bool vis2[100001] = {false};
 
void bfs (vector <int> g[], int at){
    vis2[at] = true;
    q.push_back(at);
    while (!q.empty()){
        int s = q.front();
        q.pop_front();
        cout << s << " ";
        for (auto x: g[s]){
            if (!vis2[x]){
                vis2[x] = true;
                q.push_back(x);
            }
        }
    }
}


//===============================================================================================
//===============================================================================================
// template
