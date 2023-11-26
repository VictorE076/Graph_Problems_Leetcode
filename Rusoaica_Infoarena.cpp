#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
//ifstream f("rusoaica.in.txt");
//ofstream g("rusoaica.out.txt");
ifstream f("rusuoaica.in");
ofstream g("rusuoaica.out");

bool CompareWeights(vector<int>& a, vector<int>& b)
{
    return (a[2] < b[2]);
}

class Graph
{
    const int n;
    const int m;
    const int A;
    vector<vector<int>> edges;

    int find_(vector<int>& parent, const int node)
    {
        if (parent[node] == node)
            return node;
        return parent[node] = find_(parent, parent[node]);
    }
    bool union_(vector<int>& parent, vector<int>& rank, const int p1, const int p2)
    {
        if (p1 == p2)
            return false;
        if (rank[p1] < rank[p2])
            parent[p1] = p2;
        else if (rank[p2] < rank[p1])
            parent[p2] = p1;
        else
        {
            parent[p2] = p1;
            rank[p1]++;
        }
        return true;
    }
public:
    Graph() = delete;
    Graph(const int n, const int m, const int A) : n(n), m(m), A(A)
    {
        int t1, t2, t3;
        for (int i = 0; i < this->m; i++)
        {
            f >> t1 >> t2 >> t3;
            this->edges.push_back({ t1 - 1, t2 - 1, t3 });
        }
    }
    //
    void Kruskal_Algorithm()
    {
        int min_cost = 0, num_edges_mst = 0;
        vector<int> parent(this->n);
        vector<int> rank(this->n, 0);
        for (int i = 0; i < this->n; i++)
        {
            parent[i] = i;
        }

        sort(this->edges.begin(), this->edges.end(), CompareWeights);
        
        for (int i = 0; i < this->m; i++)
        {
            int x = this->edges[i][0], y = this->edges[i][1];
            int cost = this->edges[i][2];

            bool unified = false;
            if(cost <= this->A) // Incercam sa includem in MST doar muchiile (tunelurile) care au un cost mai mic sau egal decat costul "A". 
            {
                int px = find_(parent, x);
                int py = find_(parent, y);
                unified = union_(parent, rank, px, py);
            }
            
            if (unified) // Daca muchia (tunelul) apare in MST, atunci platim costul acesteia.
            {
                min_cost += cost;
                num_edges_mst++;
            }
            else
                min_cost -= cost; // Daca muchia (tunelul) nu apare in MST, atunci o vindem.
        }

        min_cost = min_cost + this->A * (this->n - 1 - num_edges_mst); // Vom cumpara muchii (tuneluri) la costul "A" astfel incat sa avem toate nodurile (statii de metrou) in MST.
        g << min_cost << endl;
    }
    ~Graph() = default;
};

int main()
{
    // Time Complexity: O(n + m * log(m)) - Kruskal Algorithm
    int n, m, A;
    f >> n >> m >> A;
    Graph gr(n, m, A);
    f.close();
    gr.Kruskal_Algorithm();
    g.close();
    return 0;
}

