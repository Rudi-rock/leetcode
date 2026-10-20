#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isRotation(vector<int>& nums, vector<int>& sortedNums,
                    int start, int k) {
        vector<int> lps(k, 0);

        for (int i = 1, len = 0; i < k;) {
            if (sortedNums[start + i] == sortedNums[start + len]) {
                lps[i++] = ++len;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        int j = 0;

        for (int i = 0; i < 2 * k - 1; i++) {
            int value = nums[start + (i % k)];

            while (j > 0 && value != sortedNums[start + j]) {
                j = lps[j - 1];
            }

            if (value == sortedNums[start + j]) {
                j++;
            }

            if (j == k) {
                return true;
            }
        }

        return false;
    }

    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());

        vector<int> divisors;

        for (int i = 1; 1LL * i * i <= n; i++) {
            if (n % i == 0) {
                divisors.push_back(i);

                if (i != n / i) {
                    divisors.push_back(n / i);
                }
            }
        }

        int result = 0;

        for (int k : divisors) {
            bool valid = true;

            for (int i = 0; i < n; i += k) {
                if (!isRotation(nums, sortedNums, i, k)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                result += k;
            }
        }

        return result;
    }
};