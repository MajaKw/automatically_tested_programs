#include <iostream>
#include <string>

using namespace std;

class matrix
{
private:
    short int row;
    short int col;
    short int** m;

public:
    matrix(int a = 0, int b = 0)
    {
        row = a;
        col = b;
        m = new short int* [row];
        for (int i = 0; i < row; ++i)
        {
            m[i] = new short int[col];
            for (int j = 0; j < col; ++j)
            {
                m[i][j] = 0;
            }
        }
    }
    matrix(const matrix& mtrx)
    {
        row = mtrx.row;
        col = mtrx.col;
        m = new short int* [row];
        for (int i = 0; i < row; ++i)
        {
            m[i] = new short int[col];
            for (int j = 0; j < col; ++j)
            {
                m[i][j] = mtrx.m[i][j];
            }
        }
    }
    ~matrix()
    {
        if (row != 0 && col != 0)
        {
            for (int i = 0; i < row; ++i)
            {
                delete[] m[i];
            }
            delete[] m;
        }
    }
    void operator=(const matrix& A)
    {
        if (A.col != col || A.row != row)
        {
            for (int i = 0; i < row; i++)
                delete[] m[row];
            delete[] m;
            row = A.row;
            col = A.col;
            m = new short int* [row];
            for (int i = 0; i < row; i++)
                m[i] = new short int[col];
        }

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                m[i][j] = A.m[i][j];
            }
        }
    }
    int get_row()
    {
        return row;
    }

    matrix initialize(int r, int c, int n)
    {
        int i = 0;
        int j = 0;
        matrix C(n - 1, n - 1);
        for (int x = 0; x < n; ++x)
        {
            j = 0;
            if (x != r)
            {
                for (int y = 0; y < n; ++y)
                {
                    if (y != c)
                    {
                        C.m[i][j] = m[x][y];
                        ++j;
                    }
                }
                ++i;
            }
        }
        return C;
    }

    int find_max_zeros()
    {
        int max = 0;
        int curr = 0;
        int which_row = 0;
        for (int i = 0; i < row; ++i)
        {
            curr = 0;
            for (int j = 0; j < col; ++j)
            {
                if (m[i][j] == 0)
                    ++curr;
                if (curr > max)
                {
                    curr = max;
                    which_row = i;
                }
            }
        }
        return which_row;
    }
    long long determinant()
    {
        long long sum = 0;
        if (row != col)
        {
            string error = "ERROR DETERMINANT";
            throw error;
        }
        if (row == 1)
        {
            return (long long)m[0][0];
        }
        else
        {
            long long sgn;
            int nr_row = find_max_zeros();
            for (int i = 0; i < row; ++i)
            {
                if ((i + nr_row) % 2 == 0)
                    sgn = 1;
                else
                    sgn = -1;
                if (m[nr_row][i] != 0)
                {
                    matrix sub = initialize(nr_row, i, row);
                    long long val = sub.determinant();
                    sum += (long long)m[nr_row][i] * val * sgn;
                }
            }
            return sum;
        }
    }

    void id()
    {
        for (int i = 0; i < row; ++i)
        {
            ++m[i][i];
        }
    }

    friend ostream& operator<<(ostream& out, const matrix& A);
    friend istream& operator>>(istream& in, const matrix& A);
    friend matrix operator+(const matrix& A, const matrix& B);
    friend matrix operator-(const matrix& A, const matrix& B);
    friend matrix operator*(const matrix& A, const matrix& B);
    friend matrix operator^(const matrix& A, int p);
};

istream& operator>>(istream& in, const matrix& A)
{
    for (int i = 0; i < A.row; ++i)
    {
        for (int j = 0; j < A.col; ++j)
        {
            in >> A.m[i][j];
        }
    }
    return in;
}
ostream& operator<<(ostream& out, const matrix& A)
{
    for (int i = 0; i < A.row; ++i)
    {
        for (int j = 0; j < A.col; ++j)
        {
            out << A.m[i][j] << " ";
        }
        out << endl;
    }
    return out;
}
matrix operator+(const matrix& A, const matrix& B)
{
    if (A.row != B.row || A.col != B.col)
    {
        string err = "ERROR ADD";
        throw err;
    }

    matrix C(A.row, A.col);
    for (int i = 0; i < A.row; ++i)
    {
        for (int j = 0; j < A.col; ++j)
        {
            C.m[i][j] = (A.m[i][j] + B.m[i][j]) % 1000;
        }
    }
    return C;
}

matrix operator*(const matrix& A, const matrix& B)
{
    if (A.col != B.row)
    {
        string err = "ERROR MULTIPLY";
        throw err;
    }
    matrix C(A.row, B.col);
    for (int i = 0; i < A.row; ++i)
    {
        for (int k = 0; k < B.row; ++k)
        {
            for (int j = 0; j < B.col; ++j)
            {
                C.m[i][j] = (C.m[i][j] + A.m[i][k] * B.m[k][j]) % 1000;
            }
        }
    }
    return C;
}

matrix operator^(const matrix& A, int p)
{
    if (A.row != A.col)
    {
        string err = "ERROR POWER";
        throw err;
    }
    int bits = 0;
    int p_temp = p;
    while (p != 0)
    {
        if ((p & 1) == 1)
            ++bits;
        p >>= 1;
    }
    p = p_temp;
    matrix temp(A);
    matrix result(A.row, A.col);
    result.id();
    while (p > 0)
    {
        int check = p & 1;
        if (check == 1)
        {
            result = result * temp;
        }
        p >>= 1;
        temp = temp * temp;
    }
    return result;
}

int main()
{
    int z;
    cin >> z;
    for (int i = 0; i < z; ++i)
    {
        string operation;
        int pow;
        cin >> operation;
        if (operation == "POWER")
        {
            cin >> pow;
        }
        int row_A, col_A;
        cin >> row_A >> col_A;
        matrix A(row_A, col_A);
        cin >> A;
        if (operation == "POWER")
        {
            matrix C(row_A, col_A);
            try
            {
                C = A ^ pow;
            }
            catch (string err)
            {
                cout << err << endl;
                continue;
            }
            cout << C;
        }
        if (operation == "DETERMINANT")
        {
            long long det;
            try
            {
                det = A.determinant();
            }
            catch (string err)
            {
                cout << err << endl;
                continue;
            }
            cout << det << endl;
        }
        if (operation == "ADD" || operation == "MULTIPLY")
        {
            int row_B, col_B;
            cin >> row_B >> col_B;
            matrix B(row_B, col_B);
            cin >> B;
            if (operation == "ADD")
            {
                matrix C(row_A, col_A);
                try
                {
                    C = A + B;
                }
                catch (string err)
                {
                    cout << err << endl;
                    continue;
                }
                cout << C;
            }
            else if (operation == "MULTIPLY")
            {
                matrix C(row_A, col_B);
                try
                {
                    C = A * B;
                }
                catch (string err)
                {
                    cout << err << endl;
                    continue;
                }
                cout << C;
            }
        }
    }
}
