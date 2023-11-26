#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
//ifstream f("bile.in.txt");
//ofstream g("bile.out.txt");
ifstream f("bile.in");
ofstream g("bile.out");

class Tabla
{
    const int n;
    vector<vector<bool>> tabla;
    vector<pair<int, int>> ind;
    const int x_axis[4] = { -1, 0, 1, 0 };
    const int y_axis[4] = { 0, 1, 0, -1 };
    int max_dim;

    bool check_borders_(const int a, const int b)
    {
        if (a < 0 || a >= this->n || b < 0 || b >= this->n)
            return false;
        return true;
    }

    int maxim_(const int a, const int b)
    {
        if (a > b)
            return a;
        return b;
    }

    int find_(const int node, vector<int>& parent)
    {
        if (node == parent[node])
            return node;
        return parent[node] = find_(parent[node], parent);
    }

    void union_(vector<int>& parent, vector<int>& rank, vector<int>& num_nodes, const int x, const int y)
    {
        int px = find_(x, parent);
        int py = find_(y, parent);
        if (px == py)
            return;
        if (rank[px] < rank[py])
        {
            parent[px] = py;
            num_nodes[py] += num_nodes[px];
            this->max_dim = maxim_(this->max_dim, num_nodes[py]);
        }
        else if (rank[py] < rank[px])
        {
            parent[py] = px;
            num_nodes[px] += num_nodes[py];
            this->max_dim = maxim_(this->max_dim, num_nodes[px]);
        }
        else
        {
            parent[py] = px;
            rank[px]++;
            num_nodes[px] += num_nodes[py];
            this->max_dim = maxim_(this->max_dim, num_nodes[px]);
        }
    }
public:
    Tabla() = delete;
    Tabla(const int n) : n(n), max_dim(1)
    {
        for (int i = 0; i < this->n; i++)
        {
            this->tabla.push_back({});
            for (int j = 0; j < this->n; j++)
            {
                this->tabla[i].push_back(false);
            }
        }
        int l, c;
        for (int i = 0; i < this->n * this->n; i++)
        {
            f >> l >> c;
            this->ind.push_back(make_pair(l - 1, c - 1));
        }
    }
    ~Tabla() = default;
    ///
    void Bile()
    {
        // Putem trata matricea de (n * n) ca array pentru usurinta calculelor (in special pentru operatiile de tip Union-Find).
        vector<int> parent(this->n * this->n);
        vector<int> rank(this->n * this->n, 0);
        vector<int> num_nodes(this->n * this->n, 1);
        for (int i = 0; i < this->n * this->n; i++)
        {
            parent[i] = i;
        }
  
        stack<int> st;
        for (int i = (this->n * this->n) - 1; i >= 0; i--) 
        {
            if (i == (this->n * this->n) - 1)
                st.push(0); // Nu avem nicio bila pe tabla in final.
            else    
                st.push(this->max_dim);
            
            for (int c = 0; c < 4; c++) // Este mai usor sa "introducem" elementele pe tabla, in loc sa le "stergem" deoarece astfel putem folosi Union_Find pentru eficienta.
            {
                // Luam coordonatele fiecarui vecin al elementului (bilei) care urmeaza sa fie pusa pe tabla (matrice).
                int xc = this->ind[i].first + x_axis[c];
                int yc = this->ind[i].second + y_axis[c];
                
                if (!check_borders_(xc, yc) || this->tabla[xc][yc] == false)
                    continue; // Ignoram elementele (bilele) puse pe tabla (matrice), precum si indicii care nu se afla in interiorul tablei (matricei). 
                
                union_(parent, rank, num_nodes, this->ind[i].first * this->n + this->ind[i].second, xc * this->n + yc); // Union_Find intre elementul curent (bila care urmeaza sa fie pusa pe tabla) si toti vecinii (stanga, sus, dreapta, jos) acestuia.
            }

            this->tabla[ind[i].first][ind[i].second] = true; // Marcam "true" pozitia in care am introdus elementul curent (bila) pe tabla (matrice).
        }

        while (!st.empty()) // Solutia corecta este in ordine inversa deoare cerinta este sa "scoatem" elementele de pe tabla, nu sa le "introducem".
        {
            g << st.top() << endl;
            st.pop();
        }
    }
};

int main()
{
    // Time Complexity: O(n * n * log*(n)) - Union_Find Structure.
    int n;
    f >> n;
    Tabla t(n);
    f.close();
    t.Bile();
    g.close();
    return 0;
}
