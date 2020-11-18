#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

using namespace std;

double function(double x);
double function2(double x, double y);
double ITrap(double x1, double xn, double e);
double ISimp(double x1, double xn, double e);
double ISimpKU(double x0, double xn, double y0, double yn, double e);

void main()
{
	double x0 = 0, xn = 1.234, e1 = 10e-5, e2 = 10e-6, I, xd0 = 0, xdn = 4, yd0 = 0, ydm = 2;
	int n = 2;

	cout << " metod trapeciu :" << endl;
	I = ITrap(x0, xn, e1);
	cout << " I = " << I << endl << endl;

	I = ITrap(x0, xn, e2);
	cout << " I = " << I << endl << endl;

	cout << " metod Simpsona :" << endl;
	I = ISimp(x0, xn, e1);
	cout << " I = " << I << endl << endl;

	I = ISimp(x0, xn, e2);
	cout << " I = " << I << endl << endl;

	cout << " dvoinoi integral :" << endl;
	I = ISimpKU(xd0, xdn, yd0, ydm, e1);
	cout << " I = " << I << endl << endl;
}

double function2(double x, double y)
{
	return pow(x, 2) / (1 + pow(y, 2));
}

double function(double x)
{
	return pow(sin(x), 2) / pow((1 + pow(x, 3)), 0.5);
}

double ISimpKU(double x0, double xn, double y0, double ym, double e)
{
	int n = 5, m = 5;
	double  S = 0, x = x0, y = y0;
	double hx = (xn - x0) / n, hy = (ym - y0) / m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			S += (function2((x + 2 * i * hx), (y + 2 * j * hy)) + 4 * function2((x + (2 * i + 1) * hx), y + 2 * j * hy) + 4 * function2(x + 2 * i * hx, y + (2 * j + 1) * hy) + function2(x + (2 * i + 2) * hx, y + 2 * j * hy) + 16 * function2(x + (2 * i + 1) * hx, y + (2 * j + 1) * hy) + 4 * function2(x + (2 * i + 2) * hx, y + (2 * j + 1) * hy) + 4 * function2(x + (2 * i + 1) * hx, y + (2 * j + 2) * hy) + 4 * function2(x + 2 * i * hx, y + (2 * j + 1) * hy) + function2(x + 2 * i * hx, y + (2 * j + 2) * hy) + function2(x + (2 * i + 2) * hx, y + (2 * j + 2) * hy));

			y += hy;
		}
		x += hx;
	}

	return S * hx * hy / 9;
}

double ISimp(double x0, double xn, double e)
{
	int n = 1, p;
	double x, h, So = 0, Sn = 0;

	do
	{
		n *= 2;
		So = Sn;
		h = (xn - x0) / n;
		Sn = function(x0) + function(xn);
		x = x0;
		for (int i = 1; i < n; i++)
		{
			if (i % 2 == 0) p = 2;
			else p = 4;
			x += h;
			Sn += p * function(x);
		}

		Sn *= (h / 3);

	} while (fabs(Sn - So) > 15 * e);

	cout << " e = " << e << endl;
	cout << " n = " << n << endl;
	cout << " R = " << fabs(Sn - So) << endl;
	return Sn;
}

double ITrap(double x0, double xn, double e)
{
	int n = 1;
	double x, h, So = 0, Sn = 0;

	do
	{
		n *= 2;
		So = Sn;
		h = (xn - x0) / n;
		Sn = function(x0) + function(xn);
		x = x0;
		for (int i = 1; i < n; i++)
		{
			x += h;
			Sn += 2 * function(x);
		}

		Sn *= (h / 2);

	} while (fabs(Sn - So) > 3 * e);

	cout << " e = " << e << endl;
	cout << " n = " << n << endl;
	cout << " R = " << fabs(Sn - So) << endl;
	return Sn;
}