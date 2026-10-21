class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // 0 operations: already sorted
        bool sorted = true;

        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }

        if (sorted)
            return 0;

        // Cannot sort the whole string,
        // and for length 2 the only substring containing both
        // characters is the whole string.
        if (n == 2)
            return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // One operation is enough if one endpoint is already correct.
        if (s[0] == mn || s[n - 1] == mx)
            return 1;

        // If min/max exists inside, two operations are enough.
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx)
                return 2;
        }

        // Both extremes are at the wrong endpoints.
        return 3;
    }
};