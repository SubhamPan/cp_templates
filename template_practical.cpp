#include <bits/stdc++.h>
using namespace std;

using ll = long long; using ld = long double;
#define int long long
#define double long double
#define endl '\n'
#define Hi_I_am_Subham_Pan ios_base::sync_with_stdio(false);cin.tie(0); cout.tie(0);
#define vin(a) for(auto&XX:a)cin>>XX;//idk y but it restricts my thought process at times
#define vout(v) for (auto XX: v)cout<<XX<<' ';cout<<endl;
#define meh {cout<<"NO"<<endl;return;}
#define yay {cout<<"YES"<<endl;return;}
//=======================================================------------------------------------------------------
void print(int t) {cout << t;} 
void print(string t) {cout << t;}
void print(char t) {cout << t;}
void print(double t) {cout << t;}
template <class T, class V> void print(pair <T, V> p);
template <class T> void print(vector <T> v);
template <class T> void print(set <T> v);
template <class T, class V> void print(map <T, V> v);
template <class T> void print(multiset <T> v);
template <class T, class V> void print(pair <T, V> p) {cout << "{"; print(p.first); cout << ","; print(p.second); cout << "}";}
template <class T> void print(vector <T> v) {cout << "[ "; for (T i : v) {print(i); cout << " ";} cout << "]\n";}
template <class T> void print(set <T> v) {cout << "[ "; for (T i : v) {print(i); cout << " ";} cout << "]\n";}
template <class T> void print(multiset <T> v) {cout << "[ "; for (T i : v) {print(i); cout << " ";} cout << "]\n";}
template <class T, class V> void print(map <T, V> v) {cout << "[ "; for (auto i : v) {print(i); cout << " ";} cout << "]\n";}
//=======================================================------------------------------------------------------
// #define pow2(x) (1ll<<(x))
template <typename T, typename U> T cdiv(T x, U y) {assert(y!=0);return (x > 0 ? (x + y - 1) / y : x / y);}
template <typename T, typename U> T fdiv(T x, U y) {assert(y!=0);return (x > 0 ? x / y : (x - y + 1) / y);}
template <typename T> int sgn(T val) {return (T(0) < val) - (val < T(0));} //sgn(x) gives -1/0/1
//returns integer, only works if a is a guarantee perfect square
long long sqroot(long long a){long long b = (long long) sqrtl(a);if ((b + 1) * (b + 1) == a){b++;}return b;}
constexpr ll inf = 1E18;
//(raise(a,b) = a^b) [a,b > 0].
long long raise(long long a, long long b) {long long res = 1;for(int i = 0; i<b; i++) {if(inf/res < a) return 0;res *= a;}return res;}
bool isSquare(int n) {int r = sqrtl(1.0L * n);return r*r == n;}
//=======================================================----------------------------------
const int MAX = 200007; //2*10^5 + 7
const int mod = 1000000007; //1e9+7, comment it out if u want to use the other MOD
// // const int MOD = 998244353;
// const double EPS=1E-9;
// const int MAXN = 10000010; //1e7+10
//----------------



void solve() {
      

      

      // cout << "===========" << endl;    
}

/*ngu, lesgo*/
int32_t main() {
      Hi_I_am_Subham_Pan
      //cout<<fixed<<setprecision(20)<<x; //-> for printing a double 'x'.

      // freopen("", "r", stdin);
      // freopen("", "w", stdout);

      int TT=1;
      cin>>TT; //comment out this line if only 1 test case is needed
      while(TT--) {
            solve();
      }

      return 0;
}

