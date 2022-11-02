#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

    void Print()
    {
        cout << "Height:" << Height << endl;
        cout << "Width:" << Width << endl;

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

    static Matrix LoadData(string file)
    {
        fstream plik;
        int wyraz;

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

        return Matrix(width, height, arrayData);
    }
};

void SimpleGause(Matrix matrix)
{
    for (int i = 0; i < matrix.Height; i++)
    {
        for (int j = i+1; j < matrix.Height; j++)
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
    matrix.Print();
    double* xs = new double[matrix.Height];

    for (int i = matrix.Height-1; i >= 0; i--)
    {
        double b = matrix.Get(i, matrix.Width-1);
        double a = matrix.Get(i, i);

        double sum = 0;

        for (int k = matrix.Height-1; k > i; k--)
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


int main()
{
    cout << "Case:";
    int caseId;
    cin >> caseId;

    if (caseId == 1)
    {
        Matrix matrix = Matrix::LoadData("dane1_1.txt");
        matrix.Print();

        if (matrix.HasDiagonalZero())
        {
            throw "Matrix has diagonal 0!";
            return -2;
        }
        cout << "Simple Gause!" << endl;
        SimpleGause(matrix);
        return 0;
    }

    if (caseId == 2)
    {
        Matrix matrix = Matrix::LoadData("dane2_1.txt");
        matrix.Print();

        if (matrix.HasDiagonalZero())
        {
            throw "Matrix has diagonal 0!";
            return -2;
        }

        return 0;
    }


    cout << "Wrong case!" << endl;
    return -1;
}