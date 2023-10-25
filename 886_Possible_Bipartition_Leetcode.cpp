#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Solution {
    bool BFS(vector<int>* graph, int node, char* colors)
    {
        queue<int> q;
        q.push(node);
        colors[node] = 0;
        while (!q.empty())
        {
            int vertex = q.front();
            q.pop();
            int sz = graph[vertex].size();
            for (int i = 0; i < sz; i++)
            {
                int neighb = graph[vertex][i];
                if (colors[neighb] == 2)
                {
                    colors[neighb] = 1 - colors[vertex];
                    q.push(neighb);
                }
                else if (colors[vertex] == colors[neighb])
                {
                    return false;
                }
            }
        }
        return true;
    }
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) 
    {
        vector<int>* graph;
        graph = new vector<int>[n + 1];
        char* colors;
        colors = new char[n + 1];
        for (int i = 0; i <= n; i++)
        {
            colors[i] = 2;
        }
        int sz = dislikes.size();
        for (int i = 0; i < sz; i++)
        {
            int ai = dislikes[i][0], bi = dislikes[i][1];
            graph[ai].push_back(bi);
            graph[bi].push_back(ai);
        }
        for (int i = 1; i <= n; i++)
        {
            if (colors[i] != 2)
                continue;
            bool check = BFS(graph, i, colors);
            if (!check)
            {
                delete[] graph;
                delete[] colors;
                return false;
            }
        }
        delete[] graph;
        delete[] colors;
        return true;
    }
};
int main()
{
    // Example 1:
    int n1 = 4;
    vector<vector<int>> dislikes1 = { {1, 2}, {1, 3}, {2, 4} };
    Solution s1;
    bool sol1 = s1.possibleBipartition(n1, dislikes1);
    cout << "Solution 1: " << sol1 << endl; // True
    // Example 2:
    int n2 = 3;
    vector<vector<int>> dislikes2 = { {1, 2}, {1, 3}, {2, 3} };
    Solution s2;
    bool sol2 = s2.possibleBipartition(n2, dislikes2);
    cout << "Solution 2: " << sol2 << endl; // False
    return 0;
}


