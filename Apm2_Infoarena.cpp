#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <limits>
using namespace std;

//ifstream f("apm2.in.txt");
//ofstream g("apm2.out.txt");
ifstream f("apm2.in");
ofstream g("apm2.out");

const int MAX_LIMIT = INT_MAX;

bool compareCosts(vector<int>& a, vector<int>& b)
{
    return (a[2] < b[2]);
}

class Graph
{
    const int n;
    const int m;
    const int Q;
    vector<vector<int>> edges;
    vector<vector<int>> n_edges; // "Q" number of new edges
    
    int find_(vector<int>& parent, const int node)
    {
        if (node == parent[node])
            return node;
        parent[node] = find_(parent, parent[node]);
        return parent[node];
    }

    void union_(vector<int>& parent, vector<int>& rank, const int x, const int y)
    {
        int px = find_(parent, x);
        int py = find_(parent, y);
        if (px == py)
            return;
        if (rank[px] < rank[py])
            parent[px] = py;
        else if (rank[py] < rank[px])
            parent[py] = px;
        else
        {
            parent[py] = px;
            rank[px]++;
        }
    }

    void Print_Modified_New_Costs_()
    {
        for (int i = 0; i < this->Q; i++)
        {
            g << this->n_edges[i][2] << endl;
        }
    }

public:
    Graph() = delete;
    Graph(const int n, const int m, const int Q) : n(n), m(m), Q(Q)
    {
        int x, y, t;
        for (int i = 0; i < this->m; i++)
        {
            f >> x >> y >> t;
            this->edges.push_back({ x, y, t });
        }
        for (int i = 0; i < this->Q; i++)
        {
            f >> x >> y;
            this->n_edges.push_back({ x, y, MAX_LIMIT }); // Noile "Q" drumuri sunt separate de celelalte "m" drumuri principale si nu au initial niciun cost (MAX_LIMIT).
        }
    }

    void Apm2()
    {
        // Aplicam algoritmul lui Kruskal pe cele "m" drumuri principale.
        vector<int> parent(this->n + 1);
        vector<int> rank(this->n + 1, 0);
        for (int i = 0; i <= this->n; i++)
        {
            parent[i] = i;
            // cout << parent[i] << " " << rank[i] << endl;
        }

        sort(this->edges.begin(), this->edges.end(), compareCosts); // sortam crescator cele "m" drumuri principale. 

        for (int i = 0; i < this->m; i++)
        {
            const int node_x = this->edges[i][0];
            const int node_y = this->edges[i][1];
            const int weight = this->edges[i][2]; // costul drumului de la nodul 'X' la 'Y'.
        
            union_(parent, rank, node_x, node_y); // Aplicam Union_Find pe cele doua noduri ('X', 'Y').
            
            for (int j = 0; j < this->Q; j++)
            {
                const int n_node_x = this->n_edges[j][0];
                const int n_node_y = this->n_edges[j][1];

                if (this->n_edges[j][2] < MAX_LIMIT)
                    continue;
                
                const int parent_n_x = find_(parent, n_node_x);
                const int parent_n_y = find_(parent, n_node_y);

                if (parent_n_x != parent_n_y)
                    continue;

                // Modificam o singura data fiecare drum nou din cele "Q" date doar daca nodurile au fost deja incluse anterior in MST.
                // Cum cele "m" muchii (drumuri) alese sunt deja sortate crescator dupa costul lor, valoarea "weight" va reprezenta, la fiecare pas, costul maxim al unei muchii deja incluse in MST.
                this->n_edges[j][2] = weight - 1; // weight = "max cost" in MST edges.
            }
        }

        Print_Modified_New_Costs_();

    }

    ~Graph() = default;
};
int main()
{
    // Time Complexity: O(n + m * log(m) + Q * m * log*(m))
    int n, m, Q;
    f >> n >> m >> Q;
    Graph gr(n, m, Q);
    f.close();
    gr.Apm2();
    g.close();
    return 0;
}
