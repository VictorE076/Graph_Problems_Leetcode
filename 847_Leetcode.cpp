#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>
#include <limits>
using namespace std;

const int MIN_LIMIT = INT_MIN;

class Solution 
{
    int shortestPath = 0;
    vector<int> powers2; // { 2^0, 2^1, 2^2, ..., 2^n } -- powers2[i] = 2^i

    void initialize_powers2_(const int n) // O(n)
    {
        int val = 1;
        this->powers2.push_back(val);
        
        for (int k = 1; k <= n; k++)
        {
            val = val << 1; // val = val * 2;
            this->powers2.push_back(val);
        }
    }

    //
    void Print_powers2_(const int n)
    {
        cout << "Powers_of_2 vector:\n";
        int index = 0;
        for (const int elem : this->powers2)
        {
            cout << "( " << index++ << ", " << elem << " )\t";
        }
        cout << "\n\n";
    }
    //

public:
    int shortestPathLength(vector<vector<int>>& graph) 
    {
        const int n = graph.size(); // "n" number of nodes in the undirected, connected graph;
        initialize_powers2_(n); // Precalculam toate puterile lui "2" incepand de la "2^0" pana la "2^n" inclusiv, a.i. pt. nodul "i" vom putea afla in O(1) valoarea "2^i".

        // Print_powers2_(n);

        vector<unordered_set<int>> visited(n); // Average O(1) for all operations in the vector of "unordered_sets"; 
        queue<pair<int, int>> q; // (node, position) - Each node (1 - n) can have a corresponding step (1 - (2^n-1)) - no duplicate steps (Dynamic Programming Approach to find the value of the shortest path visiting all nodes).
        for (int i = 0; i < n; i++)
        {
            q.push(make_pair(i, this->powers2[i])); // Putting all source vertices to the queue at first (first visitting all source vertices).
        }
        
        this->shortestPath = 0;

        while (!q.empty()) // Begin "Multisource BFS" loop
        {
            const int sz_q = q.size();
            for (int c = 0; c < sz_q; c++) // Prelucram toate elementele din coada (Multisource BFS), iar apoi incrementam distanta care ne va da rezultatul final la un moment dat.
            {
                int node = q.front().first;
                int position = q.front().second;
                q.pop();

                if (position >= this->powers2[n] - 1) // Primul nod a carui stare este mai mare sau egala cu "2^n-1", inseamna ca a epuizat toate posibilitatile de traversare ale drumului prin nodurile grafului, deci returnam "shortest_path" (distanta minima).
                    return this->shortestPath; // Am gasit drumul minim care trece prin toate nodurile grafului.

                if (visited[node].find(position) == visited[node].end()) // NOT found (the queue "q" does not contain duplicates).
                {
                    visited[node].insert(position); // Tuplul (node, position) nu a fost inca pus in "unordered_set[node]", asa ca il vom adauga acolo.

                    for (const int neighb : graph[node]) // Check the adjacent nodes for "node" in our graph.
                    {
                        int newPosition_OR = position | (this->powers2[neighb]); // Finding in O(1) the correct position (step) for the adjacent node "neighb" which might be inserted in the queue (Bitwise OR operator).

                        if (visited[neighb].find(newPosition_OR) == visited[neighb].end()) // NOT found (the queue "q" does not contain duplicates).
                        {
                            q.push(make_pair(neighb, newPosition_OR)); // Adaugam vecinul lui "node", precum si pozitia corecta a acestuia in coada (doar in cazul in care nu a fost niciodata adaugat in coada pana in acel moment, pt. a fi procesat).
                        }
                    }
                }
            }

            this->shortestPath++; // Increment the distance. The "Multisource BFS" approach will visit the vertices which are at a distance of "1" from all source vertices, then at a distance of "2" from all source vertices and so on and so forth.
        }
        
        return MIN_LIMIT;
    }
};

int main()
{
    // Time Complexity: O(n * 2^n).
    // Auxiliary Space: O(n * 2^n).
    //
    // Example 1:
    vector<vector<int>> gr1 = { {1, 2, 3}, {0}, {0}, {0} };
    Solution s1;
    cout << "SOLUTION 1: " << s1.shortestPathLength(gr1) << endl << endl; // 4

    // Example 2:
    vector<vector<int>> gr2 = { {1}, {0, 2, 4}, {1, 3, 4}, {2}, {1, 2} };
    Solution s2;
    cout << "SOLUTION 2: " << s2.shortestPathLength(gr2) << endl << endl; // 4

    return 0;
}
