/* The provided code defines a C++ struct template SmartSet that implements a data structure similar to a multiset, but with some additional features. 
    It maintains two multisets (big and small) and keeps track of the sum of elements in each set (sumBig and sumSmall). The elements are assumed to be of type T, which is a template parameter.

Here's a brief explanation of each function and member variable:

Constructor: Initializes big, small, sumBig, and sumSmall.
size(): Returns the total number of elements in both big and small multisets.
normalizeSmall(int k): Adjusts the sizes of big and small multisets such that the size of small becomes k. It moves elements between big and small to ensure that small contains the smallest k elements.
insert(T x): Inserts element x into either big or small based on its value. If x is less than the smallest element in big, it goes to small; otherwise, it goes to big.
erase(T x): Removes element x from either big or small based on its value.
getSumSmall(int k): Returns the sum of the smallest k elements in the data structure after adjusting the multisets.
getSumBig(int k): Returns the sum of the largest k elements in the data structure after adjusting the multisets.
clear(): Clears the contents of the data structure.
*/

/*
https://codeforces.com/contest/1936/submission/248919814
*/  

// with the smartset (or rather smart-multiset), you can:
// insert, erase (just like a normal multiset)
// but you can also ask for the [sum] of the [smallest / biggest] 'k' elements in the multiset in O(log n).
// [sum] and [smallest/biggest] can be modified according to our needs.

template<typename T> struct SmartSet {
	multiset<T> big, small;
	T sumBig, sumSmall;
 
	SmartSet() : big(), small(), sumBig(), sumSmall() {}
 
	int size() const {
		return (int)small.size() + (int)big.size();
	}
	void normalizeSmall(int k) {
		k = max(0, min(k, size()));
		while((int)small.size() > k) {
			auto it = prev(small.end());
			sumSmall -= *it;
			sumBig += *it;
			big.insert(*it);
			small.erase(it);
		}
		while((int)small.size() < k) {
			auto it = big.begin();
			sumBig -= *it;
			sumSmall += *it;
			small.insert(*it);
			big.erase(it);
		}
	}
	void insert(T x) {
		if (big.empty() || x < *big.begin()) {
			small.insert(x);
			sumSmall += x;
		} else {
			big.insert(x);
			sumBig += x;
		}
	}

	// erase only erases ONE particular occurrence of 'x' from the smartset
	void erase(T x) {
		if (big.find(x) != big.end()) {
			big.erase(big.find(x));
			sumBig -= x;
		} else if (small.find(x) != small.end()) {
			small.erase(small.find(x));
			sumSmall -= x;
		} else {
			assert(false);
		}
	}
	T getSumSmall(int k) {
		normalizeSmall(k);
		assert((int)small.size() == k);
		return sumSmall;
	}
	T getSumBig(int k) {
		normalizeSmall(size() - k);
		assert((int)big.size() == k);
		return sumBig;
	}
	void clear() {
		sumSmall = sumBig = 0;
		small.clear();
		big.clear();
	}
};
