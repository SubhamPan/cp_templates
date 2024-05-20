 /* z[i] = the greatest number of characters starting from the position 'i' that coincide with the first characters of s (string). */
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        // optimization case:
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        // trivial case:
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }

    }
    z[0] = n;
    return z;
}

// https://codeforces.com/contest/1968/submission/261762556
