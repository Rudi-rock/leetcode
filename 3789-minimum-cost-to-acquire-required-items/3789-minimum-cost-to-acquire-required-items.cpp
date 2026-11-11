class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long best = LLONG_MAX;
        
        vector<int> candidates = {0, min(need1, need2), max(need1, need2)};
        
        for (int k : candidates) {
            long long rem1 = max(0, need1 - k);
            long long rem2 = max(0, need2 - k);
            long long cost = (long long)k * costBoth + rem1 * cost1 + rem2 * cost2;
            best = min(best, cost);
        }
        
        return best;
    }
};