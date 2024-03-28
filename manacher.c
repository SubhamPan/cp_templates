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
