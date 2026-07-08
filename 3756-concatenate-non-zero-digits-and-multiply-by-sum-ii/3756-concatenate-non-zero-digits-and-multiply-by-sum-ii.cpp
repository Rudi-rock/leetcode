class Solution {
public:
    static constexpr int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        // cnt[i] = number of non-zero digits in s[0...i-1]
        vector<int> cnt(n + 1, 0);

        // digitPrefix[i] = sum of digits in s[0...i-1]
        vector<long long> digitPrefix(n + 1, 0);

        vector<int> nz;

        for (int i = 0; i < n; i++) {
            cnt[i + 1] = cnt[i];
            digitPrefix[i + 1] = digitPrefix[i] + (s[i] - '0');

            if (s[i] != '0') {
                cnt[i + 1]++;
                nz.push_back(s[i] - '0');
            }
        }

        int m = nz.size();

        // powers of 10
        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        // prefix hash of concatenated non-zero digits
        vector<long long> hash(m + 1, 0);
        for (int i = 0; i < m; i++) {
            hash[i + 1] = (hash[i] * 10 + nz[i]) % MOD;
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int left = cnt[l];
            int right = cnt[r + 1];
            int len = right - left;

            long long x = (hash[right] - hash[left] * pow10[len]) % MOD;
            if (x < 0) x += MOD;

            long long sum = digitPrefix[r + 1] - digitPrefix[l];

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};
