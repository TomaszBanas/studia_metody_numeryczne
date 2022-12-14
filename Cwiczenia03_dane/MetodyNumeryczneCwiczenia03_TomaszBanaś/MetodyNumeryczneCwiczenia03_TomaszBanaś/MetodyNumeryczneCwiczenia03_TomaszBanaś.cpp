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

	static Matrix LoadData(string file)
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
double l(double x, int i, Matrix m)
{
	double dividend = 1;
	double divisor = 1;
	for (int j = 0; j < m.Width; j++)
	{
		if (i == j)
			continue;

		dividend *= (x - m.GetX(j));
		divisor *= (m.GetX(i) - m.GetX(j));
	}
	return dividend / divisor;
}

double L(double x, Matrix m)
{
	double result = 0;
	for (int i = 0; i < m.Width; i++)
	{
		result += (m.GetY(i) * l(x, i, m));
	}
	return result;
}
int Zadanie01()
{
	Matrix m = Matrix::LoadData("Dane01.txt");
	//double x = -1;
	double x = CinFromUser("x=");
	double y = L(x, m);
	cout << "x: " << x << " y: " << y << endl;
	return 0;
}
#pragma endregion
#pragma region Zadanie02
double b(int k, Matrix m)
{
	double sum = 0;
	for (int i = 0; i <= k; i++)
	{
		double dividend = m.GetY(i);
		double divisor = 1;
		for (int j = 0; j <= k; j++)
		{
			if (i == j)
				continue;

			divisor *= (m.GetX(i) - m.GetX(j));
		}
		sum += (dividend / divisor);
	}
	return sum;
}
double p(int k, double x, Matrix m)
{
	double result = 1;
	for (int i = 0; i < k; i++)
	{
		result *= (x - m.GetX(i));
	}
	return result;
}
double Fun02(double x, Matrix m)
{
	double b0 = b(0, m);
	cout << "b" << 0 << ": " << b0 << endl;
	double y = b0 * m.GetY(0);
	for (int i = 1; i < m.Width; i++)
	{
		double bk = b(i, m);
		cout << "b" << i << ": " << bk << endl;
		y += (bk * p(i, x, m));
	}
	return y;
}

int Zadanie02()
{
	Matrix m = Matrix::LoadData("Dane02.txt");
	cout << "##### x: " << 1 << endl;
	double y1 = Fun02(1, m);
	cout << " y: " << y1 << endl;
	cout << "##### x: " << 2 << endl;
	double y2 = Fun02(2, m);
	cout << " y: " << y2 << endl;
	cout << "##### x: " << 3 << endl;
	double y3 = Fun02(3, m);
	cout << " y: " << y3 << endl;
	cout << "##### x: " << 4 << endl;
	double y4 = Fun02(4, m);
	cout << " y: " << y4 << endl;
	cout << "##### x: " << 5 << endl;
	double y5 = Fun02(5, m);
	cout << " y: " << y5 << endl;
	cout << "##### x: " << 2.5 << endl;
	double y2i5 = Fun02(1.5, m);
	cout << " y: " << y2i5 << endl;
	return 0;
}
#pragma endregion
#pragma region Main
int mainData()
{
	cout << "Case:";
	int caseId = 2;
	//cin >> caseId;
	cout << endl << "Selected: " << caseId << endl;
	if (caseId == 1)
	{
		cout << "Zadanie 01!" << endl;
		return Zadanie01();
	}
	if (caseId == 2)
	{
		cout << "Zadanie 02!" << endl;
		return Zadanie02();
	}
	cout << "Wrong case!" << endl;
	return -1;
}
int main()
{
	try {
		return mainData();
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