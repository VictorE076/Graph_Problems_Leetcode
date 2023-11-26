#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
bool compareWeights(vector<int>& v1, vector<int>& v2)
{
    return (v1[2] < v2[2]);
}

struct UnionFind_Kruskal
{
    int* parent;
    int* rank;
    UnionFind_Kruskal() = delete;
    UnionFind_Kruskal(const int n)
    {
        this->parent = new int[n];
        this->rank = new int[n];
        for (int i = 0; i < n; i++)
        {
            this->parent[i] = i;
            this->rank[i] = 0;
        }
    }
    ~UnionFind_Kruskal()
    {
        delete[] this->parent;
        delete[] this->rank;
    }
    int Find(const int node)
    {
        if (this->parent[node] == node)
            return node;
        return this->parent[node] = Find(this->parent[node]);
    }
    bool Union(const int x, const int y)
    {
        int px = Find(x);
        int py = Find(y);
        if (px == py)
            return false;
        if (this->rank[px] == this->rank[py])
        {
            this->parent[px] = py;
            this->rank[py]++;
        }
        else if (this->rank[px] < this->rank[py])
        {
            this->parent[px] = py;
        }
        else
        {
            this->parent[py] = px;
        }
        return true;
    }
};

class Solution {
    vector<vector<int>> sol = { {}, {} }; // { critical, pseudo-critical } edges in MST
public:
    void PrintSol()
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == 0)
                cout << "Critical edges:\n";
            else
                cout << "Pseudo-critical edges:\n";
            const int sz_i = this->sol[i].size();
            for (int j = 0; j < sz_i; j++)
            {
                cout << this->sol[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\n\n";
    }
    void PrintEdges(vector<vector<int>>& edges)
    {
        const int sz = edges.size();
        for (int i = 0; i < sz; i++)
        {
            const int sz_i = edges[i].size();
            for (int j = 0; j < sz_i; j++)
            {
                cout << edges[i][j] << " ";
            }
            cout << endl << endl;
        }
        cout << endl << endl;
    }
    void PrintVector(vector<int>& v)
    {
        const int sz = v.size();
        for (int i = 0; i < sz; i++)
        {
            cout << v[i] << " ";
        }
        cout << endl << endl;
    }

private:
    int count_nodes(vector<bool>& nodes)
    {
        int count = 0;
        const int sz = nodes.size();
        for (int i = 0; i < sz; i++)
        {
            if (nodes[i])
                count++;
        }
        return count;
    }
    int initial_Kruskal_(const int n, vector<vector<int>>& edges)
    {
        UnionFind_Kruskal u(n);
        int initial_weight = 0;
        const int sz = edges.size();
        for (int i = 0; i < sz; i++)
        {
            int e1 = edges[i][0], e2 = edges[i][1];
            if (u.Union(e1, e2))
                initial_weight += edges[i][2];
        }
        return initial_weight;
    }
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges)
    {
        const int sz_edges = edges.size();
        for (int i = 0; i < sz_edges; i++)
        {
            edges[i].push_back(i); // (+) original index
        }

        // this->PrintEdges(edges);
        sort(edges.begin(), edges.end(), compareWeights);
        // this->PrintEdges(edges);

        int init_weight = initial_Kruskal_(n, edges); // Running Kruskal Algorithm on original graph

        // Using Brute-Force and checking Kruskal Algorithm with and without each edge in the graph 
        for (int c = 0; c < sz_edges; c++)
        {
            // 1.Check if critical edge (without current edge in Kruskal)
            vector<bool> f_nodes(n, false);
            UnionFind_Kruskal u_critical(n);
            int current_weight = 0;
            int count_edges = 0;
            for (int i = 0; i < sz_edges; i++)
            {
                if (edges[i][3] == edges[c][3]) // skip current edge
                    continue;
                int e1 = edges[i][0], e2 = edges[i][1];
                if (u_critical.Union(e1, e2))
                {
                    current_weight += edges[i][2];
                    f_nodes[e1] = true;
                    f_nodes[e2] = true;
                    count_edges++;
                }
            }
            int c_nodes = count_nodes(f_nodes);
            if (!(c_nodes == n && c_nodes == count_edges + 1) || current_weight > init_weight) // Daca avem >= 2 componente conexe in MST, atunci muchia eliminata este critica
            {
                this->sol[0].push_back(edges[c][3]); // number "c" edge is a critical one
                continue; // A critical edge cannot be pseudo-critical at the same time 
            }

            // 2.Check pseudo-critical edge (with current edge in Kruskal)
            UnionFind_Kruskal u_pseudo_critical(n);
            u_pseudo_critical.Union(edges[c][0], edges[c][1]); // adding by force the current edge in the UnionFind
            current_weight = edges[c][2];
            for (int i = 0; i < sz_edges; i++)
            {
                int e1 = edges[i][0], e2 = edges[i][1];
                if (u_pseudo_critical.Union(e1, e2))
                {
                    current_weight += edges[i][2];
                }
            }
            if (current_weight == init_weight)
                this->sol[1].push_back(edges[c][3]); // number "c" edge is a pseudo-critical one
        }
        return this->sol;
    }
};
int main()
{
    // Time Complexity: O((m ^ 2) * log*(m)).
    // Example 1:
    int n1 = 5;
    vector<vector<int>> edges1 = { {0, 1, 1}, {1, 2, 1}, {2, 3, 2}, {0, 3, 2}, {0, 4, 3}, {3, 4, 3}, {1, 4, 6} };
    Solution s1;
    vector<vector<int>> sol1 = s1.findCriticalAndPseudoCriticalEdges(n1, edges1);
    s1.PrintSol();
    // Example 2:
    int n2 = 4;
    vector<vector<int>> edges2 = { {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 1} };
    Solution s2;
    vector<vector<int>> sol2 = s2.findCriticalAndPseudoCriticalEdges(n2, edges2);
    s2.PrintSol();
    // Example 3:
    int n3 = 6;
    vector<vector<int>> edges3 = { {0, 1, 1}, {1, 2, 1}, {0, 2, 1}, {2, 3, 4}, {3, 4, 2}, {3, 5, 2}, {4, 5, 2} };
    Solution s3;
    vector<vector<int>> sol3 = s3.findCriticalAndPseudoCriticalEdges(n3, edges3);
    s3.PrintSol();
    return 0;
}