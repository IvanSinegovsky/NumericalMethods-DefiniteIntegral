#include <iostream>
using namespace std;

double f1(const double x);
double f2(const double x, const double y);
double trapezoidMethod(const double a, const double b);
double simpsonMethod(const double a, const double b);
double cubSimpsonMethod(const double a, const double b, const double c, const double d);

int main()
{
	setlocale(LC_ALL, "ru");

	double a = 0;
	double b = 1;
	cout << "Значение интеграла по формуле трапеций = " 
		<< trapezoidMethod(a, b) << "\n\n";
	cout << "Значение интеграла по формуле Симпсона = " 
		<< simpsonMethod(a, b) << "\n\n";
	cout << "Значение интеграла по кубатурной формуле Симпсона = " 
		<< cubSimpsonMethod(-1.0, 1.0, -1.0, 1.0) << endl;
	return 0;
}

double trapezoidMethod(const double a, const double b)
{
	double h, x, In, I0 = 0, eps = 1e-4, difference;
	double n = 2, k = 0;

	do
	{
		k++;
		h = (b - a) / n;
		In = f1(a);
		x = a + h;

		while (x < b)
		{
			In += 2 * f1(x);
			x += h;
		}

		In += f1(b);
		In *= h / 2;
		difference = fabs(In - I0);
		I0 = In;
		n *= 2;
	} while (difference > 3 * eps);

	cout << "Количество итераций в при вычислении по формуле трапеций = " << k << endl;

	return In;
}

double simpsonMethod(const double a, const double b)
{
	double h, x, In, I0 = 0, eps = 1e-5, difference;
	double n = 2;
	int k = 0;

	do
	{
		k++;
		h = (b - a) / (2 * n);
		In = f1(a);
		x = a + h;

		while (x < b)
		{
			In += 4 * f1(x);
			x += 2 * h;
		}

		x = a + 2 * h;

		while (x < b)
		{
			In += 2 * f1(x);
			x += 2 * h;
		}

		In += f1(b);
		In *= h / 3;
		difference = fabs(In - I0);
		I0 = In;
		n *= 2;
	} while (difference > 15 * eps);

	cout << "Количество итераций в при вычислении по формуле Симпсона = " << k << endl;

	return In;
}

double f1(const double x)
{
	return x;
}

double f2(const double x, const double y)
{
	return sin(x + y);
}

double cubSimpsonMethod(const double a, const double b, const double c, const double d)
{
	double hx, hy, x, y, In, I0 = 0, eps = 1e-5, difference;
	double n = 2; //количество разбиений x, y
	int k = 0;

	do
	{
		k++;
		In = 0;
		hx = (b - a) / (2 * n);
		hy = (d - c) / (2 * n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				In += f2(a + 2 * i * hx, c + 2 * j * hy) 
					+ 4 * f2(a + (2 * i + 1) * hx, c + 2 * j * hy) 
					+ f2(a + (2 * i + 2) * hx, c + 2 * j * hy) 
					+ 4 * f2(a + 2 * i * hx, c + (2 * j + 1) * hy) 
					+ 16 * f2(a + (2 * i + 1) * hx, c + (2 * j + 1) * hy) 
					+ 4 * f2(a + (2 * i + 2) * hx, c + (2 * j + 1) * hy) 
					+ f2(a + 2 * i * hx, c + (2 * j + 2) * hy) 
					+ 4 * f2(a + (2 * i + 1) * hx, c + (2 * j + 2) * hy) 
					+ f2(a + (2 * i + 2) * hx, c + (2 * j + 2) * hy);
			}
		In *= hx * hy / 9;
		difference = fabs(In - I0);
		I0 = In;
		n *= 2;
	} while (difference > eps);

	cout << "Количество итераций в при вычислении по кубатурной формуле Симпсона = " << k << endl;

	return In;
}