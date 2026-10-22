#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;

        // ------------------------------------------------
        // 1. Pure rotation of original array
        // ------------------------------------------------
        int p = find(nums.begin(), nums.end(), 0) - nums.begin();

        bool ok = true;

        for (int i = 0; i < n; i++) {
            if (nums[(p + i) % n] != i) {
                ok = false;
                break;
            }
        }

        if (ok) {
            // Left rotate p times
            ans = min(ans, p);

            // Equivalent right rotation (n-p) times
            // Right rotation r = Reverse + Left(r) + Reverse
            int rightRot = (n - p) % n;
            ans = min(ans, rightRot + 2);
        }

        // ------------------------------------------------
        // 2. Reverse orientation
        // ------------------------------------------------
        vector<int> rev(nums.rbegin(), nums.rend());

        int q = find(rev.begin(), rev.end(), 0) - rev.begin();

        ok = true;

        for (int i = 0; i < n; i++) {
            if (rev[(q + i) % n] != i) {
                ok = false;
                break;
            }
        }

        if (ok) {
            // Reverse + left rotate q
            ans = min(ans, 1 + q);

            // Equivalent opposite rotation
            int rightRot = (n - q) % n;
            ans = min(ans, 1 + rightRot);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};