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

double f1(double x)
{
	return sin(x);
}

double f2(double x)
{
	return (x * x) + (2 * x) + 5;
}

double f3(double x)
{
	return exp(x);
}

#pragma endregion

double SquareMethod(double (*f)(double), double a, double b)
{
	return f(a + ((b - a)/2)) * (b - a);
}

double TrapezeMethod(double (*f)(double), double a, double b)
{
	return ((b - a) / 2) * (f(a) + f(b));
}

double ParableMethod(double (*f)(double), double a, double b)
{
	return ((b - a) / 6) * (f(a) + (4 * f((a+b)/2) + f(b)));
}

double Sum(double (*m)(double (*f_in)(double), double, double), double (*f)(double), double from, double to, int n)
{
	double part = (to - from) / n;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += m(f, from + (i * part), from + ((i + 1) * part));
	}
	return sum;
}

double* GaussaLagendreXs(int n)
{
	if (n == 4)
	{
		double* xs = new double[4];
		xs[0] = -1 * (1.0 / 35) * sqrt(525 + (70 * sqrt(30)));
		xs[1] = -1 * (1.0 / 35) * sqrt(525 - (70 * sqrt(30)));
		xs[2] = (1.0 / 35) * sqrt(525 - (70 * sqrt(30)));
		xs[3] = (1.0 / 35) * sqrt(525 + (70 * sqrt(30)));
		return xs;
	}

	if (n == 2)
	{
		double* xs = new double[2];
		xs[0] = -1 * 0.57735;
		xs[1] = 0.57735;
		return xs;
	}
	throw new CustomException("GaussaLagendre cannot handle n=" + n);
}

double* GaussaLagendreAs(int n)
{
	if (n == 4)
	{
		double* As = new double[4];
		As[0] = (1.0 / 36) * (18 - sqrt(30));
		As[1] = (1.0 / 36) * (18 + sqrt(30));
		As[2] = As[1];
		As[3] = As[0];
		return As;
	}

	if (n == 2)
	{
		double* As = new double[2];
		As[0] = 1;
		As[1] = 1;
		return As;
	}
	throw new CustomException("GaussaLagendre cannot handle n=" + n);
}

double GaussaLagendreMethod(double (*f)(double), double a, double b, int n)
{
	double* xs = GaussaLagendreXs(n);
	double* As = GaussaLagendreAs(n);
	double result = 0;
	for (int i = 0; i < n; i++)
	{
		result += As[i] * f(((a + b) / 2) + ((b - a) / 2 * xs[i]));
	}
	return ((b - a) / 2) * result;
}


void Integral(double (*f)(double), double from, double to, int n)
{
	cout << "from=" << from << endl;
	cout << "to=" << to << endl;
	cout << "n=" << n << endl;
	double resultSquareMethod = Sum(SquareMethod, f, from, to, n);
	cout << "SquareMethod			result=" << resultSquareMethod << endl;
	
	double resultTrapezeMethod = Sum(TrapezeMethod, f, from, to, n);
	cout << "TrapezeMethod			result=" << resultTrapezeMethod << endl;

	double resultParableMethod = Sum(ParableMethod, f, from, to, n);
	cout << "ParableMethod			result=" << resultParableMethod << endl;

	double resultGaussaLagendreMethod = GaussaLagendreMethod(f, from, to, n);
	cout << "GaussaLagendreMethod		result=" << resultGaussaLagendreMethod << endl;
}


#pragma region Main
int mainData()
{
	cout << "f(x)=sin(x)" << endl;
	Integral(f1, 0.5, 2.5, 4);
	cout << "================================================================" << endl;
	cout << "f(x)=x^2 + 2x + 5" << endl;
	Integral(f2, 0.5, 5, 4);
	cout << "================================================================" << endl;
	cout << "f(x)=exp(x)" << endl;
	Integral(f3, 0.5, 5, 4);

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