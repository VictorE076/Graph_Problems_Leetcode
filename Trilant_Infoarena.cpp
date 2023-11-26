#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <limits>
using namespace std;
//ifstream f("trilant.in.txt");
//ofstream g("trilant.out.txt");
ifstream f("trilant.in");
ofstream g("trilant.out");

const long long MAX_LIMIT = LLONG_MAX;
vector<long long> dist[3];
int Lant; // Lantul 'A', 'B' sau 'C'.
struct min_heap
{
    bool operator()(const int a, const int b)
    {
        return (dist[Lant][a] > dist[Lant][b]);
    }
};

class Graph
{
    const int n, m, A, B, C;
    vector<pair<int, int>>* graph;
    vector<int> parent[3];

    void Dijkstra_Algorithm_(const int start)
    {
        priority_queue<int, vector<int>, min_heap> pq;
        pq.push(start);
        dist[Lant][start] = 0;
        this->parent[Lant][start] = -1;
        while (!pq.empty())
        {
            int node = pq.top();
            pq.pop();
            const int sz_node = this->graph[node].size();
            for (int i = 0; i < sz_node; i++)
            {
                int vecin = this->graph[node][i].first, cost = this->graph[node][i].second;
                if ((long long)(dist[Lant][node] + cost) < (long long)(dist[Lant][vecin]))
                {
                    dist[Lant][vecin] = (long long)(dist[Lant][node] + cost);
                    this->parent[Lant][vecin] = node;
                    pq.push(vecin);
                }
            }
        }
    }

public:
    Graph() = delete;
    Graph(const int n, const int m, const int A, const int B, const int C) : n(n), m(m), A(A), B(B), C(C)
    {
        int p, q, t;
        this->graph = new vector<pair<int, int>>[this->n + 1];
        for (int i = 0; i < this->m; i++)
        {
            f >> p >> q >> t;
            this->graph[p].push_back(make_pair(q, t));
            this->graph[q].push_back(make_pair(p, t));
        }
    }

    //
    void PrintGraph()
    {
        for (int i = 1; i <= this->n; i++)
        {
            cout << i << ": ";
            const int sz_i = this->graph[i].size();
            for (int j = 0; j < sz_i; j++)
            {
                cout << "( " << this->graph[i][j].first << ", " << this->graph[i][j].second << " )\t";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    //
    
    void Trilant()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j <= this->n; j++)
            {
                dist[i].push_back(MAX_LIMIT);
                this->parent[i].push_back(-1);
            }
        }

        Lant = 0;
        Dijkstra_Algorithm_(this->A); // Dijkstra pornind din nodul "A".

        Lant = 1;
        Dijkstra_Algorithm_(this->B); // Dijkstra pornind din nodul "B".

        Lant = 2;
        Dijkstra_Algorithm_(this->C); // Dijkstra pornind din nodul "C".

        long long min_cost = MAX_LIMIT;
        int min_node = 0;
        for (int i = 1; i <= this->n; i++)
        {   
            if (dist[0][i] + dist[1][i] + dist[2][i] < min_cost) // Costul minim este egal cu minimul distantelor de la nodul "X" la nodurile "A", "B" si "C" insumate.
            {
                min_cost = dist[0][i] + dist[1][i] + dist[2][i];
                min_node = i;
            }
        }
        g << min_cost << endl;

        for (int lant = 0; lant < 3; lant++)
        {
            int current = min_node;
            int num_nodes = 1;
            while (this->parent[lant][current] != -1)
            {
                current = this->parent[lant][current];
                num_nodes++;
            }
            
            g << num_nodes << " "; // Numarul de noduri din unul din lanturile "A", "B" sau "C".

            current = min_node;
            while (this->parent[lant][current] != -1)
            {
                g << current << " "; // Valoarea fiecarui nod din unul din lanturile "A", "B" sau "C" (exceptie fiind ultimul nod).
                current = this->parent[lant][current];
            }
            g << current << endl; // Valoarea ultimului nod din unul din lanturile "A", "B" sau "C".
        }
    }
    ~Graph() 
    {
        delete[] graph;
    }
};

int main()
{
    // Time Complexity: O(n + m * log(n)) - Dijkstra Algorithm
    int n, m, A, B, C;
    f >> n >> m >> A >> B >> C;
    Graph gr(n, m, A, B, C);
    f.close();
    // gr.PrintGraph();
    gr.Trilant();
    g.close();
    return 0;
}

