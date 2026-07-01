class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        long long sum = 0;
        multiset<int> selected, other;

        for (int i = 1; i <= dist + 1; i++) {
            selected.insert(nums[i]);
            sum += nums[i];
        }

        balance(selected, other, sum, k);

        long long ans = sum;

        for (int i = dist + 2; i < nums.size(); i++) {
            int rem = nums[i - dist - 1];

            auto it = selected.find(rem);
            if (it != selected.end()) {
                sum -= rem;
                selected.erase(it);
            } else {
                other.erase(other.find(rem));
            }

            if (selected.empty() || nums[i] <= *selected.rbegin()) {
                selected.insert(nums[i]);
                sum += nums[i];
            } else {
                other.insert(nums[i]);
            }

            balance(selected, other, sum, k);

            ans = min(ans, sum);
        }

        return ans + nums[0];
    }

private:
    void balance(multiset<int>& selected,
                 multiset<int>& other,
                 long long& sum,
                 int k) {
        while ((int)selected.size() > k - 1) {
            auto it = prev(selected.end());
            sum -= *it;
            other.insert(*it);
            selected.erase(it);
        }

        while ((int)selected.size() < k - 1) {
            auto it = other.begin();
            sum += *it;
            selected.insert(*it);
            other.erase(it);
        }

        while (!selected.empty() && !other.empty()) {
            auto a = prev(selected.end());
            auto b = other.begin();

            if (*a > *b) {
                int x = *a;
                int y = *b;

                sum += (long long)y - x;

                selected.erase(a);
                other.erase(b);

                selected.insert(y);
                other.insert(x);
            } else {
                break;
            }
        }
    }
}
;