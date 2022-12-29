#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#pragma region Utils
const double epsilon = 0.01;
struct CustomException
{
	string Message;
	CustomException(string message)
	{
		Message = message;
	}
};
double CinFromUser(string message)
{
	double result = 0;
	cout << message << endl;
	cin >> result;
	return result;
}

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

	double GetX(int i)
	{
		return Data[i];
	}

	double GetY(int i)
	{
		return Data[Width + i];
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
			throw CustomException("Matrix has diagonal 0!");
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
				if (val != 0)
					cloned.Set(i, j, 1 / val);
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
				if (i != j)
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

	static Matrix LoadPoints(string file)
	{
		fstream plik;
		double wyraz;

		plik.open(file, ios::in | ios::out);

		int width;

		plik >> width;

		int height = 2;

		double* arrayData = new double[height * width];

		for (int i = 0; i < (height * width); i++)
		{
			plik >> wyraz;
			arrayData[i] = wyraz;
		}
		plik.close();

		Matrix matrix = Matrix(width, height, arrayData);
		matrix.Print();
		return matrix;
	}
};
#pragma endregion
#pragma region Zadanie01

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
	matrix.CheckDiagonalZero();
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
		for (int j = 0; j < matrix.Width - 1; j++)
		{
			if (i == j)
				continue;

			if (matrix.Get(i, j) >= valDiag)
				throw CustomException("Matrix is not diagonally strong!");
		}
	}
}

void SimpleGause(Matrix matrix)
{
	GaussaElimination(matrix);
	ReversedGause(matrix);
}

double fi(double x, int j)
{
	return pow(x, j);
}

double g(int k, int j, Matrix matrix, int m)
{
	double result = 0;
	for (int i = 0; i < matrix.Width; i++)
	{
		result += (fi(matrix.GetX(i), k) * fi(matrix.GetX(i), j));
	}
	return result;
}

double F(int k, Matrix matrix, int m)
{
	double result = 0;
	for (int i = 0; i < matrix.Width; i++)
	{
		result += (fi(matrix.GetX(i), k) * matrix.GetY(i));
	}
	return result;
}


int Zadanie()
{
	Matrix dane = Matrix::LoadPoints("Dane01.txt");
	int degree = 1;

	cout << "Degree: ";
	cin >> degree;

	int w = (degree + 1)+1;
	int h = (degree + 1);
	Matrix gs = Matrix(w, h, ZeroArray(w * h));
	for (int i = 0; i < w-1; i++)
	{
		for (int j = 0; j < h; j++)
		{
			gs.Set(i, j, g(i, j, dane, degree));
		}
	}
	for (int j = 0; j < h; j++)
	{
		gs.Set(j, w-1, F(j, dane, degree));
	}
	gs.Print();
	cout << "Gauesee: " << endl;
	SimpleGause(gs);
	return 0;
}
#pragma endregion
#pragma region Main
int mainData()
{
	return Zadanie();
}
int main()
{
	try {
		while (true)
		{
			mainData();
		}
		return 1;
	}
	catch (const CustomException& ex) {
		cout << ex.Message << endl;
		return -2;
	}
	catch (...) {
		cout << "Something very wrong happened!" << endl;
		return -3;
	}
}
#pragma endregion