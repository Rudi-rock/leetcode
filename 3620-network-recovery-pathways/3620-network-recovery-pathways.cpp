class Solution {
public:
    int n;
    vector<int> topo;

    bool check(long long x,
               vector<vector<pair<int,int>>> &adj,
               vector<bool> &online,
               long long k) {

        const long long INF = 4e18;
        vector<long long> dist(n, INF);
        dist[0] = 0;

        for (int u : topo) {
            if (dist[u] == INF) continue;

            if (u != 0 && u != n - 1 && !online[u])
                continue;

            for (auto &[v, c] : adj[u]) {

                if (c < x) continue;

                if (v != 0 && v != n - 1 && !online[v])
                    continue;

                dist[v] = min(dist[v], dist[u] + (long long)c);
            }
        }

        return dist[n - 1] <= k;
    }

    int findMaxPathScore(vector<vector<int>>& edges,
                         vector<bool>& online,
                         long long k) {

        n = online.size();

        vector<vector<pair<int,int>>> adj(n);
        vector<int> indegree(n, 0);

        int mx = 0;

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int c = e[2];

            adj[u].push_back({v, c});
            indegree[v]++;
            mx = max(mx, c);
        }

        // Topological Sort (Kahn's Algorithm)
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &[v, c] : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0)
                    q.push(v);
            }
        }

        int ans = -1;
        long long lo = 0;
        long long hi = mx;

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;

            if (check(mid, adj, online, k)) {
                ans = (int)mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};