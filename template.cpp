#include <bits/stdc++.h>
using namespace std;
 
// #define ll long long int
using ll = long long;
//for tp
#define SubhamPan ios_base::sync_with_stdio(false);cin.tie(0); cout.tie(0);
//it doesnt matter v,t,a; u can use all(a) or vin(v) or anything.
//u get the point
#define vout(v) for (auto XX: v)cout<<XX<<' ';cout<<endl;
#define all(t) (t).begin(), (t).end()
#define rall(x) x.rbegin(), x.rend() //reversing a string/vector, can be stored somewhere
//the above one doesnt alter the original vector/string itsef though
//for altering the actual string/vector itself, use the following one:
#define reve(x) reverse(x.begin(), x.end());
#define sor(x) sort(all(x)) //can be used for vectors AND STRINGS TOO!
#define vin(a) for(auto&XX:a)cin>>XX;//idk y but it restricts my thought process at times
#define vvin(a) for(auto& b : a) {for(auto& x : b) cin>>x;}
#define vvout(a) for(auto& b: a) {for(auto& x : b) {cout<<x<<" ";}cout<<endl;}
#define sz(a) (int)a.size() //can be used for: vectors,strings,maps,sets
#define f first
#define s second
#define pb push_back
//for vpii, tuples:
#define eb emplace_back //a.eb(...);
// #define cnt(x,i) count(all(x), i); //can be used for vectors, strings //not working properly dk y
#define sort_unique(a) sort(all(a)),a.resize(unique(all(a))-a.begin())
#define pow2(x) (1ll<<(x))


#define lb lower_bound
#define ub upper_bound
 
typedef vector<int> vi;
typedef vector<ll> vl;

typedef vector<vector<int>> vvi; // vvi a(n, vi (m, 0));
typedef vector<vector<ll>> vvl;

typedef vector<pair<int,int>> vpii;
typedef vector<pair<ll, ll>> vpll;

typedef pair<int,int> pii;
typedef pair<ll, ll> pll;


//use the following in solve
#define meh {cout<<"NO"<<endl;return;}
#define yay {cout<<"YES"<<endl;return;}

//use the following in int main() or inside queries loop inside solve
#define IMmeh {cout<<"NO"<<endl;continue;}
#define IMyay {cout<<"YES"<<endl;continue;}

//debugging uses:========================================------------------------------------------------------
typedef long double ld;
void print(ll t) {cout << t;}
void print(int t) {cout << t;}
void print(string t) {cout << t;}
void print(char t) {cout << t;}
void print(double t) {cout << t;}
void print(ld t) {cout << t;}
 
template <class T, class V> void print(pair <T, V> p);
template <class T> void print(vector <T> v);
template <class T> void print(set <T> v);
template <class T, class V> void print(map <T, V> v);
template <class T> void print(multiset <T> v);
template <class T, class V> void print(pair <T, V> p) {cout << "{"; print(p.f); cout << ","; print(p.s); cout << "}";}
template <class T> void print(vector <T> v) {cout << "[ "; for (T i : v) {print(i); cout << " ";} cout << "]\n";}
template <class T> void print(set <T> v) {cout << "[ "; for (T i : v) {print(i); cout << " ";} cout << "]\n";}
template <class T> void print(multiset <T> v) {cout << "[ "; for (T i : v) {print(i); cout << " ";} cout << "]\n";}
template <class T, class V> void print(map <T, V> v) {cout << "[ "; for (auto i : v) {print(i); cout << " ";} cout << "]\n";}
//=======================================================------------------------------------------------------


template <typename T, typename U>
T cdiv(T x, U y) {
  return (x > 0 ? (x + y - 1) / y : x / y);
}
template <typename T, typename U>
T fdiv(T x, U y) {
  return (x > 0 ? x / y : (x - y + 1) / y);
}

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
} //sgn(x) gives -1/0/1

// const int MAX = 200007; 
// const int MOD = 1e9+7; //comment it out if u want to use the other MOD
// // const int MOD = 998244353;
// const double EPS=1E-6;
// const int MAXN = 1000010;
constexpr ll inf = 1E18;
//=================================================================

//mint paste here (if necessary)




//=================================================================
//dont write in solve if it is a prime factorization question
//write it in int main
//also write it in int main if a global array is required.

void solve() {

    
    


}

/*ngu*/
int main() {
    SubhamPan

    
    int TT=1;
    cin>>TT; //comment out this line if only 1 test case is needed
    while(TT--) {
        solve();
    }
 
    return 0;
}
