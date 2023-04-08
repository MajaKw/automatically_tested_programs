#include <iostream>
#include <queue>

using namespace std;

class WSP
{
public:
    int x;
    int y;
    WSP(int a = 0, int b = 0)
    {
        x = a;
        y = b;
    }
};

int main()
{

    int z;
    cin >> z;
    while (z--) {

        int n, m;
        int max = 0;
        cin >> n >> m;
        int** H = new int* [n];
        int** A = new int* [n];
        for (int i = 0; i < n; ++i)
        {
            H[i] = new int[m];
            A[i] = new int[m];
            for (int j = 0; j < m; ++j)
            {
                cin >> H[i][j];
                if (H[i][j] > max)
                {
                    max = H[i][j];
                }
                A[i][j] = 0;
            }
        }
        int wyw_x, wyw_y, schr_x, schr_y;
        cin >> wyw_y >> wyw_x >> schr_y >> schr_x;
        WSP wyw(wyw_x - 1, wyw_y - 1);
        WSP schr(schr_x - 1, schr_y - 1);
        WSP start(wyw.x, wyw.y);
        WSP ruch[4];
        ruch[0] = WSP(0, 1);
        ruch[1] = WSP(1, 0);
        ruch[2] = WSP(0, -1);
        ruch[3] = WSP(-1, 0);

        int begin = H[schr.y][schr.x];
        int end = max;
        int woda = -1;

        while (begin <= end)
        {
            queue <WSP> kolejka;
            kolejka.push(start);
            int mid = (begin + end) / 2;
            int schronisko = 0;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    A[i][j] = 0;
                }
            }

            while (!kolejka.empty())
            {

                WSP temp = kolejka.front();
                kolejka.pop();
                A[temp.y][temp.x] = 1;
                for (int i = 0; i < 4; ++i)
                {
                    if (temp.y == schr.y && temp.x == schr.x)
                    {
                        schronisko = 1;
                        break;
                    }
                    // boundaries
                    int b = temp.y + ruch[i].y;
                    int a = temp.x + ruch[i].x;
                    if (a >= m || a < 0 || b >= n || b < 0)
                    {
                        continue;
                    }
                    // check if I was there already
                    if (A[b][a] == 1)
                    {
                        continue;
                    }
                    // check height
                    if (H[b][a] > mid)
                    {
                        A[b][a] = 1;
                        continue;
                    }
                    A[b][a] = 1;
                    WSP dobry(a, b);
                    kolejka.push(dobry);

                } // for
            } // while(!kolejka.empty())
            if (schronisko == 1)
            { // mistake
                end = mid - 1;
                woda = mid;
            }
            else
            {
                begin = mid + 1;
            }
        } // while
        if (woda == -1)
        {
            cout << "ERROR" << endl;
        }
        else
        {
            cout << woda << endl;
        }

        for (int i = 0; i < n; ++i) {
            delete H[i];
            delete A[i];
        }
        delete A;
        delete H;

    }
}