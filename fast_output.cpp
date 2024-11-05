// https://atcoder.jp/contests/abc378/submissions/59357383
// used when you want to output a 128bit number.

static struct FastOutput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t buf_pos = 0;
  static constexpr int TMP_SIZE = 1 << 20;
  char tmp[TMP_SIZE];
  FILE *out = stdout;

  inline void put_char(char c) {
    buf[buf_pos++] = c;
    if (buf_pos == BUF_SIZE) {
      fwrite(buf, 1, buf_pos, out);
      buf_pos = 0;
    }
  }

  ~FastOutput() {
    fwrite(buf, 1, buf_pos, out);
  }

  inline FastOutput& operator<<(char c) {
    put_char(c);
    return *this;
  }

  inline FastOutput& operator<<(const char* s) {
    while (*s) {
      put_char(*s++);
    }
    return *this;
  }

  inline FastOutput& operator<<(const string& s) {
    for (int i = 0; i < (int) s.size(); i++) {
      put_char(s[i]);
    }
    return *this;
  }

  template <typename T>
  inline char* integer_to_string(T n) {
    // beware of TMP_SIZE
    char* p = tmp + TMP_SIZE - 1;
    if (n == 0) {
      *--p = '0';
    } else {
      bool is_negative = false;
      if (n < 0) {
        is_negative = true;
        n = -n;
      }
      while (n > 0) {
        *--p = (char) ('0' + n % 10);
        n /= 10;
      }
      if (is_negative) {
        *--p = '-';
      }
    }
    return p;
  }

  template <typename T>
  inline typename enable_if<is_integral<T>::value, char*>::type stringify(T n) {
    return integer_to_string(n);
  }

  #if !defined(_WIN32) || defined(_WIN64)
  inline char* stringify(__int128 n) {
    return integer_to_string(n);
  }
  #endif

  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, char*>::type stringify(T n) {
    sprintf(tmp, "%.17f", n);
    return tmp;
  }

  template <typename T>
  inline FastOutput& operator<<(const T& n) {
    auto p = stringify(n);
    for (; *p != 0; p++) {
      put_char(*p);
    }
    return *this;
  }
} fast_output;

#define cout fast_output


// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);
//   int n, m;
//   cin >> n >> m;
//   vector<int> a(n);
//   for (int i = 0; i < n; i++) {
//     cin >> a[i];
//   }
//   vector<int> pref(n + 1);
//   for (int i = 0; i < n; i++) {
//     pref[i + 1] = (pref[i] + a[i]) % m;
//   }
//   ordered_set<pair<int, int>> s;
//   __int128 ans = 0;
//   int64_t sum = 0;
//   for (int i = 0; i <= n; i++) {
//     auto key = make_pair(pref[i], i);
//     int add = int(s.size()) - int(s.order_of_key(key));
//     s.insert(key);
//     ans += int64_t(pref[i]) * i + int64_t(add) * m - sum;
//     sum += pref[i];
//   }
//   cout << ans << '\n';
//   return 0;
// }

