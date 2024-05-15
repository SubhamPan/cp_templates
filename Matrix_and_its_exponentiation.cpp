
// Example usage: https://codeforces.com/contest/1970/submission/259665402


template <typename T>
class Mat
{
public:
    vector<vector<T>> mat;
    int n, m;
 
    Mat(int n, int m)
    {
        this->n = n;
        this->m = m;
        mat.resize(n, vector<T>(m, 0));
    }
 
    Mat operator*(Mat &other)
    {
        Mat res(n, other.m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < other.m; j++)
            {
                for (int k = 0; k < m; k++)
                {
                    res.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        return res;
    }
 
    Mat operator^(int e)
    {
        Mat res(n, m);
        for (int i = 0; i < n; i++)
            res.mat[i][i] = 1;
        Mat base = *this;
        while (e)
        {
            if (e & 1)
                res = res * base;
            base = base * base;
            e >>= 1;
        }
        return res;
    }
};
