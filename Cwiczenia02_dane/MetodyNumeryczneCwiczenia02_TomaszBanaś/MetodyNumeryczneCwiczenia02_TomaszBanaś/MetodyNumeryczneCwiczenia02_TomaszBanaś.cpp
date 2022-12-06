#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

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


double Zadanie01_fun(double x)
{
	return cos(pow(x, 3) - (2 * x));
}

void Zadanie01_display(int i, double a, double b, double x0)
{
	Zadanie_display(i, a, Zadanie01_fun(a), b, Zadanie01_fun(b), x0, Zadanie01_fun(x0), (Zadanie01_fun(a) * Zadanie01_fun(x0)));
}

int Zadanie01()
{
	/*double from = CinFromUser("From:");
	double to = CinFromUser("To:");
	double threashold = CinFromUser("Threashold:");*/

	double from = 0;
	double to = 2;
	double epsilon = 0.01;

	double x0 = 0;
	double y = 0;
	Zadanie_display_names();
	int i = 0;
	do
	{
		x0 = (from + to) / 2;
		y = Zadanie01_fun(x0);
		i++;
		Zadanie01_display(i, from, to, x0);
		if (Zadanie01_fun(from) * y < 0)
		{
			to = x0;
		}
		else
		{
			from = x0;
		}
	} while (abs(y) > epsilon);

	cout << "Result"  << endl;
	cout << "x:" << x0 << " y: " << y << endl;
	return 0;
}

double Zadanie02_fun(double x)
{
	return cos(pow(x, 3) - (2 * x));
}

double Zadanie02_equation(double a, double b)
{
	return a - (Zadanie02_fun(a)*(b-a)/(Zadanie02_fun(b)- Zadanie02_fun(a)));
}


void Zadanie02_display(int i, double a, double b, double x0)
{
	Zadanie_display(i, a, Zadanie02_fun(a), b, Zadanie02_fun(b), x0, Zadanie02_fun(x0), (Zadanie02_fun(a) * Zadanie02_fun(x0)));
}
void Zadanie02_recur(int i, double a, double b, double epsilon)
{
	double x1 = Zadanie02_equation(a, b);
	double y = Zadanie02_fun(x1);
	if (abs(y) < epsilon)
	{
		cout << "Result" << endl;
		cout << "x:" << x1 << " y: " << y << endl;
		return;
	}
	Zadanie02_display(i, a, b, x1);
	if (Zadanie01_fun(a) * y < 0)
	{
		Zadanie02_recur(++i, a, x1, epsilon);
	}
	else
	{
		Zadanie02_recur(++i, x1, b, epsilon);
	}
}

int Zadanie02()
{
	double a = 0;
	double b = 2;
	double epsilon = 0.01;
	Zadanie_display_names();
	Zadanie02_recur(1, a, b, epsilon);
	return 0;
}

double Zadanie03_fun(double x)
{
	return ((-1) * pow(x, 3)) + (10 * x) +5;
}

double Zadanie03_fun_derivative(double x)
{
	return ((-3) * pow(x, 2)) + 10;
}
//
//void Zadanie_display_names()
//{
//	cout << "i\t";
//	cout << "\t";
//	cout << "a";
//	cout << "\t";
//	cout << "f(a)";
//	cout << "\t";
//	cout << "\t";
//	cout << "b";
//	cout << "\t";
//	cout << "f(b)";
//	cout << "\t";
//	cout << "\t";
//	cout << "x0";
//	cout << "\t";
//	cout << "f(x0)";
//	cout << "\t";
//	cout << "\t";
//	cout << "f(a)*f(x0)";
//	cout << "\t";
//	cout << endl;
//}
//void Zadanie_display(int i, double a, double fa, double b, double fb, double x0, double fx0, double res)
//{
//	cout << i;
//	cout << "\t";
//	cout << a;
//	cout << "\t";
//	cout << fa;
//	cout << "\t";
//	cout << b;
//	cout << "\t";
//	cout << fb;
//	cout << "\t";
//	cout << x0;
//	cout << "\t";
//	cout << fx0;
//	cout << "\t";
//	cout << res;
//	cout << "\t";
//	cout << endl;
//}


int Zadanie03()
{
	double a = 2;
	double b = 6;
	double epsilon = 0.01;
	double x = 6;
	Zadanie_display_names();
	while (true)
	{
		x = x - (Zadanie03_fun(x) / Zadanie03_fun_derivative(x));
		double y = Zadanie03_fun(x);
		cout << y << endl;
	}
	return 0;
}

int mainData()
{
	cout << "Case:";
	int caseId = 2;
	cin >> caseId;
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

	if (caseId == 3)
	{
		cout << "Zadanie 03!" << endl;
		return Zadanie03();
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