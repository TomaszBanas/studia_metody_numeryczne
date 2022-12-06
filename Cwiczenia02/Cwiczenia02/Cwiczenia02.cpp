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
void Zadanie_display_names()
{
	cout << "i";
	cout << "\t";
	cout << "a";
	cout << "\t";
	cout << "f(a)";
	cout << "\t";
	cout << "\t";
	cout << "b";
	cout << "\t";
	cout << "f(b)";
	cout << "\t";
	cout << "\t";
	cout << "x0";
	cout << "\t";
	cout << "f(x0)";
	cout << "\t";
	cout << "\t";
	cout << "f(a)*f(x0)";
	cout << "\t";
	cout << endl;
}
void Zadanie_display(int i, double a, double fa, double b, double fb, double x0, double fx0, double res)
{
	cout << i;
	cout << "\t";
	cout << a;
	cout << "\t";
	cout << fa;
	cout << "\t";
	cout << b;
	cout << "\t";
	cout << fb;
	cout << "\t";
	cout << x0;
	cout << "\t";
	cout << fx0;
	cout << "\t";
	cout << res;
	cout << "\t";
	cout << endl;
}
#pragma endregion
#pragma region Samples
double fun01(double x)
{
	return cos(pow(x, 3) - (2 * x));
}

double fun02(double x)
{
	return ((-1) * pow(x, 3)) + (10 * x) + 5;
}
double fun02_derivative(double x)
{
	return ((-3) * pow(x, 2)) + 10;
}
#pragma endregion
#pragma region Zadanie01
void Zadanie01_display(int i, double a, double b, double x0, double (*func)(double))
{
	Zadanie_display(i, a, func(a), b, func(b), x0, func(x0), (func(a) * func(x0)));
}
int Zadanie01(double (*func)(double))
{
	double from = 0;
	double to = 2;
	double x0 = 0;
	double y = 0;
	Zadanie_display_names();
	int i = 0;
	do
	{
		x0 = (from + to) / 2;
		y = func(x0);
		i++;
		Zadanie01_display(i, from, to, x0, func);
		if (func(from) * y < 0)
		{
			to = x0;
		}
		else
		{
			from = x0;
		}
	} while (abs(y) > epsilon);
	cout << "Result" << endl;
	cout << "x:" << x0 << " y: " << y << endl;
	return 0;
}
#pragma endregion
#pragma region Zadanie02
double Zadanie02_equation(double a, double b, double (*func)(double))
{
	return a - (func(a) * (b - a) / (func(b) - func(a)));
}
void Zadanie02_display(int i, double a, double b, double x0, double (*func)(double))
{
	Zadanie_display(i, a, func(a), b, func(b), x0, func(x0), (func(a) * func(x0)));
}
void Zadanie02_recur(int i, double a, double b, double (*func)(double))
{
	double x1 = Zadanie02_equation(a, b, func);
	double y = func(x1);
	if (abs(y) < epsilon)
	{
		cout << "Result" << endl;
		cout << "x:" << x1 << " y: " << y << endl;
		return;
	}
	Zadanie02_display(i, a, b, x1, func);
	if (func(a) * y < 0)
	{
		Zadanie02_recur(++i, a, x1, func);
	}
	else
	{
		Zadanie02_recur(++i, x1, b, func);
	}
}
int Zadanie02(double (*func)(double))
{
	double a = 0;
	double b = 2;
	Zadanie_display_names();
	Zadanie02_recur(1, a, b, func);
	return 0;
}
#pragma endregion
#pragma region Zadanie03
int Zadanie03_tangent(double (*func)(double), double (*derivative)(double))
{
	int n = 7;
	int i = 0;
	double x0 = 6;
	double y = 0;
	do
	{
		i++;
		cout << "i: " << i << "x: " << x0 << ", y: " << y << endl;
		x0 = x0 - (func(x0) / derivative(x0));
		y = func(x0);
	}
	while (i < n);
	//while (abs(y) > epsilon && i < n);
	cout << "Result" << endl;
	cout << "x:" << x0 << " y: " << y << endl;
	return 0;
}
int Zadanie03_secant(double (*f)(double))
{
	int n = 7;
	int i = 0;
	double x1 = 6;
	double x0 = x1-0.1;
	double y = 0;
	do
	{
		i++;
		cout << "i: " << i << "x: " << x1 << ", y: " << y << endl;
		double z = (f(x1) - f(x0)) / (x1 - x0);
		double x = x1 - (f(x1) / z);
		y = f(x);
		x0 = x1;
		x1 = x;
	} 
	while (i < n);
	//while (abs(y) > epsilon && i < n);
	cout << "Result" << endl;
	cout << "x:" << x1 << " y: " << y << endl;
	return 0;
}
#pragma endregion
#pragma region Main
int mainData()
{
	cout << "Case:";
	int caseId = 4;
	//cin >> caseId;
	cout << endl << "Selected: " << caseId << endl;
	if (caseId == 1)
	{
		cout << "Zadanie 01!" << endl;
		return Zadanie01(fun01);
	}
	if (caseId == 2)
	{
		cout << "Zadanie 02!" << endl;
		return Zadanie02(fun01);
	}
	if (caseId == 3)
	{
		cout << "Zadanie 03 Tangent!" << endl;
		return Zadanie03_tangent(fun02, fun02_derivative);
	}

	if (caseId == 4)
	{
		cout << "Zadanie 03 Secant!" << endl;
		return Zadanie03_secant(fun02);
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