class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        
        // Build children list
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++)
            children[parent[i]].push_back(i);
        
        vector<int> answer(n, 1);
        unordered_map<char, vector<int>> char_ancestors;
        
        function<void(int)> dfs = [&](int node) {
            char c = s[node];
            
            // Reparent if closer ancestor with same char exists
            if (!char_ancestors[c].empty()) {
                int new_parent = char_ancestors[c].back();
                parent[node] = new_parent;
            }
            
            char_ancestors[c].push_back(node);
            
            for (int child : children[node])
                dfs(child);
            
            char_ancestors[c].pop_back();
            
            if (parent[node] != -1)
                answer[parent[node]] += answer[node];
        };
        
        dfs(0);
        return answer;
    }
};