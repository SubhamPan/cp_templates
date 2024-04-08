
// shadow orz
vector<int> manacher_odd(string s){
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0LL, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
pair<vector<int>,vector<int>> manacher(string s){
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    res = vector<int>(begin(res) + 1, end(res) - 1);
    vector<int> d1(s.size()),d2(s.size());
    for(int i = 0; i < (int)s.size(); i++){
        d1[i] = res[2*i] / 2;
        if(i){
            d2[i] = (res[2*i - 1] - 1) / 2;
        }
    }
    return {d1,d2};
}
/*
d1[i] = number of odd-length palindromes centered at i
d2[i] = number of even-length palindromes centered at (i-1,i)
// [not exactly number, check the is_palin lamda function for more clarity]

Example
s = a {b a _b_ a b} c
 
d1[3] = 3
 
s = c {b a _a_ b} d
 
d2[3] = 2
*/

// EXample usage:
// split a string s into substrings that are not palindromes.

void solve() {

    string s; cin >> s;
    int n = s.size();

    auto [d1, d2] = manacher(s);

    auto is_palin = [&](int L, int R) -> bool {
        // substr = [L, R] (both inclusive).
        int len = (R - L + 1);
        int center = (L + R + 1) / 2;

        if(len % 2 == 1) {
            int mx_pal_len = (2 * d1[center]) - 1;
            return len <= mx_pal_len;
        } else {
            int mx_pal_len = (2 * d2[center]);
            return len <= mx_pal_len;
        }
    };


    if(is_palin(0, n-1) == false) {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << s << endl;
        return;
    }

    for(int i = 0; i < n-1; i++) {
        // i is ending point of first substr
        if(is_palin(0, i) == true || is_palin(i+1, n-1) == true) {
            continue;
        }

        cout << "YES" << endl;
        cout << 2 << endl;
        cout << s.substr(0, i+1) << " " << s.substr(i+1, n - (i+1)) << endl;
        return;
    }

    cout << "NO" << endl;
    
    // cout<<"===="<<endl;

}








// =====================================================================================================================

// ecnerwala orz
/**
 * manacher(S): return the maximum palindromic substring of S centered at each point
 *
 * Input: string (or vector) of length N (no restrictions on character-set)
 * Output: vector res of length 2*N+1
 *   For any 0 <= i <= 2*N:
 *   * i % 2 == res[i] % 2
 *   * the half-open substring S[(i-res[i])/2, (i+res[i])/2) is a palindrome of length res[i]
 *   * For odd palindromes, take odd i, and vice versa
 */
template <typename V> std::vector<int> manacher(const V& S) {
    int N = (int)(S.size());
    std::vector<int> res(2*N+1, 0);
    for (int i = 1, j = -1, r = 0; i < 2*N; i++, j--) {
        if (i > r) {
            r = i+1, res[i] = 1;
        } else {
            res[i] = res[j];
        }
        if (i+res[i] >= r) {
            int b = r>>1, a = i-b;
            while (a > 0 && b < N && S[a-1] == S[b]) {
                a--, b++;
            }
            res[i] = b-a, j = i, r = b<<1;
        }
    }
    return res;
}

    // in void solve(): for a string 's'.
    vector<int> max_pal = manacher(s);

    // checking if len = "len" is a palindrome or not. [len = r-l+1].
    // i.e. checking if s[l,r] is a palindrome or not.
    if(len % 2 == 0) {
        if(max_pal[2 * cdiv(l+r, 2)] >= len) {
            ans -= len;
        }
    } else {
        if(max_pal[2 * cdiv(l+r, 2) + 1] >= len) {
            ans -= len;
        }
    }





// ababa
// the vector max_pal = manacher("ababa") will store:
// index: 0; center: 0| borders: 0 and 0| subtring: ; max palindrome len: 0
// index: 1; center: 0| borders: 0 and 1| subtring: a; max palindrome len: 1
// index: 2; center: 1| borders: 1 and 1| subtring: ; max palindrome len: 0
// index: 3; center: 1| borders: 0 and 3| subtring: aba; max palindrome len: 3
// index: 4; center: 2| borders: 2 and 2| subtring: ; max palindrome len: 0
// index: 5; center: 2| borders: 0 and 5| subtring: ababa; max palindrome len: 5
// index: 6; center: 3| borders: 3 and 3| subtring: ; max palindrome len: 0
// index: 7; center: 3| borders: 2 and 5| subtring: aba; max palindrome len: 3
// index: 8; center: 4| borders: 4 and 4| subtring: ; max palindrome len: 0
// index: 9; center: 4| borders: 4 and 5| subtring: a; max palindrome len: 1
// index: 10; center: 5| borders: 5 and 5| subtring: ; max palindrome len: 0

// abbab
// the vector max_pal = manacher("ababa") will store:
// index: 0; center: 0| borders: 0 and 0| subtring: ; max palindrome len: 0
// index: 1; center: 0| borders: 0 and 1| subtring: a; max palindrome len: 1
// index: 2; center: 1| borders: 1 and 1| subtring: ; max palindrome len: 0
// index: 3; center: 1| borders: 1 and 2| subtring: b; max palindrome len: 1
// index: 4; center: 2| borders: 0 and 4| subtring: abba; max palindrome len: 4
// index: 5; center: 2| borders: 2 and 3| subtring: b; max palindrome len: 1
// index: 6; center: 3| borders: 3 and 3| subtring: ; max palindrome len: 0
// index: 7; center: 3| borders: 2 and 5| subtring: bab; max palindrome len: 3
// index: 8; center: 4| borders: 4 and 4| subtring: ; max palindrome len: 0
// index: 9; center: 4| borders: 4 and 5| subtring: b; max palindrome len: 1
// index: 10; center: 5| borders: 5 and 5| subtring: ; max palindrome len: 0
