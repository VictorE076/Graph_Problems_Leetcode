#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// "26" de litere (A-Z)

const int N = 26 * 26 * 26; // 26^3 = 17576 (the LIMIT of all possible combinations of 3 - letter airport names).

bool CompareDecodedAirports(const int a, const int b)
{
    return (a > b); // Descending order
}

class Solution
{
    vector<string> sol;

    int decode_airport_(const string& str) // O(1) - Fiecare combinatie de 3 litere (A-Z) corespunde unui cod (de tip int) transformat din baza "26".
    {
        return (int)((int)(str[0] - 'A') * 26 * 26 + (int)(str[1] - 'A') * 26 + (int)(str[2] - 'A')); 
    }
    string get_decoded_airport_(const int num) // O(1) - transformarea codului (int) inapoi in string-ul format din exact 3 litere (A-Z) in baza "26". 
    {
        // Prin impartiri repetate la "26" si luat resturile in ordinea inversa a impartirilor (ca la transformarile numerelor in baza "2"). 
        string temp[3];
        int divided_code = num;
        for (int c = 2; c >= 0; c--)
        {
            int rest = divided_code % 26;
            temp[c] = (char)(rest + 'A');
            divided_code = divided_code / 26;
        }

        return (temp[0] + temp[1] + temp[2]); // reconstructia string-ului format din exact 3 litere (A-Z) conform codului (int) dat ca parametru.
    }
    void swap_Strings_(string& str1, string& str2) // O(1)
    {
        string temp = str1;
        str1 = str2;
        str2 = temp;
    }

    void DFS_Edges_(vector<vector<int>>& gr, const int node) // O(m)
    {
        while(!gr[node].empty()) // Scoatem, pe rand, toate muchiile grafului nostru (utilizand recursivitatea DFS-ului).
        {
            const int count_edges = gr[node].size();
            const int last_neighb = gr[node][count_edges - 1];
            gr[node].pop_back(); // Scoatem ultimul nod adiacent nodului "node" (codul acestui vecin este cel mai mic la momentul actual).
            DFS_Edges_(gr, last_neighb);
        }

        this->sol.push_back(get_decoded_airport_(node)); // Dupa prelucrarea tuturor apelurilor recursive de dupa nodul curent "node", vom adauga aeroportul corespunzator codului curent al lui "node" in solutia problemei.
    }
    void ReverseSol_() // O(m) - Inversam vectorul ce reprezinta solutia problemei. 
    {
        const int sz = this->sol.size();
        const int middle = this->sol.size() >> 1;
        for (int i = 0; i < middle; i++)
        {
            swap_Strings_(this->sol[i], this->sol[(sz - 1) - i]);
        }
    }

    //
    void PrintGraph_(vector<vector<int>>& g)
    {
        cout << "Printing the Encrypted GRAPH:\n";
        const int sz = g.size();
        for (int i = 0; i < sz; i++)
        {
            if (g[i].empty())
                continue;

            cout << i << " : ";
            for (const int elem : g[i])
            {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    //

public:
    vector<string> findItinerary(vector<vector<string>>& tickets)
    {
        vector<vector<int>> Graph(N); // "26^3" possible distinct combinations of 3 letters (A-Z) representing the airports from input.

        for (const vector<string>& ticket : tickets)
        {
            int from = decode_airport_(ticket[0]);
            int to = decode_airport_(ticket[1]);
            Graph[from].push_back(to);
        }

        // PrintGraph_(Graph);

        for (int i = 0; i < N; i++)
        {
            sort(Graph[i].begin(), Graph[i].end(), CompareDecodedAirports); // Pentru fiecare nod "i" sortam descrescator dupa valoarea codurilor aeroporturilor ce reprezinta nodurile adiacente cu nodul "i".
        }

        // PrintGraph_(Graph);

        int from_JFK = decode_airport_("JFK"); // Toate solutiile incep cu aeroportul "JFK".
        DFS_Edges_(Graph, from_JFK); // DFS-ul nostru va scoate, pe rand, fiecare muchie din graful initial (de la final vectorului in timp constant, motiv pt. care am sortat descrescator fiecare vector de noduri adiacente nodului "i").  
        ReverseSol_(); // Vectorul de string-uri ce reprezinta solutia finala (itinerar) trebuie inversat. 

        // PrintGraph_(Graph);

        return this->sol;
    }

    void PrintSol()
    {
        for (const string& airport : this->sol)
        {
            cout << airport << " ";
        }
        cout << endl << endl;
    }
};

int main()
{
    // Time Complexity: O((N + m) * log(m))
    // Auxiliary Space: O(N + m)
    // 
    // Example 1:
    vector<vector<string>> v1 = { {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"} };
    Solution s1;
    cout << "SOLUTION 1:\n\n";
    vector<string> sol1 = s1.findItinerary(v1); // ["JFK", "MUC", "LHR", "SFO", "SJC"]
    s1.PrintSol();

    // Example 2:
    vector<vector<string>> v2 = { {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"} };
    Solution s2;
    cout << "SOLUTION 2:\n\n";
    vector<string> sol2 = s2.findItinerary(v2); // ["JFK", "ATL", "JFK", "SFO", "ATL", "SFO"]
    s2.PrintSol();

    return 0;
}

