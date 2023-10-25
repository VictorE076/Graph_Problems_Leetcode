#include <iostream>
#include <vector>
using namespace std;
class Solution {
    vector<vector<int>> sol;
    void DFS_(int pred, int node, int level, int* min_level, vector<int>* g)
    {
        min_level[node] = level;
        int sz = g[node].size();
        for (int i = 0; i < sz; i++)
        {
            int neighb = g[node][i];
            if (min_level[neighb] == -1)
                DFS_(node, neighb, level + 1, min_level, g);
            if (neighb != pred && min_level[neighb] < min_level[node])
            {
                min_level[node] = min_level[neighb];
            }
        }
        if (pred > -1 && level == min_level[node])
        {
            this->sol.push_back({pred, node});
        }
    }
public:
    void PrintSolution()
    {
        int sz = this->sol.size();
        for (int i = 0; i < sz; i++)
        {
            cout << "( " << this->sol[i][0] << ", " << this->sol[i][1] << " )\t";
        }
        cout << endl << endl;
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
    {
        vector<int>* graph = new vector<int>[n];
        int sz = connections.size();
        for (int i = 0; i < sz; i++)
        {
            int ai = connections[i][0], bi = connections[i][1];
            graph[ai].push_back(bi);
            graph[bi].push_back(ai);
        }
        int* min_level = new int[n];
        for (int i = 0; i < n; i++)
        {
            min_level[i] = -1;
        }
        for (int i = 0; i < n; i++)
        {
            if (min_level[i] != -1)
                continue;
            DFS_(-1, i, 1, min_level, graph);
        }
        delete[] graph;
        delete[] min_level;
        return this->sol;
    }
};
int main()
{
    // Example 1:
    vector<vector<int>> graph1 = { {0, 1}, {1, 2}, {2, 0}, {1, 3} };
    Solution s1;
    vector<vector<int>> sol1 = s1.criticalConnections(4, graph1);
    cout << "Solution 1:\n";
    s1.PrintSolution();
    // Example 2:
    vector<vector<int>> graph2 = { {0, 1} };
    Solution s2;
    vector<vector<int>> sol2 = s2.criticalConnections(2, graph2);
    cout << "Solution 2:\n";
    s2.PrintSolution();
    return 0;
}
