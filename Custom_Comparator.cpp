/* Lambda in Sorting Algorithms (std::sort):

The lambda function is used directly in the call to std::sort to sort the vector v in descending order.
This approach is suitable for temporary, one-time sorting operations.



Custom Comparator in Containers (std::set):

The lambda function defines a custom comparator for sorting elements in descending order.
The decltype(comp) specifies the type of the comparator, which is necessary for defining the set s with a custom comparator.
This approach ensures the set maintains the specified order throughout its lifetime.
*/



vector<int> v = {5, 2, 9, 1, 5, 6};
// Sort in descending order using a lambda function as a custom comparator
sort(v.begin(), v.end(), [](int x, int y) -> bool {
  return x > y;
});
// Print sorted vector
for (int num : v) {std::cout << num << " ";}
// 9 6 5 5 2 1

// -----------------------------------
auto comp = [](int a, int b) {
  return a > b; // Custom comparator for descending order
};

// Using decltype to declare a set with the custom comparator
std::set<int, decltype(comp)> s(comp);

// Insert elements into the set
s.insert(5);s.insert(2);s.insert(9);s.insert(1);s.insert(6);

// Print elements of the set
for (int num : s) {std::cout << num << " ";}
// 9 6 5 2 1


// =====================================================
//if you need a comparator function that has [&]; do this:
vector<set<ll>> leaves(n);
for (ll i = 0; i < n; i++) {
    if (g[i].size() == 1) {
        leaves[*g[i].begin()].insert(i);
    }
}

auto comp = [&](const auto& u, const auto& v) -> bool {
    if (leaves[u].size() == leaves[v].size()) return u < v;
    return leaves[u].size() > leaves[v].size();
};
// NOTE: do NOT put auto instead of ll in the following line:
std::function<bool(const ll&, const ll&)> comp_func = comp;
set<ll, decltype(comp_func)> st(comp_func);

for (ll i = 0; i < n; i++) {st.insert(i);}
// ===================

