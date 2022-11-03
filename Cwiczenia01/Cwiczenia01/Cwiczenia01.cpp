#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

double* ZeroArray(int size)
{
    double* arrayData = new double[size];
    for (int i = 0; i < size; i++)
    {
        arrayData[i] = 0;
    }
    return arrayData;
}

struct Matrix
{
    int Width;
    int Height;
    double* Data;
    Matrix(int width, int height, double* data)
    {
        Width = width;
        Height = height;
        Data = data;
    }

    double Get(int x, int y)
    {
        return Data[(x * Width) + y];
    }

    void Set(int x, int y, double value)
    {
        Data[(x * Width) + y] = value;
    }

    void ExchangeRows(int from, int to)
    {
        for (int i = 0; i < Width; i++)
        {
            double v1 = Get(from, i);
            double v2 = Get(to, i);
            Set(from, i, v2);
            Set(to, i, v1);
        }
    }

    void Print()
    {
        /*cout << "Height:" << Height << endl;
        cout << "Width:" << Width << endl;*/

        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                cout << Get(i, j) << "     ";
            }
            cout << endl;
        }
    }

    bool HasDiagonalZero()
    {
        for (int i = 0; i < Height; i++)
        {
            if (Get(i, i) == 0)
            {
                return true;
            }
        }
        return false;
    }
    void CheckDiagonalZero()
    {
        if (HasDiagonalZero())
        {
            throw "Matrix has diagonal 0!";
        }
    }

    Matrix Clone()
    {
        double* arrayData = ZeroArray(Height * Width);
        Matrix cloned = Matrix(Width, Height, arrayData);
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                cloned.Set(i, j, Get(i, j));
            }
        }
        return cloned;
    }

    Matrix Clone(int width, int height)
    {
        double* arrayData = ZeroArray(height * width);
        Matrix cloned = Matrix(width, height, arrayData);
        for (int i = 0; i < min(height, Height); i++)
        {
            for (int j = 0; j < min(width, Width); j++)
            {
                cloned.Set(i, j, Get(i, j));
            }
        }
        return cloned;
    }

    Matrix Clone(int width, int height, int offsetWidth, int offsetHeight)
    {
        double* arrayData = ZeroArray(height * width);
        Matrix cloned = Matrix(width, height, arrayData);
        for (int i = offsetHeight; i < min(height, Height) + offsetHeight; i++)
        {
            for (int j = offsetWidth; j < min(width, Width) + offsetWidth; j++)
            {
                cloned.Set(i - offsetWidth, j - offsetHeight, Get(i, j));
            }
        }
        return cloned;
    }

    Matrix Reversed()
    {
        double* arrayData = ZeroArray(Height * Width);
        Matrix cloned = Matrix(Width, Height, arrayData);
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                double val = Get(i, j);
                if(val != 0)
                    cloned.Set(i, j, 1/val);
            }
        }
        return cloned;
    }

    Matrix Diagonal()
    {
        double* arrayData = ZeroArray(Height * Width);
        Matrix cloned = Matrix(Width, Height, arrayData);
        for (int i = 0; i < min(Height, Width); i++)
        {
            cloned.Set(i, i, Get(i, i));
        }
        return cloned;
    }

    Matrix Triagonal()
    {
        double* arrayData = ZeroArray(Height * Width);
        Matrix cloned = Matrix(Width, Height, arrayData);
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                if(i != j)
                    cloned.Set(i, j, Get(i, j));
            }
        }
        return cloned;
    }

    Matrix Add(Matrix b)
    {
        double* arrayData = ZeroArray(Height * Width);
        Matrix cloned = Matrix(Width, Height, arrayData);
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                cloned.Set(i, j, Get(i, j) + b.Get(i, j));
            }
        }
        return cloned;
    }

    Matrix Multiply(double val)
    {
        double* arrayData = ZeroArray(Height * Width);
        Matrix cloned = Matrix(Width, Height, arrayData);
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                cloned.Set(i, j, Get(i, j) * val);
            }
        }
        return cloned;
    }

    Matrix Multiply(Matrix b)
    {
        double* arrayData = ZeroArray(Height * b.Width);
        Matrix cloned = Matrix(b.Width, Height, arrayData);
        for (int i = 0; i < cloned.Height; i++)
        {
            for (int j = 0; j < cloned.Width; j++)
            {
                double val = 0;
                for (int z = 0; z < max(cloned.Height, cloned.Width); z++)
                {
                    val += Get(i, z) * b.Get(z, j);
                }
                cloned.Set(i, j, val);
            }
        }
        return cloned;
    }

    static Matrix LoadData(string file)
    {
        fstream plik;
        double wyraz;

        plik.open(file, ios::in | ios::out);

        int height;

        plik >> height;

        int width = height + 1;

        double* arrayData = new double[height * width];

        for (int i = 0; i < (height * width); i++)
        {
            plik >> wyraz;
            arrayData[i] = wyraz;
        }
        plik.close();

        Matrix matrix = Matrix(width, height, arrayData);
        matrix.Print();
        matrix.CheckDiagonalZero();
        return matrix;
    }
};

