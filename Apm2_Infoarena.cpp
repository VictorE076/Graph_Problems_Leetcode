#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <limits>
using namespace std;

ifstream f("apm2.in.txt");
ofstream g("apm2.out.txt");
//ifstream f("apm2.in");
//ofstream g("apm2.out");

const int MIN_LIMIT = INT_MIN;
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
    /// 
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
        ///
    }
    ~Graph() = default;
    //
    void PrintEdges()
    {
        for (int i = 0; i < this->m; i++)
        {
            cout << this->edges[i][0] << " " << this->edges[i][1] << " " << this->edges[i][2] << endl;
        }
        cout << endl << endl;
    }
    //
    ///
};
int main()
{
    // Time Complexity: O(...)
    int n, m, Q;
    f >> n >> m >> Q;
    // cout << n << " " << m << " " << Q << endl;
    Graph gr(n, m, Q);
    f.close();
    ///
    g.close();
    // gr.PrintEdges();
    return 0;
}
