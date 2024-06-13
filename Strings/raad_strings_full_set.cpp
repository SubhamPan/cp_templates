// https://codeforces.com/contest/1984/submission/265627622 (his submission link)

typedef long long ll;
ll mod = 1e9+7;


ll binexp(ll x , ll n){
        if(n == 0)return 1; 
        if(n == 1)return x%mod;
        ll y = binexp(x,n/2);
        if(n%2 == 0)return (y*y)%mod;
        else return (((y*y)%mod)*x)%mod;
}
 
ll modinv(ll x){
    return binexp(x,mod-2);
}
 
ll nCr(ll n,ll r){
    if(r < 0)return 0;
    if(r > n)return 0;
    if(r > n/2){r = n - r;}
    if(r == 0 || n == r)return 1;
    ll tot = 1;
    for(ll i = n;i>=n-r+1;i--){
        tot = (tot*i)%mod;
    }
    
    for(ll i = 2;i<=r;i++){
        tot = (tot*modinv(i))%mod;
    }
    return tot;
}

 
// -------------------------------------------------------------------------
// Below code is for computing prefix and suffix hashes 
vector<ll> inv;
vector<ll> bin;
 
//As I dont want to compute binexp and modinv everytime we use , I precomputed here for 53 
//53 is the hash prime number thing 
void precompute(ll n){
    inv.assign(n+1,0);
    bin.assign(n+1,0);
    bin[0] = 1;
    inv[0] = 1;
    ll inv2969 = modinv(2969);
    fr(n)bin[i+1] = (2969*bin[i])%mod;
    fr(n)inv[i+1] = (inv2969*inv[i])%mod;
}
 
//pre and suf return the prefix and suffix hash of a string
ll pre(ll l,ll r,ll prefix[]){
    if(l == 0)return prefix[r];
    else{
        return ((prefix[r]-prefix[l-1]+mod)*inv[l])%mod;
    }
}
 
ll suf(ll l,ll r,ll n,ll suffix[]){
    if(r == n-1)return suffix[l];
    else{
        return ((suffix[l]-suffix[r+1]+mod)*inv[n-r-1])%mod;
    }
}
 
//run this to precompute the total prefix and suffix hashes 
void compute(ll prefix[],ll suffix[],string& str,ll n){
    prefix[0] = (str[0]-'a');
    suffix[n-1] = (str[n-1]-'a'); 
    for(int i = 1;i<n;i++)prefix[i] = (prefix[i-1] + ((ll)(str[i]-'a'))*bin[i])%mod;
    for(int i = n-2;i>=0;i--)suffix[i] = (suffix[i+1] + ((ll)(str[i]-'a'))*bin[n-1-i])%mod;
    //computed
}
 
//checks whether string from l to r is a palindrome
bool palindrome_check(ll l,ll r,ll n,ll prefix[],ll suffix[]){
    return (pre(l,r,prefix) == suf(l,r,n,suffix));
}
//-----------------------------------------------------------------

void prefixfunction(string& s,int p[]){
    int n = s.length();
    for(int i = 1;i<n;i++){
        int j = p[i-1];
        while(s[i] != s[j] && j > 0){
            j = p[j-1];
        }
        if(s[i] == s[j])
            p[i] = j+1;
        else p[i] = j;
    }
}
 
void automaton(string& s,int p[],vector<vector<int>>& next){ //next needs to be n+1 long
    int n = s.length();
    for(int i = 0;i<=n;i++){
        for(int j = 0;j<26;j++){
            if(i > 0){
                if(i < n && 'a' + j == s[i])next[i][j] = i + 1;
                else next[i][j] = next[p[i-1]][j];
            }else{
                if('a' + j == s[i])
                    next[i][j] = 1; //i+1 th character match checked
                else next[i][j] = 0;
            }
        }
    }
}

