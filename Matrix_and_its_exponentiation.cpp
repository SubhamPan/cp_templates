
// Example usage: https://codeforces.com/contest/1970/submission/261025104



 
template <typename T>
class Mat {
public:
    vector<vector<T>> mat;
    int n, m;
 
    Mat(int n, int m) {
        this->n = n;
        this->m = m;
        mat.resize(n, vector<T>(m, 0));
    }
 
    Mat operator*(Mat &other) {
        Mat res(n, other.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < other.m; j++) {
                for (int k = 0; k < m; k++) {
                    res.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        return res;
    }
    
    // power/expoenetiation - (base matrix raised to the power e)
    Mat operator^(int e) {
        Mat res(n, m);
        for (int i = 0; i < n; i++)
            res.mat[i][i] = 1;

        Mat base = *this;

        // binary exponentiation concept:
        while (e) {
            if (e & 1)
                res = res * base;
            base = base * base;
            e >>= 1;
        }
        return res;
    }
};

// Mat<ll> mat(n, n);

// Example usage: [here Z is modulo int wala struct that i(pan) use]
// Mat<Z> mat(m, m);
// for(int i = 0; i < m; i++) {
//   for(int j = 0; j < m; j++) {
//       mat.mat[i][j] = s[i]*l[j] + l[i]*s[j] + s[i]*s[j]; // needs to take at least one short path
//   }
// }

// Mat<Z> result = mat ^ n; // raise it to the nth power

// Z ans = 0;
// for(int i = 0; i < m; i++) {ans += result.mat[i][0];}
// cout << ans << endl;
 
