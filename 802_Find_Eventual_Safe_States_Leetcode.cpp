#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Solution {
    vector<int> sol;
    void CountingSort_sol_(const int n)
    {
        bool* freq;
        freq = new bool[n];
        for (int i = 0; i < n; i++)
        {
            freq[i] = 0;
        }
        int sz = sol.size();
        for (int i = 0; i < sz; i++)
        {
            freq[sol[i]] = 1;
        }
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (freq[i] == 1)
                sol[count++] = i;
        }
        delete[] freq;
    }
    void TopologicalSorting_BFS(vector<int>* r_g, int* id_r, const int n)
    {
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (id_r[i] != 0)
                continue;
            q.push(i);
        }
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            this->sol.push_back(node);
            int sz = r_g[node].size();
            for (int i = 0; i < sz; i++)
            {
                int neighb = r_g[node][i];
                if (id_r[neighb] > 0)
                {
                    id_r[neighb]--;
                    if (id_r[neighb] == 0)
                        q.push(neighb);
                }
            }
        }
    }
public:
    void PrintSolution()
    {
        int sz = this->sol.size();
        for (int i = 0; i < sz; i++)
        {
            cout << this->sol[i] << " ";
        }
        cout << endl << endl;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) 
    {
        int sz = graph.size();
        vector<int>* reverse_graph;
        reverse_graph = new vector<int>[sz];
        int* in_degrees_reverse;
        in_degrees_reverse = new int[sz];
        for (int i = 0; i < sz; i++)
        {
            int sz_i = graph[i].size();
            in_degrees_reverse[i] = sz_i;
            for (int j = 0; j < sz_i; j++)
            {
                int neighb = graph[i][j];
                reverse_graph[neighb].push_back(i);
            }
        }
        TopologicalSorting_BFS(reverse_graph, in_degrees_reverse, sz);
        CountingSort_sol_(sz);
        delete[] in_degrees_reverse;
        delete[] reverse_graph;
        return this->sol;
    }
};
int main()
{
    // Example 1:
    vector<vector<int>> graph1 = { {1, 2}, {2, 3}, {5}, {0}, {5}, {}, {} };
    Solution s1;
    cout << "Solution 1:\n";
    vector<int> v1 = s1.eventualSafeNodes(graph1);
    s1.PrintSolution();
    //
    // Example 2:
    vector<vector<int>> graph2 = { {1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {} };
    Solution s2;
    cout << "Solution 2:\n";
    vector<int> v2 = s2.eventualSafeNodes(graph2);
    s2.PrintSolution();
    return 0;
}
