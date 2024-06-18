// https://codeforces.com/contest/1821/submission/203626535 [pasted below]
// https://codeforces.com/contest/1821/problem/F

#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string(string(s)); }
string to_string(bool b) { return to_string(int(b)); }
string to_string(vector<bool>::reference b) { return to_string(int(b)); }
string to_string(char b) { return "'" + string(1, b) + "'"; }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
	return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}
template <typename A, typename T = typename A::value_type>
string to_string(A v) {
	string res = "{";
	for (const auto& x : v) res += (res == "{" ? "" : ", ") + to_string(x);
	return res + "}";
}
void debug() { cerr << endl; }
template <typename Head, typename... Tail>
void debug(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug(T...);
}
#define db(...) cerr << "[" << #__VA_ARGS__ << "]:", debug(__VA_ARGS__)
#else
#define db(...) 42
#endif
using ll = long long;
using ld = long double;
const int MOD = 998244353; // 2^23 * 119 + 1
struct Mint {
	int val;
	Mint() { val = 0; }
	Mint(ll x) {
		val = (-MOD <= x && x < MOD) ? x : x % MOD;
		if (val < 0) val += MOD;
	}
	template <typename U>
	explicit operator U() const { return (U)val; }
	friend bool operator==(const Mint& a, const Mint& b) { return a.val == b.val; }
	friend bool operator!=(const Mint& a, const Mint& b) { return !(a == b); }
	friend bool operator<(const Mint& a, const Mint& b) { return a.val < b.val; }
	Mint& operator+=(const Mint& m) { if ((val += m.val) >= MOD) val -= MOD; return *this; }
	Mint& operator-=(const Mint& m) { if ((val -= m.val) < 0) val += MOD; return *this; }
	Mint& operator*=(const Mint& m) { val = (ll)val * m.val % MOD; return *this; }
	friend Mint modex(Mint a, ll p) {
		assert(p >= 0);
		Mint ans = 1;
		for (; p; p >>= 1) {
			if (p & 1) ans *= a;
			if (p > 1) a *= a;
		}
		return ans;
	}
	Mint& operator/=(const Mint& m) { return *this *= modex(m, MOD - 2); }
	Mint& operator++() { return *this += 1; }
	Mint& operator--() { return *this -= 1; }
	Mint operator++(int) { Mint result(*this); *this += 1; return result; }
	Mint operator--(int) { Mint result(*this); *this -= 1; return result; }
	Mint operator-() const { return Mint(-val); }
	friend Mint operator+(Mint a, const Mint& b) { return a += b; }
	friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
	friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
	friend Mint operator/(Mint a, const Mint& b) { return a /= b; }
	friend ostream& operator<<(ostream& os, const Mint& x) { return os << x.val; }
	friend string to_string(const Mint& b) { return to_string(b.val); }
};
namespace fft {
#define NTT
const Mint gen = 3; // ord(3) = 2^23 * 119
vector<int> rev(1, 0); // rev has [base] bits
vector<Mint> roots;
int base = 0;
void precompute(int nbase) {
	if (nbase <= base) return;
	rev.resize(1 << nbase);
	for (int i = 0; i < (1 << nbase); ++i) {
		rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (nbase - 1));
	}
	roots.resize(1 << nbase);
	for (; base < nbase; ++base) {
		int len = 1 << base;
		Mint root = modex(gen, (MOD - 1) >> (base + 1));
		roots[len] = 1;
		for (int i = 1; i < len; ++i) roots[len + i] = roots[len + i - 1] * root;
	}
}
void fft(vector<Mint>& a) {
	int n = a.size();
	assert((n & (n - 1)) == 0);
	int zeros = __builtin_ctz(n);
	precompute(zeros);
	int shift = base - zeros;
	for (int i = 0; i < n; ++i) {
		if (i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
	}
	for (int len = 1; len < n; len <<= 1)
		for (int i = 0; i < n; i += 2 * len)
			for (int j = 0; j < len; ++j) {
				Mint u = a[i + j], v = a[i + j + len] * roots[len + j];
				a[i + j] = u + v;
				a[i + j + len] = u - v;
			}
}
vector<Mint> multiply(vector<Mint> a, vector<Mint> b) {
	if (a.empty() || b.empty()) return {};
	int sz = a.size() + b.size() - 1;
	int n = sz == 1 ? 1 : 1 << (32 - __builtin_clz(sz - 1));
	bool eq = (a == b);
	a.resize(n);
	fft(a);
	if (eq) b = a;
	else {
		b.resize(n);
		fft(b);
	}
	Mint inv = Mint(1) / n;
	for (int i = 0; i < n; ++i) a[i] *= b[i] * inv;
	fft(a);
	reverse(a.begin() + 1, a.end());
	a.resize(sz);
	return a;
}
vector<Mint> multiply(const vector<Mint>& a, const vector<Mint>& b, int m) {
	assert(m == 998244353);
	return multiply(a, b);
}
}  // namespace fft
namespace polynomial {
template <typename T>
vector<T>& operator+=(vector<T>& a, const vector<T>& b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); ++i) a[i] += b[i];
	return a;
}
template <typename T>
vector<T> operator+(vector<T> a, const vector<T>& b) {
	return a += b;
}
template <typename T>
vector<T>& operator-=(vector<T>& a, const vector<T>& b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); ++i) a[i] -= b[i];
	return a;
}
template <typename T>
vector<T> operator-(vector<T> a, const vector<T>& b) {
	return a -= b;
}
template <typename T>
vector<T> operator-(vector<T> a) {
	for (int i = 0; i < a.size(); ++i) a[i] = -a[i];
	return a;
}
template <typename T>
vector<T> operator+=(vector<T>& a, const T& b) {
	for (int i = 0; i < a.size(); ++i) a[i] += b;
	return a;
}
template <typename T>
vector<T> operator-=(vector<T>& a, const T& b) {
	for (int i = 0; i < a.size(); ++i) a[i] -= b;
	return a;
}
template <typename T>
vector<T> operator*=(vector<T>& a, const T& b) {
	for (int i = 0; i < a.size(); ++i) a[i] *= b;
	return a;
}
template <typename T>
vector<T> operator/=(vector<T>& a, const T& b) {
	for (int i = 0; i < a.size(); ++i) a[i] /= b;
	return a;
}
template <typename T>
vector<T> operator+(vector<T> a, const T& b) { return a += b; }
template <typename T>
vector<T> operator-(vector<T> a, const T& b) { return a -= b; }
template <typename T>
vector<T> operator*(vector<T> a, const T& b) { return a *= b; }
template <typename T>
vector<T> operator/(vector<T> a, const T& b) { return a /= b; }
template <typename T>
vector<T> operator*(const vector<T>& a, const vector<T>& b) {
	if (a.empty() || b.empty()) return {};
	if (min(a.size(), b.size()) < 40) {
		vector<T> c(a.size() + b.size() - 1);
		for (int i = 0; i < a.size(); ++i) {
			for (int j = 0; j < b.size(); ++j) {
				c[i + j] += a[i] * b[j];
			}
		}
		return c;
	}
	return fft::multiply(a, b, MOD);
}
template <typename T>
vector<T>& operator*=(vector<T>& a, const vector<T>& b) {
	return a = a * b;
}
/* Invert a power series mod x^n, where f[0] != 0
P[2n] = P[n](2 - f * P[n]) mod x^(2n). O(n log n).
For FFT precision: if using double, ensure a.size <= 530,000. */
vector<Mint> inverse(const vector<Mint>& a) {
#ifdef NTT
	assert(!a.empty() && a[0] != 0);
	int n = a.size();
	vector<Mint> b = {1 / a[0]};
	for (int m = 2; b.size() < n; m <<= 1) {
		vector<Mint> aCut(a.begin(), a.begin() + min(n, m));
		aCut.resize(2 * m);
		b.resize(2 * m);
		fft::fft(aCut);
		fft::fft(b);
		for (int i = 0; i < 2 * m; ++i) {
			b[i] *= 2 - aCut[i] * b[i];
		}
		fft::fft(b);
		reverse(b.begin() + 1, b.end());
		b.resize(m);
		Mint inv = Mint(1) / (2 * m);
		b *= inv;
	}
	b.resize(n);
	return b;
#else
	assert(!a.empty() && a[0] != 0);
	int n = a.size();
	vector<Mint> b = {1 / a[0]};
	for (int m = 2; b.size() < n; m <<= 1) {
		vector<Mint> aCut(a.begin(), a.begin() + min(n, m));
		auto x = aCut * (b * b);
		b.resize(m);
		for (int i = 0; i < m; ++i) {
			b[i] += b[i] - x[i];
		}
	}
	b.resize(n);
	return b;
#endif
}
/* Polynomial division: divide A (<= deg n) by B (deg m)
A(x) = Q(x)B(x) + R(x), deg Q <= n-m. Substitute x = 1/x.
x^nA(1/x) = (x^(n-m)Q(1/x))(x^mB(1/x)) + x^(n-m+1)(x^(m-1)R(1/x))
Note x^deg * poly(1/x) = poly_reverse(x).
So A_rev(x) = Q_rev(x)B_rev(x) mod x^(n-m+1).
So we can recover Q, since deg Q_rev <= n-m.
Resulting size is max(0, n-m+1).
O(n log n) */
vector<Mint>& operator/=(vector<Mint>& a, vector<Mint> b) {
	assert(!b.empty() && b.back() != 0);
	int n = a.size();
	int m = b.size();
	if (n < m) {
		a.clear();
		return a;
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	b.resize(n - m + 1);
	a *= inverse(b);
	a.erase(a.begin() + n - m + 1, a.end());
	reverse(a.begin(), a.end());
	return a;
}
vector<Mint> operator/(vector<Mint> a, const vector<Mint>& b) {
	return a /= b;
}
/* O(n log n) where n = a.size(). Returned poly has no leading zeros. */
vector<Mint>& operator%=(vector<Mint>& a, const vector<Mint>& b) {
	a -= b * (a / b);
	while (!a.empty() && a.back() == 0) a.pop_back();
	return a;
}
vector<Mint> operator%(vector<Mint> a, const vector<Mint>& b) {
	return a %= b;
}
vector<Mint> gcd(vector<Mint> a, vector<Mint> b) {
	while (!b.empty()) {
		auto c = b;
		b = a % b;
		swap(a, c);
	}
	return a;
}
/* Calculate integral with c=0. Returned size = a.size() + 1. */
vector<Mint> integral(const vector<Mint>& a) {
	vector<Mint> ret(a.size() + 1);
	for (int i = 1; i < ret.size(); ++i) {
		ret[i] = a[i - 1] / i;
	}
	return ret;
}
/* Returned size = max(0, a.size() - 1). */
vector<Mint> derivative(const vector<Mint>& a) {
	if (a.empty()) return a;
	vector<Mint> ret(a.size() - 1);
	for (int i = 0; i + 1 < a.size(); ++i)
		ret[i] = a[i + 1] * (i + 1);
	return ret;
}
/* Calculate log(f) mod x^n, where f[0] == 1. ret[0] == 0. O(n log n) */
vector<Mint> logarithm(const vector<Mint>& a) {
	assert(!a.empty() && a[0] == 1);
	auto ret = integral(derivative(a) * inverse(a));
	ret.resize(a.size());
	return ret;
}
/* Calculate exp(f) mod x^n, where f[0] == 0. ret[0] == 1.
P[2n] = P[n](1 - log(P[n]) + f) mod x^(2n)
O(n log n) */
vector<Mint> exponent(const vector<Mint>& a) {
	assert(!a.empty() && a[0] == 0);
	int n = a.size();
	vector<Mint> b = {1};
	for (int m = 2; b.size() < n; m <<= 1) {
		vector<Mint> x(a.begin(), a.begin() + min((int)a.size(), m));
		++x[0];
		auto oldB = b;
		b.resize(m);
		b = oldB * (x - logarithm(b));
		b.resize(m);
	}
	b.resize(n);
	return b;
}
/* Multipoint evaluation: Evaluate A (deg d) at n points xs modulo MOD.
Key idea: A(x_i) = A(x) mod (x - x_i).
Calculate A mod (x-x_l)...(x-x_r) for range [l,r].
O(n log^2 n + d log d) */
vector<Mint> multipoint(const vector<Mint>& a, vector<Mint> xs) {
	int n = xs.size();
	vector<vector<Mint>> prods(2 * n - 1);
	function<void(int, int, int)> getProds = [&](int sn, int s, int e) {
		if (s == e) {
			prods[sn] = {-xs[s], 1};
			return;
		}
		int m = (s + e) >> 1, lsn = sn + 1, rsn = sn + ((m - s + 1) << 1);
		getProds(lsn, s, m);
		getProds(rsn, m + 1, e);
		prods[sn] = prods[lsn] * prods[rsn];
	};
	getProds(0, 0, n - 1);
	function<void(int, int, int, const vector<Mint>&)> calc = [&](int sn, int s, int e, const vector<Mint>& f) {
		if (s == e) {
			xs[s] = f.empty() ? 0 : f[0];
			return;
		}
		int m = (s + e) >> 1, lsn = sn + 1, rsn = sn + ((m - s + 1) << 1);
		calc(lsn, s, m, f % prods[lsn]);
		calc(rsn, m + 1, e, f % prods[rsn]);
	};
	calc(0, 0, n - 1, a);
	return xs;
}
/* Given a polynomial A and generator g, evaluate Y[k] = A(g^k mod MOD) for all 0 <= k < n.
A(g^(2k)) = sum_i a_i * g^(2ki)
A(g^(2k+1)) = sum_i a_i * g^i * g^(2ki)
Chirp z-transform: g^(2ki) = g^(kk) g^(ii) g^(-(k-i)^2); so we can convolve.
O(MOD + (n + deg A) log (n + deg A)) */
vector<Mint> chirpz(vector<Mint> a, Mint g, int n) {
	int d = a.size();
	int phi = MOD - 1;
	vector<Mint> pw(phi + 1);
	pw[0] = 1;
	for (int i = 1; i <= phi; ++i) pw[i] = pw[i - 1] * g;
	auto chirpzEven = [&](const vector<Mint>& b, int m) {
		vector<Mint> u(d), v(m + d - 1);
		for (int i = 0; i < d; ++i) {
			u[i] = b[i] * pw[(ll)i * i % phi];
		}
		for (int i = -(d - 1); i < m; ++i) {
			v[d - 1 + i] = pw[phi - (ll)i * i % phi];
		}
		auto z = u * v;
		vector<Mint> ret(m);
		for (int i = 0; i < m; ++i) {
			ret[i] = pw[(ll)i * i % phi] * z[d - 1 + i];
		}
		return ret;
	};
	auto even = chirpzEven(a, (n + 1) >> 1);
	for (int i = 0; i < d; ++i) a[i] *= pw[i % phi];
	auto odd = chirpzEven(a, n >> 1);
	vector<Mint> ret(n);
	for (int i = 0; i < n; ++i) {
		ret[i] = (i & 1) ? odd[i >> 1] : even[i >> 1];
	}
	return ret;
}
/* Compute A^p mod B in O(b log b log p). Returned poly has no leading zeros. */
vector<Mint> powerMod(const vector<Mint>& a, ll p, const vector<Mint>& b) {
	if (!p) return {1};
	vector<Mint> c;
	if (p & 1) {
		c = powerMod(a, p - 1, b) * a;
	} else {
		c = powerMod(a, p >> 1, b);
		c *= c;
	}
	return c % b;
}
/* Compute A^p mod x^n in O(n log n) using exp/log. p <= LLONG_MAX, n <= INT_MAX.
A has deg < n. Result has size n. */
vector<Mint> power(vector<Mint> a, ll p, int n) {
	if (!n) return {};
	if (!p) {
		vector<Mint> ret(n);
		ret[0] = 1;
		return ret;
	}	
	assert(n > 0 && p > 0 && a.size() <= n);
	int m = 0;
	while (m < a.size() && a[m] == 0) ++m;
	if (m - 1 >= (n - 1) / p) return {}; // equiv to mp >= n
	a.erase(a.begin(), a.begin() + m);
	Mint inv = 1 / a[0];
	Mint c = modex(a[0], p);
	a *= inv;
	a = logarithm(a);
	Mint q = p;
	a *= q;
	a = exponent(a);
	a.insert(a.begin(), m * p, 0);
	a.resize(n);
	a *= c;
	return a;
}
/* Compute A^p in O(m log m + log p), where m = p*deg(A). Result has size m+1 and deg m (ignoring A={} cases). */
vector<Mint> power(vector<Mint> a, int p) {
	assert(p >= 0);
	vector<Mint> ret = {1};
	for (; p; p >>= 1) {
		if (p & 1) ret *= a;
		if (p > 1) a *= a;
	}
	return ret;
}
vector<Mint> multiplyAll(const vector<vector<Mint>>& polys, int s, int e) {
	if (s == e) return polys[s];
	int m = (s + e) >> 1;
	auto a = multiplyAll(polys, s, m);
	auto b = multiplyAll(polys, m + 1, e);
	return a * b;
}
/* Multiply n polynomials of total deg d in O(n log d + d log d log n). If d <= 1 then it's O(n).
If no poly is empty, then resulting polynomial has size exactly sum(poly.size()-1)+1. Else size is 0. */
vector<Mint> multiplyAll(const vector<vector<Mint>>& polys) {
	return polys.empty() ? vector<Mint>{1} : multiplyAll(polys, 0, polys.size() - 1);
}
/* Returns S[0..p]: S[t] = 1^t + 2^t + ... + m^t.
0 <= m. 0 <= p < min(MOD-1, INT_MAX-1). O(log(MOD) + p log(p)). [exp(x) - exp((m+1)x)] / [1 - exp(x)]
If only fixed p is needed, interpolate on S[p]=deg (p+1)-poly is much faster. */
vector<Mint> sumConsecutivePowers(ll m, int p) {
	assert(m >= 0 && p >= 0);
	vector<Mint> ex(p + 2);
	Mint v = 1;
	for (int i = 1; i <= p + 1; ++i) v *= i;
	v = 1 / v;
	for (int i = p + 1; i >= 0; --i) {
		ex[i] = v;
		v *= i;
	}
	auto denom = -ex;
	denom.erase(denom.begin());
	vector<Mint> num(p + 1);
	Mint mult = Mint(m) + 1;
	v = 1;
	for (int i = 0; i <= p; ++i) {
		v *= mult;
		num[i] = ex[i + 1] * (1 - v);
	}
	auto S = num * inverse(denom);
	S.resize(p + 1);
	v = 1;
	for (int i = 0; i <= p; ++i) {
		S[i] *= v;
		v *= i + 1;
	}
	return S;
}
}  // namespace polynomial
using namespace polynomial;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	ll rem = n - (ll)m * (k + 1);
	if (rem < 0) {
		cout << 0 << '\n';
		return 0;
	}
	vector<Mint> P(rem + 1, 1);
	for (int i = 0; i < min((int)rem + 1, k); ++i) P[i] = 2;
	auto res = power(P, m, rem + 1);
	Mint ans = accumulate(res.begin(), res.end(), Mint(0));
	cout << ans << '\n';
}
 
