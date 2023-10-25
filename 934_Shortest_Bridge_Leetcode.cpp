#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Solution {
    const int X_axis[4] = { -1, 0, 1, 0 };
    const int Y_axis[4] = { 0, 1, 0, -1 };
    queue<pair<int, int>> q;
    void explore_first_island_Lee_(vector<vector<int>>& grid, bool** visited, int i, int j, const int n)
    {
        q.push(make_pair(i, j));
        visited[i][j] = true;
        while (!q.empty())
        {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int xi = x + X_axis[k];
                int yi = y + Y_axis[k];
                if (!(-1 < xi && xi < n && -1 < yi && yi < n))
                    continue;
                if (grid[xi][yi] && !visited[xi][yi])
                {
                    q.push(make_pair(xi, yi));
                    visited[xi][yi] = true;
                }
            }
        }
        for (int k = 0; k < n; k++)
        {
            for (int l = 0; l < n; l++)
            {
                if (!visited[k][l])
                    continue;
                q.push(make_pair(k, l));
            }
        }
    }
    pair<int, int> first_island_(vector<vector<int>>& grid, bool** visited, const int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    return make_pair(i, j);
                }
            }
        }
        return make_pair(-1, -1);
    }
    int shortest_bridge_(vector<vector<int>>& grid, bool** visited, const int n)
    {
        int closest = 0;
        while (!q.empty())
        {
            int sz = q.size();
            for(int c = 0; c < sz; c++)
            {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int xi = x + X_axis[k];
                    int yi = y + Y_axis[k];
                    if (!(-1 < xi && xi < n && -1 < yi && yi < n && !visited[xi][yi]))
                        continue;
                    if (grid[xi][yi] == 1)
                        return closest;
                    q.push(make_pair(xi, yi));
                    visited[xi][yi] = true;
                }
            }
            closest++;
        }
        return closest;
    }
public:
    int shortestBridge(vector<vector<int>>& grid) 
    {
        const int n = grid.size();
        bool** visited;
        visited = new bool* [n];
        for (int i = 0; i < n; i++)
        {
            visited[i] = new bool[n];
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
            }
        }
        pair<int, int> coordinates = first_island_(grid, visited, n);
        explore_first_island_Lee_(grid, visited, coordinates.first, coordinates.second, n);
        int sol = shortest_bridge_(grid, visited, n);
        for (int i = 0; i < n; i++)
        {
            delete[] visited[i];
        }
        delete[] visited;
        return sol;
    }
};
int main()
{
    // Example 1:
    vector<vector<int>> grid1 = { {0, 1}, {1, 0} };
    Solution s1;
    cout << "Solution 1: " << s1.shortestBridge(grid1) << endl;
    //
    // Example 2:
    vector<vector<int>> grid2 = { {0, 1, 0}, {0, 0, 0}, {0, 0, 1} };
    Solution s2;
    cout << "Solution 2: " << s2.shortestBridge(grid2) << endl;
    //
    // Example 3:
    vector<vector<int>> grid3 = { {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1} };
    Solution s3;
    cout << "Solution 3: " << s3.shortestBridge(grid3) << endl;
    return 0;
}
