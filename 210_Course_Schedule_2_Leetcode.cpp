#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Solution {
    void TopologicalSorting_BFS(vector<int>* g, int* id, vector<int>& sol, int n)
    {
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (id[i] != 0)
                continue;
            q.push(i);
        }
        while (!q.empty())
        {
            int vertex = q.front();
            q.pop();
            sol.push_back(vertex);
            int sz = g[vertex].size();
            for (int i = 0; i < sz; i++)
            {
                int neighb = g[vertex][i];
                if (id[neighb] > 0)
                {
                    id[neighb]--;
                    if (id[neighb] == 0)
                        q.push(neighb);
                }
            }
        }
    }
public:
    void PrintSolution(vector<int>& sol)
    {
        int sz = sol.size();
        for (int i = 0; i < sz; i++)
        {
            cout << sol[i] << " ";
        }
        cout << "\n\n";
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
    {
        vector<int> solution;
        vector<int>* graph;
        graph = new vector<int>[numCourses];
        int* in_degrees;
        in_degrees = new int[numCourses];
        for (int i = 0; i < numCourses; i++)
        {
            in_degrees[i] = 0;
        }
        int sz = prerequisites.size();
        for (int i = 0; i < sz; i++)
        {
            int ai = prerequisites[i][0], bi = prerequisites[i][1];
            graph[bi].push_back(ai);
            in_degrees[ai]++;
        }
        TopologicalSorting_BFS(graph, in_degrees, solution, numCourses);
        if (solution.size() < numCourses)
        {
            delete[] graph;
            delete[] in_degrees;
            return {};
        }
        delete[] graph;
        delete[] in_degrees;
        return solution;
    }
};
int main()
{
    // Example 1:
    vector<vector<int>> graph1 = { {1, 0} };
    Solution a1;
    vector<int> s1 = a1.findOrder(2, graph1);
    cout << "Sol. 1: size = " << s1.size() << endl;
    if (s1.size() > 0)
    {
        a1.PrintSolution(s1);
    }
    // Example 2:
    vector<vector<int>> graph2 = { {1, 0}, {2, 0}, {3, 1}, {3, 2} };
    Solution a2;
    vector<int> s2 = a2.findOrder(4, graph2);
    cout << "Sol. 2: size = " << s2.size() << endl;
    if (s2.size() > 0)
    {
        a2.PrintSolution(s2);
    }
    // Example 3:
    vector<vector<int>> graph3 = {};
    Solution a3;
    vector<int> s3 = a3.findOrder(1, graph3);
    cout << "Sol. 3: size = " << s3.size() << endl;
    if (s3.size() > 0)
    {
        a3.PrintSolution(s3);
    }
    // Example 4:
    vector<vector<int>> graph4 = { {0, 2}, {4, 2}, {1, 4}, {2, 1}, {1, 3}, {4, 3} };
    Solution a4;
    vector<int> s4 = a4.findOrder(5, graph4);
    cout << "Sol. 4: size = " << s4.size() << endl;
    if (s4.size() > 0)
    {
        a4.PrintSolution(s4);
    }
    return 0;
}

