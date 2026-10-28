class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[j][x] = whether XOR value x is possible
        // when reaching the current cell in column j
        vector<bitset<1024>> dp(n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                bitset<1024> cur;

                // Starting cell
                if (i == 0 && j == 0) {
                    cur[grid[i][j]] = 1;
                } 
                else {
                    // Come from above
                    if (i > 0) {
                        for (int x = 0; x < 1024; x++) {
                            if (dp[j][x]) {
                                cur[x ^ grid[i][j]] = 1;
                            }
                        }
                    }

                    // Come from left
                    if (j > 0) {
                        for (int x = 0; x < 1024; x++) {
                            if (dp[j - 1][x]) {
                                cur[x ^ grid[i][j]] = 1;
                            }
                        }
                    }
                }

                dp[j] = cur;
            }
        }

        // Find the smallest possible XOR
        for (int x = 0; x < 1024; x++) {
            if (dp[n - 1][x]) {
                return x;
            }
        }

        return -1;
    }
};