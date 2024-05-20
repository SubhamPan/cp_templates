 
vector<int> z_function(const string& s) {
	const int n = s.size();
	vector<int> z(n);
	int opt = 0;
	for (int i = 1; i < n; ++i) {
		if (i < opt + z[opt]) {
			z[i] = min(z[i - opt], opt + z[opt] - i);
		}
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
			++z[i];
		}
		if (opt + z[opt] < i + z[i]) {
			opt = i;
		}
	}
	z[0] = n;
	return z;
}
