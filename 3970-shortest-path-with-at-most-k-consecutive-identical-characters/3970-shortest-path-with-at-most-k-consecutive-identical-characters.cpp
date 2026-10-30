#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        const long long INF = LLONG_MAX / 4;
        vector<long long> dist((size_t)n * (k + 1), INF);
        auto idx = [&](int node, int run) { return (size_t)node * (k + 1) + run; };

        priority_queue<tuple<long long, int, int>,
                       vector<tuple<long long, int, int>>,
                       greater<tuple<long long, int, int>>> pq;

        dist[idx(0, 1)] = 0;
        pq.push({0LL, 0, 1});

        while (!pq.empty()) {
            auto [d, u, r] = pq.top();
            pq.pop();
            if (d > dist[idx(u, r)]) continue;
            if (u == n - 1) return (int)d;

            for (auto [v, w] : adj[u]) {
                int nr;
                if (labels[v] == labels[u]) {
                    nr = r + 1;
                    if (nr > k) continue;
                } else {
                    nr = 1;
                }
                long long nd = d + w;
                if (nd < dist[idx(v, nr)]) {
                    dist[idx(v, nr)] = nd;
                    pq.push({nd, v, nr});
                }
            }
        }
        return -1;
    }
};