#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip> // for aproximations
#include <limits>
#include <float.h>
using namespace std;
//ifstream f("cablaj.in.txt");
//ofstream g("cablaj.out.txt");
ifstream f("cablaj.in");
ofstream g("cablaj.out");
const double MAX_LIMIT = DBL_MAX;
class coordinates
{
    const int n;
    pair<int, int>* co;
    double get_distance_(const int xi, const int yi, const int xj, const int yj)
    {
        return (double)(sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj)));
    }
    int get_min_dst_node_(double* dst, bool* visited)
    {
        double minimum = (double)(MAX_LIMIT);
        int selected_node = -1;
        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                continue;
            if ((double)(dst[i]) < (double)(minimum))
            {
                minimum = (double)(dst[i]);
                selected_node = i;
            }
        }
        return selected_node;
    }
public:
    coordinates() = delete;
    coordinates(const int n) : n(n)
    {
        co = new pair<int, int>[n];
        for (int i = 0; i < n; i++)
        {
            f >> co[i].first >> co[i].second;
        }
    }
    //
    void print_coordinates()
    {
        for (int i = 0; i < n; i++)
        {
            cout << co[i].first << " " << co[i].second << endl;
        }
        cout << endl << endl;
    }
    //
    void Prim_Algorithm()
    {
        double total_cost = 0;
        double* dist;
        bool* visited;
        dist = new double[this->n];
        visited = new bool[this->n];
        for (int i = 0; i < this->n; i++)
        {
            dist[i] = (double)(MAX_LIMIT);
            visited[i] = false;
        }
        dist[0] = 0; // Incepem de la nodul "0"
        for (int i = 0; i < n; i++)
        {
            int min_chosen = get_min_dst_node_(dist, visited);
            if (min_chosen == -1)
                continue;
            visited[min_chosen] = true;
            total_cost += (double)(dist[min_chosen]);
            for (int j = 0; j < n; j++)
            {
                if (min_chosen == j || visited[j])
                    continue; // Ignoram muchia de la un nod la el insusi, precum si nodurile deja vizitate
                double distance = get_distance_(co[min_chosen].first, co[min_chosen].second, co[j].first, co[j].second);
                // cout << min_chosen << " " << j << " -> " << distance << endl;
                if ((double)(distance) < (double)(dist[j]))
                {
                    dist[j] = (double)(distance);
                }
            }
            // cout << total_cost << endl;
        }
        g << setprecision(3) << fixed << total_cost << endl;
        delete[] dist;
        delete[] visited;
    }
    ~coordinates()
    {
        delete[] co;
    }
};
int main()
{
    // Time Complexity: O(n^2) - Using Prim's Algorithm
    int n;
    f >> n;
    coordinates sol(n);
    f.close();
    // sol.print_coordinates();
    sol.Prim_Algorithm();
    g.close();
    return 0;
}
