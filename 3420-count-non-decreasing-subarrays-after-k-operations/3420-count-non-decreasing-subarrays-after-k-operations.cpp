class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 17;

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        vector<int> nxt(n, n), st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i])
                st.pop_back();

            if (!st.empty())
                nxt[i] = st.back();

            st.push_back(i);
        }

        vector<vector<int>> up(LOG + 1, vector<int>(n, n));
        vector<vector<long long>> cost(LOG + 1, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];
            cost[0][i] = 1LL * nums[i] * (nxt[i] - i - 1)
                       - (pref[nxt[i]] - pref[i + 1]);
        }

        for (int j = 1; j <= LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[j - 1][i];

                if (mid < n) {
                    up[j][i] = up[j - 1][mid];
                    cost[j][i] = cost[j - 1][i] + cost[j - 1][mid];
                } else {
                    cost[j][i] = cost[j - 1][i];
                }
            }
        }

        auto getCost = [&](int l, int r) {
            long long res = 0;
            int cur = l;

            for (int j = LOG; j >= 0; j--) {
                if (up[j][cur] <= r) {
                    res += cost[j][cur];
                    cur = up[j][cur];
                }
            }

            res += 1LL * nums[cur] * (r - cur)
                 - (pref[r + 1] - pref[cur + 1]);

            return res;
        };

        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int l = 0, high = r;

            while (l < high) {
                int mid = l + (high - l) / 2;

                if (getCost(mid, r) <= k)
                    high = mid;
                else
                    l = mid + 1;
            }

            ans += r - l + 1;
        }

        return ans;
    }
};