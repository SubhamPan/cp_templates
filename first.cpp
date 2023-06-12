// FXNS
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



//=================================================================
//===========================================================

//Array of prime numbers (denoted by 1) till const int MAX.
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

    void unite(int a, int b) {
        int c = find(a);
        int d = find(b);
        if(d!=c) {
            if(sz[c] < sz[d]) swap(c,d);

            p[d] = c;
            sz[c] += sz[d];
        }
    }

};

