#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
using namespace std;
//ifstream f("padure.in.txt");
//ofstream g("padure.out.txt");
ifstream f("padure.in");
ofstream g("padure.out");

const int limit = 2147483647;
const int x_axis[4] = { -1, 0, 1, 0 };
const int y_axis[4] = { 0, 1, 0, -1 };

class Matrix {
    const int n, m, pl, pc, cl, cc;
    int** mat;
public:
    Matrix() = delete;
    Matrix(const int n, const int m, const int pl, const int pc, const int cl, const int cc)
        : n(n), m(m), pl(pl), pc(pc), cl(cl), cc(cc)
    {
        mat = new int* [this->n];
        for (int i = 0; i < this->n; i++)
        {
            mat[i] = new int[this->m];
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < this->n; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
    }
    //
    void Read()
    {
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                f >> this->mat[i][j];
            }
        }
    }
    void Print()
    {
        cout << this->pl << " " << this->pc << " " << this->cl << " " << this->cc << endl << endl;
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                cout << this->mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    //
private:
    // !! Folosim un deque sau priority_queue pentru a scoate mereu din coada, indicii a caror distanta este minima
    // !! Alegem un deque deoarece vom avea doar perechi de indici cu distante ( d si/sau d + 1 ) in coada, 
    // reducand astfel complexitatea la O(1) per operatie in deque.
    void Lee_Algorithm_(int** d)
    {
        deque<pair<int, int>> dq;
        d[this->pl][this->pc] = 0;
        dq.push_back(make_pair(this->pl, this->pc));
        while (!dq.empty())
        {
            int x = dq.front().first;
            int y = dq.front().second;
            dq.pop_front();
            for (int c = 0; c < 4; c++)
            {
                int xi = x + x_axis[c];
                int yi = y + y_axis[c];
                if (!(-1 < xi && xi < n && -1 < yi && yi < m))
                    continue;
                int correct_pos_dis;
                if (this->mat[x][y] == this->mat[xi][yi])
                    correct_pos_dis = d[x][y];
                else
                    correct_pos_dis = d[x][y] + 1;
                if (d[xi][yi] <= correct_pos_dis)
                    continue;
                d[xi][yi] = correct_pos_dis;
                if (dq.empty())
                {
                    dq.push_front(make_pair(xi, yi));
                    continue;
                }
                int front_x = dq.front().first;
                int front_y = dq.front().second;
                if (d[xi][yi] > d[front_x][front_y])
                    dq.push_back(make_pair(xi, yi));
                else
                    dq.push_front(make_pair(xi, yi));
            }
        }
    }
public:
    int Sol_Minimum_Diamonds()
    {
        int solution = limit;
        int** distance;
        distance = new int* [this->n];
        for (int i = 0; i < this->n; i++)
        {
            distance[i] = new int[this->m];
        }
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                distance[i][j] = limit;
            }
        }
        Lee_Algorithm_(distance);
        solution = distance[this->cl][this->cc];
        for (int i = 0; i < this->n; i++)
        {
            delete[] distance[i];
        }
        delete[] distance;
        return solution;
    }

};
int main()
{
    int n, m, pl, pc, cl, cc;
    f >> n >> m >> pl >> pc >> cl >> cc;
    Matrix ma(n, m, pl - 1, pc - 1, cl - 1, cc - 1);
    ma.Read();
    // ma.Print();
    int sol = ma.Sol_Minimum_Diamonds();
    g << sol;
    f.close();
    g.close();
    return 0;
}