void ReversedGause(Matrix matrix)
{
    double* xs = new double[matrix.Height];
    for (int i = matrix.Height - 1; i >= 0; i--)
    {
        double b = matrix.Get(i, matrix.Width - 1);
        double a = matrix.Get(i, i);
        double sum = 0;
        for (int k = matrix.Height - 1; k > i; k--)
        {
            sum += matrix.Get(i, k) * xs[k];
        }
        double x = (b - sum) / a;
        xs[i] = x;
    }
    for (int i = 0; i < matrix.Height; i++)
    {
        cout << "x" << i << "=" << xs[i] << endl;
    }
}

void GaussaEliminationSingleColumn(Matrix matrix, int i)
{
    for (int j = i + 1; j < matrix.Height; j++)
    {
        double m = matrix.Get(j, i) / matrix.Get(i, i);
        for (int x = i; x < matrix.Width; x++)
        {
            double newData = matrix.Get(j, x) - (matrix.Get(i, x) * m);
            matrix.Set(j, x, newData);
        }
    }
    if (matrix.HasDiagonalZero())
    {
        throw "Matrix has diagonal 0!";
    }
}

void GaussaElimination(Matrix matrix)
{
    for (int i = 0; i < matrix.Width; i++)
    {
        GaussaEliminationSingleColumn(matrix, i);
    }
    matrix.Print();
}

void GaussaEliminationWithPivoting(Matrix matrix)
{
    for (int i = 0; i < matrix.Width; i++)
    {
        int maxIndex = i;
        for (int j = i; j < matrix.Height; j++)
        {
            if (matrix.Get(j, i) > matrix.Get(maxIndex, i))
                maxIndex = j;
        }
        if (maxIndex != i)
            matrix.ExchangeRows(i, maxIndex);

        GaussaEliminationSingleColumn(matrix, i);
    }
    matrix.Print();
}

void CheckDiagonaloyStrong(Matrix matrix)
{
    for (int i = 0; i < matrix.Height; i++)
    {
        double valDiag = matrix.Get(i, i);
        for (int j = 0; j < matrix.Width-1; j++)
        {
            if (i == j)
                continue;

            if(matrix.Get(i, j) >= valDiag)
                throw "Matrix is not diagonally strong!";
        }
    }
}


void SimpleGause(Matrix matrix)
{
    GaussaElimination(matrix);
    ReversedGause(matrix);
}


void Jacobiego(Matrix matrix)
{
    CheckDiagonaloyStrong(matrix);

    Matrix LU = matrix.Clone(matrix.Height, matrix.Height).Triagonal();                     cout << "LU!-----------------------------------------------------------------------" << endl; LU.Print();
    Matrix D_reversed = matrix.Clone(matrix.Height, matrix.Height).Diagonal().Reversed();   cout << "D_reversed!---------------------------------------------------------------" << endl; D_reversed.Print();
    Matrix b = matrix.Clone(1, matrix.Height, matrix.Height, 0);                            cout << "b!------------------------------------------------------------------------" << endl; b.Print();
    Matrix P = D_reversed.Multiply(-1).Multiply(LU);                                        cout << "P!------------------------------------------------------------------------" << endl; P.Print();
    Matrix q = D_reversed.Multiply(b);                                                      cout << "q!------------------------------------------------------------------------" << endl; q.Print();

    int iterations = 5;
    cout << "How many iterations? " << endl;
    cin >> iterations;
    Matrix x = q.Clone();                                                                   cout << "x[0]:" << endl; x.Print();
    for (int i = 0; i < iterations-1; i++)
    {
        x = P.Multiply(x).Add(q);                                                           cout << "x[" << i+1 << "]:----------------------" << endl; x.Print();
    }
    cout << "Result!-------------------------------------------------------------------" << endl;
    for (int i = 0; i < x.Height; i++)
    {
        cout << "x" << i << "=" << x.Get(0, i) << endl;
    }
}

void Pivoting(Matrix matrix)
{
    GaussaEliminationWithPivoting(matrix);
    ReversedGause(matrix);
}


int mainData()
{
    cout << "Case:";
    int caseId = 3;
    //cin >> caseId;
    cout << endl << "Selected: " << caseId << endl;

    if (caseId == 1)
    {
        Matrix matrix = Matrix::LoadData("dane1_2.txt");
        cout << "Simple Gause!" << endl;
        SimpleGause(matrix);
        return 0;
    }

    if (caseId == 2)
    {
        Matrix matrix = Matrix::LoadData("dane2_1.txt");
        cout << "Jacobiego!" << endl;
        Jacobiego(matrix);
        return 0;
    }

    if (caseId == 3)
    {
        Matrix matrix = Matrix::LoadData("dane3_1.txt");
        cout << "Gause with pivot!" << endl;
        Pivoting(matrix);
        return 0;
    }


    cout << "Wrong case!" << endl;
    return -1;
}

int main()
{
    try {
        return mainData();
    }
    catch (...) {
        //cout << e << endl;
        return -2;
    }
}