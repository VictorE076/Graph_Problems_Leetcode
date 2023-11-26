#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX_LIMIT = 2147483647;
vector<vector<int>> dst_every_k; // n * (k + 2) matrix (max_path_nodes = 2 + k_stops)
struct rule
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return dst_every_k[a.first][a.second] > dst_every_k[b.first][b.second];
    }
};

class Solution {

private:
    int Dijkstra_k_stops(vector<pair<int, int>>* g, const int n, const int src, const int dst, const int k) 
    {
        for (int i = 0; i < n; i++)
        {
            dst_every_k.push_back({});
            for (int j = 0; j < k + 2; j++)
            {
                dst_every_k[i].push_back(MAX_LIMIT);
            }
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, rule> pq; // (node, num_of_stops)

        dst_every_k[src][0] = 0;
        pq.push(make_pair(src, 0));

        while (!pq.empty()) 
        {
            int node = pq.top().first, num_stops = pq.top().second;
            pq.pop();
            if (node == dst)
            {
                int cheapest = dst_every_k[node][num_stops];
                dst_every_k.clear();
                return cheapest;
            }   
            if (num_stops < k + 1)
            {
                const int sz = g[node].size();
                for (int i = 0; i < sz; i++)
                {
                    int neighb = g[node][i].first, price = g[node][i].second;
                    if (dst_every_k[node][num_stops] + price < dst_every_k[neighb][num_stops + 1])
                    {
                        dst_every_k[neighb][num_stops + 1] = dst_every_k[node][num_stops] + price;
                        pq.push(make_pair(neighb, num_stops + 1));
                    }
                }
            }
        }

        dst_every_k.clear();
        return -1;
    }

public:
    void PrintGraph(vector<pair<int, int>>* g, const int n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << i << " :  ";
            const int sz = g[i].size();
            for (int j = 0; j < sz; j++)
            {
                cout << g[i][j].first << " " << g[i][j].second << "\t";
            }
            cout << "\n\n";
        }
        cout << "\n\n";
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        vector<pair<int, int>>* graph;
        graph = new vector<pair<int, int>>[n];

        const int sz = flights.size();
        for (int i = 0; i < sz; i++)
        {
            int a, b, prc;
            a = flights[i][0];
            b = flights[i][1];
            prc = flights[i][2];
            graph[a].push_back(make_pair(b, prc));
        }

        // this->PrintGraph(graph, n);

        int cheapest_price = Dijkstra_k_stops(graph, n, src, dst, k);

        delete[] graph;
        return cheapest_price;
    }
};
int main()
{
    // Time Complexity: O(n * k + m * log(m)) 
    // 
    // Example 1:
    int n1 = 4, src1 = 0, dst1 = 3, k1 = 1;
    vector<vector<int>> flights1 = { {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200} };
    Solution s1;
    cout << s1.findCheapestPrice(n1, flights1, src1, dst1, k1) << endl;
    // Example 2:
    int n2 = 3, src2 = 0, dst2 = 2, k2 = 1;
    vector<vector<int>> flights2 = { {0, 1, 100}, {1, 2, 100}, {0, 2, 500} };
    Solution s2;
    cout << s2.findCheapestPrice(n2, flights2, src2, dst2, k2) << endl;
    // Example 3:
    int n3 = 3, src3 = 0, dst3 = 2, k3 = 0;
    vector<vector<int>> flights3 = { {0, 1, 100}, {1, 2, 100}, {0, 2, 500} };
    Solution s3;
    cout << s3.findCheapestPrice(n3, flights3, src3, dst3, k3) << endl;
    return 0;
}
