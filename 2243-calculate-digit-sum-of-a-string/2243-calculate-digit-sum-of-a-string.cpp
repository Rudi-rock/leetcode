class Solution {
public:
    string digitSum(string s, int k) {
        while (s.length() > k) {
            string new_s = "";
            for (int i = 0; i < s.length(); i += k) {
                string group = s.substr(i, k);
                int sum = 0;
                for (char c : group) sum += c - '0';
                new_s += to_string(sum);
            }
            s = new_s;
        }
        return s;
    }
};