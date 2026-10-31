class Solution {
public:
    const int MOD = 1e9 + 7;

    int m, n;

    vector<vector<vector<pair<int, int>>>> memo;
    vector<vector<vector<bool>>> vis;

    pair<int, int> solve(int i, int j, int dir,
                         vector<vector<int>>& grid) {

        if (i >= m || j >= n)
            return {-1, -1};

        if (vis[i][j][dir])
            return memo[i][j][dir];

        vis[i][j][dir] = true;

        int ni, nj;

        if (dir == 0) {
            ni = i + 1;
            nj = j;
        } 
        else {
            ni = i;
            nj = j + 1;
        }

        if (ni >= m || nj >= n) {
            return memo[i][j][dir] = {-1, -1};
        }

        if (grid[ni][nj] == 0) {
            return memo[i][j][dir] = {ni, nj};
        }

        return memo[i][j][dir] =
            solve(ni, nj, 1 - dir, grid);
    }

    int uniquePaths(vector<vector<int>>& grid) {

        m = grid.size();
        n = grid[0].size();

        memo.assign(m, vector<vector<pair<int, int>>>(
            n, vector<pair<int, int>>(2, {-1, -1})
        ));

        vis.assign(m, vector<vector<bool>>(
            n, vector<bool>(2, false)
        ));

        vector<vector<long long>> dp(
            m, vector<long long>(n, 0)
        );

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1 || dp[i][j] == 0)
                    continue;

                // Move Right
                if (j + 1 < n) {

                    if (grid[i][j + 1] == 0) {
                        dp[i][j + 1] =
                            (dp[i][j + 1] + dp[i][j]) % MOD;
                    } 
                    else {

                        auto p = solve(i, j + 1, 0, grid);

                        if (p.first != -1) {
                            dp[p.first][p.second] =
                                (dp[p.first][p.second] +
                                 dp[i][j]) % MOD;
                        }
                    }
                }

                // Move Down
                if (i + 1 < m) {

                    if (grid[i + 1][j] == 0) {
                        dp[i + 1][j] =
                            (dp[i + 1][j] + dp[i][j]) % MOD;
                    } 
                    else {

                        auto p = solve(i + 1, j, 1, grid);

                        if (p.first != -1) {
                            dp[p.first][p.second] =
                                (dp[p.first][p.second] +
                                 dp[i][j]) % MOD;
                        }
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};