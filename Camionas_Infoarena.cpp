#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>
#include <limits>
using namespace std;
//ifstream f("camionas.in.txt");
//ofstream g("camionas.out.txt");
ifstream f("camionas.in");
ofstream g("camionas.out");

const int MAX_LIMIT = INT_MAX;
vector<int> dist;
struct min_heap
{
    bool operator()(const int a, const int b)
    {
        return (dist[a] > dist[b]);
    }
};

class Graph
{
    const int n;
    const int m;
    const int G;
    vector<pair<int, bool>>* graph;

public:
    Graph() = delete;
    Graph(const int n, const int m, const int G) : n(n), m(m), G(G)
    {
        this->graph = new vector<pair<int, bool>>[n + 1];
        int x, y, gi;
        for (int i = 0; i < this->m; i++)
        {
            f >> x >> y >> gi;
            bool endurance = false; // Drum ce nu necesita modificarea rezistentei acestuia.
            if (gi < this->G)
                endurance = true; // Drum ce necesita modificarea rezistentei acestuia.
            this->graph[x].push_back(make_pair(y, endurance));
            this->graph[y].push_back(make_pair(x, endurance));
        }
    }

    void Dijkstra_Algorithm()
    {
        for (int i = 0; i <= this->n; i++)
        {
            dist.push_back(MAX_LIMIT);
        }

        priority_queue<int, vector<int>, min_heap> pq;

        // Incepem mereu de la nodul "1"
        dist[1] = 0;
        pq.push(1);

        while (!pq.empty())
        {
            int node = pq.top();
            pq.pop();
            
            const int sz_node = this->graph[node].size();
            for (int i = 0; i < sz_node; i++)
            {
                int vecin = this->graph[node][i].first;
                int cost = (int)(this->graph[node][i].second);
                
                if (dist[node] + cost < dist[vecin])
                {
                    dist[vecin] = dist[node] + cost;
                    pq.push(vecin);
                }
            }
        }
        g << dist[this->n] << endl; // Numarul minim de drumuri a caror rezistenta trebuie marita.
    }
    ~Graph()
    {
        delete[] this->graph;
    }
};

int main()
{
    // Time Complexity: O(n + m * log(n)) - Dijkstra's Algorithm
    int n, m, G;
    f >> n >> m >> G;
    Graph gr(n, m, G);
    f.close();
    gr.Dijkstra_Algorithm();
    g.close();
    return 0;
}
