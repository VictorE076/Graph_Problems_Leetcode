#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution {
    const int limit = (int)('z' + 1);
    void swap_(string& a, string& b)
    {
        string temp = b;
        b = a;
        a = temp;
    }
    void Equals_signs_first_(vector<string>& eq)
    {
        int sz_equals = 0;
        if (eq[0][1] == '=')
            sz_equals++;
        int sz_eq = eq.size();
        for (int i = 1; i < sz_eq; i++)
        {
            if (eq[i][1] == '=')
            {
                swap_(eq[sz_equals], eq[i]);
                sz_equals++;
            }
        }
    }
    const int ordL_(const char n)
    {
        return (int)(n - 'a');
    }
    int find_(int* parent, const int i)
    {
        int a = i;
        while (a != parent[a])
        {
            a = parent[a];
        }
        return a;
    }
    void union_(int* parent, const int x, const int y)
    {
        parent[x] = parent[y];
    }

public:
    void PrintEquations(vector<string>& eq)
    {
        int sz = eq.size();
        for (int i = 0; i < sz; i++)
        {
            cout << eq[i] << endl;
        }
        cout << endl;
    }
    bool equationsPossible(vector<string>& equations)
    {
        int* parent;
        parent = new int[limit];
        for (int i = 0; i < limit; i++)
        {
            parent[i] = i; 
        }
        Equals_signs_first_(equations); // Intai facem operatia UNION intre elementele egale, apoi decidem daca toate celelalte elemente diferite pot satisface simultan toate ecuatiile sau nu.
        // PrintEquations(equations);
        int sz = equations.size();
        for (int i = 0; i < sz; i++)
        {
            int x = ordL_(equations[i][0]), y = ordL_(equations[i][3]);
            char sign = equations[i][1];
            int x_root = find_(parent, x);
            int y_root = find_(parent, y);
            if (sign == '=')
            {
                if(x_root != y_root)
                    union_(parent, x_root, y_root);
            }
            else if (sign == '!')
            {
                if (x_root == y_root)
                {
                    delete[] parent;
                    return false;
                }
            }
        }
        delete[] parent;
        return true;
    }
};
int main()
{
    // Example 1:
    vector<string> equations1 = { "a==b", "b!=a" };
    Solution a1;
    cout << "Solution 1: " << a1.equationsPossible(equations1) << endl; // FALSE
    // Example 2:
    vector<string> equations2 = { "b==a", "a==b" };
    Solution a2;
    cout << "Solution 2: " << a2.equationsPossible(equations2) << endl; // TRUE
    return 0;
}
