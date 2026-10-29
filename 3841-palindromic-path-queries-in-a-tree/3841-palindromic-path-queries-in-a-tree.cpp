class Solution {
    static constexpr int LOG = 17;

    int n, timer;
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, bit, val;

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[0][u] = p;

        for (int k = 1; k < LOG; ++k) {
            up[k][u] = up[k - 1][up[k - 1][u]];
        }

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    void update(int i, int x) {
        for (; i <= n; i += i & -i) {
            bit[i] ^= x;
        }
    }

    int query(int i) {
        int res = 0;

        for (; i > 0; i -= i & -i) {
            res ^= bit[i];
        }

        return res;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];

        for (int k = 0; k < LOG; ++k) {
            if (diff & (1 << k)) {
                u = up[k][u];
            }
        }

        if (u == v) return u;

        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        timer = 0;

        adj.assign(n, {});
        up.assign(LOG, vector<int>(n));
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        bit.assign(n + 2, 0);
        val.resize(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        for (int i = 0; i < n; ++i) {
            val[i] = 1 << (s[i] - 'a');
        }

        dfs(0, 0);

        // Initialize the Fenwick tree using Euler difference updates.
        for (int u = 0; u < n; ++u) {
            update(tin[u], val[u]);
            update(tout[u] + 1, val[u]);
        }

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int newMask = 1 << (c - 'a');
                int delta = val[u] ^ newMask;

                update(tin[u], delta);
                update(tout[u] + 1, delta);

                val[u] = newMask;
            } else {
                int v;
                ss >> v;

                int pu = query(tin[u]);
                int pv = query(tin[v]);
                int w = lca(u, v);

                int pathMask = pu ^ pv ^ val[w];

                ans.push_back(
                    (pathMask & (pathMask - 1)) == 0
                );
            }
        }

        return ans;
    }
};