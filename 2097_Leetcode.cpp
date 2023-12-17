#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

class Solution 
{
    vector<vector<int>> sol; // Solutia problemei.
    stack<int> revSol; // Stiva in care vom adauga nodurile in ordine inversa pt. constructia drumului.

    int findStartNode_(unordered_map<int, vector<int>>& gr, unordered_map<int, int>& inDeg, unordered_map<int, int>& outDeg) // O(n)
    {
        int node = 0;
        for (auto p = gr.begin(); p != gr.end(); p++)
        {
            node = p->first; // Current "key" in the Graph (unordered_map) which represents a node value.
            if (outDeg[node] - inDeg[node] == 1) // StartNode este reprezentat de nodul care "inchide" primul circuit, facand legatura cu un nod exterior primului circuit care poate fi inclus sau nu in cel de al 2-lea circuit.
                return node; // Am gasit nodul de start.
        }

        return node; // Daca graful initial reprezinta un intreg ciclu eulerian, atunci nodul de start poate fi oricare din cele existente (in cazul nostru este ultimul nod gasit in graful initial - "unordered_map").
    }
    void DFS_Edges_(unordered_map<int, vector<int>>& gr, const int node) // O(n + m)
    {
        while (!gr[node].empty()) // Scoatem, pe rand, toate muchiile grafului nostru (utilizand recursivitatea DFS-ului).
        {
            const int sz = gr[node].size();

            int last_neighb = gr[node][sz - 1]; 
            gr[node].pop_back(); // Scoatem ultimul nod curent adiacent nodului "node".
            DFS_Edges_(gr, last_neighb);
        }

        this->revSol.push(node); // Dupa prelucrarea tuturor apelurilor recursive de dupa nodul curent "node", vom adauga nodul in solutia problemei (Am folosit o stiva deoarece drumul valid de muchii va fi in ordine inversa).
    }
    void ArrangePairs_() // O(m)
    {
        while (!this->revSol.empty())
        {
            int aNode = this->revSol.top(); // Primul nod din varful stivei.
            this->revSol.pop();

            if (this->revSol.empty())
                break;

            int bNode = this->revSol.top(); // Urmatorul nod curent din varful stivei.
            this->sol.push_back({ aNode, bNode }); // Solutia problemei va include muchiile in ordinea parcurgerii lor in graf, nu a nodurilor si atat.
        }
    }

    //
    void PrintGraph_(unordered_map<int, vector<int>>& gr)
    {
        cout << "Graph:\n";

        for (auto p = gr.begin(); p != gr.end(); p++)
        {
            cout << p->first << " : ";

            for (const int edge : p->second)
            {
                cout << edge << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    void PrintDeg_(unordered_map<int, int>& Deg, const bool code)
    {
        if (!code)
            cout << "In-Degree number for each vertex:\n";
        else
            cout << "Out-Degree number for each vertex:\n";

        for (auto p = Deg.begin(); p != Deg.end(); p++)
        {
            cout << p->first << " : " << p->second << endl; // ( key : value ) in unordered_map (Deg).
        }
        cout << endl << endl;
    }
    //

public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) 
    {
        // Average O(1) operations in "unordered_maps" (Use it instead of normal vectors when dealing with a large range of node values).
        unordered_map<int, vector<int>> Graph;
        unordered_map<int, int> inDeg; // "In-Degree" values for each node in the Graph.
        unordered_map<int, int> outDeg; // "Out-Degree" values for each node in the Graph.

        for (const vector<int>& pair : pairs) // Just initializing the values for each "key" being inserted in the unordered_map (Graph).
        {
            for (int i = 0; i < 2; i++) // vector<int> pair = { start, end };
            {
                Graph[pair[i]] = {};
                inDeg[pair[i]] = 0;
                outDeg[pair[i]] = 0;
            }
        }

        for (const vector<int>& pair : pairs) // Constructing the Graph
        {
            Graph[pair[0]].push_back(pair[1]);
            inDeg[pair[1]]++;
            outDeg[pair[0]]++;
        }

        // PrintGraph_(Graph);
        // PrintDeg_(inDeg, false);
        // PrintDeg_(outDeg, true);

        int beginNode = findStartNode_(Graph, inDeg, outDeg); // Gasim nodul de start.
        DFS_Edges_(Graph, beginNode); // Construim drumul cu toate muchiile, in ordine inversa.
        ArrangePairs_(); // Inversam ordinea nodurilor conform eliminarii lor din stiva.

        return this->sol;
    }

    void PrintSol()
    {
        for (const vector<int>& pair : this->sol)
        {
            cout << "( " << pair[0] << ", " << pair[1] << " )\t";
        }
        cout << endl << endl;
    }
};

int main()
{
    // Time Complexity: O(n + m)
    // Auxiliary Space: O(n + m)
    //
    // Example 1:
    vector<vector<int>> pairs1 = { {5, 1}, {4, 5}, {11, 9}, {9, 4} };
    Solution s1;
    cout << "SOLUTION 1:\n\n";
    vector<vector<int>> sol1 = s1.validArrangement(pairs1);
    s1.PrintSol(); // [[11, 9], [9, 4], [4, 5], [5, 1]]

    // Example 2:
    vector<vector<int>> pairs2 = { {1, 3}, {3, 2}, {2, 1} };
    Solution s2;
    cout << "SOLUTION 2:\n\n";
    vector<vector<int>> sol2 = s2.validArrangement(pairs2);
    s2.PrintSol(); // [[1, 3], [3, 2], [2, 1]]

    // Example 3:
    vector<vector<int>> pairs3 = { {1, 2}, {1, 3}, {2, 1} };
    Solution s3;
    cout << "SOLUTION 3:\n\n";
    vector<vector<int>> sol3 = s3.validArrangement(pairs3);
    s3.PrintSol(); // [[1, 2], [2, 1], [1, 3]]

    return 0;
}

