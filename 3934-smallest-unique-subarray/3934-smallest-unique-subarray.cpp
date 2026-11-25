class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        
        auto hasUnique = [&](int len) -> bool {
            unordered_map<unsigned long long, int> freq;
            unsigned long long base = 100003, mod = (1ULL << 61) - 1; // Mersenne prime
            
            auto mulmod = [&](unsigned long long a, unsigned long long b) -> unsigned long long {
                return (__uint128_t)a * b % mod;
            };
            
            unsigned long long hash = 0, power = 1;
            
            for (int i = 0; i < len; i++) {
                hash = (mulmod(hash, base) + nums[i]) % mod;
                if (i > 0) power = mulmod(power, base);
            }
            freq[hash]++;
            
            for (int i = len; i < n; i++) {
                hash = (hash - mulmod(nums[i - len], power) % mod + mod) % mod;
                hash = (mulmod(hash, base) + nums[i]) % mod;
                freq[hash]++;
            }
            
            for (auto& [k, v] : freq)
                if (v == 1) return true;
            return false;
        };
        
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (hasUnique(mid)) hi = mid;
            else lo = mid + 1;
        }
        
        return lo;
    }
};