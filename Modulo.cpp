// https://codeforces.com/contest/1925/submission/271937974
// Full set for SI ^
// (includes norm, add, mul, power, mod_div, init, NcR).
// [Pasted below:]

// #include <bits/stdc++.h>
// using namespace std;
// /* DaBest */
// using ll = long long; using ld = long double;
// #define int long long
// #define double long double
// #define endl '\n'

const ll mod = 1000000007;

const ll MAXN = 300001;
vector<ll> fac(MAXN);
vector<ll> inv_fac(MAXN);

void norm(ll &a) {
      if(a < -mod || a >= mod) {a %= mod;}
      if(a < 0) {a += mod;}
}

void add(ll &a, ll b) {
      norm(a);
      norm(b);

      a += b;

      norm(a);
}

void mul(ll &a, ll b) {
      norm(a);
      norm(b);

      a *= b;

      norm(a);
}

// (x ^ y) % mod in O(log y).
ll power(ll x, unsigned int y) {
      if(y == 0) {return 1;}
      ll res = 1;
      x %= mod;
      if(x == 0) {return 0;}
      while(y > 0) {
            if(y & 1) {
                  mul(res, x);
            }
            y = y >> 1;
            mul(x, x);
      }
      return res;
}

void mod_div(ll &a, ll b) {
      // (a/= b ) % mod
      norm(a);
      norm(b);

      ll inv_b = power(b, mod - 2);
      mul(a, inv_b);

      norm(a);
}

void NT_init() {
      fac[0] = 1; inv_fac[0] = 1; mod_div(inv_fac[0], fac[0]);
      for(ll i = 1; i < MAXN; i++) {
            fac[i] = fac[i-1];
            mul(fac[i], i);
            inv_fac[i] = 1;
            mod_div(inv_fac[i], fac[i]);
      }
}

ll NcR(ll n, ll r) {
      if(n < r) {return 0;}
      if(r == 0) {return 1;}
      ll ans = fac[n];
      mul(ans, inv_fac[r]);
      mul(ans, inv_fac[n-r]);
      return ans;
}

// void solve() {
//       ll n, m, k; cin >> n >> m >> k;
//       // cout << n << endl;
      
//       ll tot = NcR(n, 2);
//       // cout << "tot: " << tot << endl;

//       ll f_tot = 0;
//       for(ll i = 0; i < m; i++) {
//             ll a, b, f; cin >> a >> b >> f;
//             add(f_tot, f);
//       }

//       ll base = k;
//       mul(base, f_tot);
//       mod_div(base, tot);

//       // cout << k << " " << f_tot << " | tot: " << tot << " " << base << endl;

//       ll avg_inc = 0;

//       for(ll i = 1; i <= k; i++) {

//             ll sum = i*(i-1)/2;
//             sum %= mod;

//             ll prob = NcR(k, i);

//             ll pick = 1;
//             mod_div(pick, tot);
//             pick = power(pick, i);

//             ll dont_pick = tot - 1;
//             mod_div(dont_pick, tot);
//             dont_pick = power(dont_pick, k - i);

            
//             mul(prob, pick);
//             mul(prob, dont_pick);

//             ll temp = sum;
//             mul(temp, prob);

//             add(avg_inc, temp);

//             // cout << sum << " " << prob << " " << pick << " " << dont_pick << " " << avg_inc << endl;
//       }
//       // cout << endl;

//       mul(avg_inc, m);  

//       ll ans = base;
//       add(ans, avg_inc);

//       cout << ans << endl;
//       // cout << "=======" << endl;

// }

// /*ngu, lesgo*/
// int32_t main() {
//       ios_base::sync_with_stdio(false);cin.tie(0); cout.tie(0);

      NT_init();

//       int TT=1;
//       cin>>TT; //comment out this line if only 1 test case is needed
//       while(TT--) {solve();}
//       return 0;
// }
 
