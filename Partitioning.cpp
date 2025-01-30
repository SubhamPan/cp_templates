// https://atcoder.jp/contests/abc390/tasks/abc390_d
// https://atcoder.jp/contests/abc390/submissions/62099092

/*
The provided code is attempting to solve a problem involving partitioning a set of bags of stones and computing the bitwise XOR of the sums of stones in each partition. Here's a breakdown of what the code is doing:
1. **Input Reading**: The code reads the number of bags \( N \) and the number of stones \( A_i \) in each bag.
2. **Partitioning**: The `Partitioning` class contains a method `GetAllPartitions` that generates all possible ways to partition the set of bags into non-empty subsets. This is done by manipulating indexes and lists to generate different combinations of partitions.
3. **XOR Calculation**: For each partition, the code calculates the sum of stones in each subset of the partition and then computes the bitwise XOR of these sums. This result is stored in a global vector `yay`.
4. **Unique Values Counting**: After generating all possible partitions and their corresponding XOR values, the code sorts the `yay` vector and counts the number of unique XOR values.
5. **Output**: Finally, the code prints the count of unique XOR values.

### Detailed Explanation of `GetAllPartitions` Method:
- **Initialization**: The method starts by initializing a list of lists (`lists`) with the original elements (stones in bags).
- **Loop for Partitions**: The method enters a loop where it continuously generates new partitions by manipulating the indexes and lists:
  - It calculates the XOR of the sums of stones in each subset of the current partition and stores it in `yay`.
  - It then adjusts the indexes to generate the next partition. This involves popping elements from lists and pushing them into new or existing lists to form different combinations.
- **Termination**: The loop terminates when no more partitions can be generated, and the method returns the result.

### Issues and Improvements:
- **Efficiency**: The current implementation may not be efficient for larger values of \( N \) due to the exhaustive generation of all partitions.
- **Correctness**: The method `GetAllPartitions` seems to have logical issues in generating partitions correctly, which might lead to incorrect results.
- **Global Variable**: The use of a global vector `yay` is not ideal. It would be better to pass it as a parameter or handle it within the method.

### Conclusion:
The code aims to solve the problem by generating all possible partitions of the bags and computing the unique XOR values of the sums of stones in each partition. However, the implementation may need improvements for correctness and efficiency.
*/


#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <set>

#define int long long

using namespace std;

vector<int> yay;
class Partitioning {
public:
    template<typename T>
    static std::vector<std::vector<std::vector<T>>> GetAllPartitions(const std::vector<T>& elements) {
        std::vector<std::vector<T>> lists;
        std::vector<int> indexes(elements.size());
        lists.push_back(std::vector<T>(elements.begin(), elements.end()));
        std::vector<std::vector<std::vector<T>>> result;

        while (true) {
            int god = 0;
            for(auto &vec: lists)
            {
                int sum = 0;
                for(auto it: vec) sum += it;
                god ^= sum;
            }
            yay.push_back(god);
            int i, index;
            for (i = indexes.size() - 1;; --i) {
                if (i <= 0)
                    return result;
                index = indexes[i];
                lists[index].pop_back();
                if (!lists[index].empty())
                    break;
                lists.erase(lists.begin() + index);
            }
            ++index;
            if (index >= lists.size())
                lists.push_back(std::vector<T>());
            for (; i < indexes.size(); ++i) {
                indexes[i] = index;
                lists[index].push_back(elements[i]);
                index = 0;
            }
        }
    }
};

signed main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto &i: arr) cin >> i;
    auto list = Partitioning::GetAllPartitions(arr);
    sort(yay.begin(), yay.end());
    int cnt = 1;
    for(int i = 1; i < yay.size(); i++)
    {
        if(yay[i] != yay[i - 1]) cnt++;
    }
    cout << cnt << '\n';
    return 0;
}

