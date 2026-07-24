class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int v : nums) {
            auto ndp = dp;  // option of taking this index 0 times

            for (int used = 0; used <= 3; used++) {
                for (int x = 0; x < MAXX; x++) {
                    if (!dp[used][x]) continue;

                    // Take this index once
                    if (used + 1 <= 3)
                        ndp[used + 1][x ^ v] = true;

                    // Take this index twice (xor contribution = 0)
                    if (used + 2 <= 3)
                        ndp[used + 2][x] = true;

                    // Take this index three times
                    if (used + 3 <= 3)
                        ndp[used + 3][x ^ v] = true;
                }
            }

            dp = move(ndp);
        }

        int ans = 0;
        for (bool ok : dp[3])
            if (ok) ans++;

        return ans;
    }
};