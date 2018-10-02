#include "stdafx.h"
#include <fstream>
#include <iostream> 
#include "Spline.h"
#include<math.h>
#include <ostream> 
#include<stdio.h> 

using namespace std;
Spline::Spline(double tmin, double tmax, double h1, double h2, int TaskId,int TypeTask)
{
	TaskID = TaskId;
	TaskType = TypeTask;
	H = h1;	
	T = h2;
	BordA = tmin;
	BordB = tmax;
	for (int i = 0; i <= N; i++)
	{
		x[i] = BordA + i * H;
		if (i != 0)
			h[i] = x[i] - x[i - 1];
		else h[i] = H;
	}
	MakeSpline();
}


Spline::~Spline()
{
}
double Spline::FinalSpline(double t)
{
	int i = 1;
	bool ok = false;

	while (!ok)
	{
		if (t != x[N])
		{
			if ((t >= x[i - 1]) && (t < x[i]))
			{
				ok = true;
			}
			else i++;
		}
		else
		{
			ok = true;
			i = N;
		}
	}
	return a[i] + b[i] * (t - x[i]) + (c[i] / 2.0) * (t - x[i]) * (t - x[i]) + (d[i] / 6.0) * (t - x[i]) * (t - x[i]) * (t - x[i]);
}
void Spline::SweepMethod()
{
	double res[N + 1];
	double alfa[N];
	double betta[N];
	for (int i = 0; i < N; i++)
	{
		alfa[i] = 0;
		betta[i] = 0;
		res[i] = 0;
	}
	alfa[0] = 0;
	betta[0] = M1;

	for (int i = 1; i < N; i++)
	{
		alfa[i] = -cValue[i] / (aValue[i] * alfa[i - 1] + bValue[i]);
		betta[i] = (fValue[i] - aValue[i] * betta[i - 1]) / (aValue[i] * alfa[i - 1] + bValue[i]);
	}
	res[N] = M2;
	for (int i = N - 1; i >= 0; i--)
	{
		res[i] = alfa[i] * res[i + 1] + betta[i];

	}
	for (int i = 0; i <= N; i++)
	{
		c[i] = res[i];
	}
}

void Spline::MakeSpline()
{
	char symbol;
	if ((TaskID == 1)||(TaskID == 2))
	{
		if (TaskType == 1)
		{
			ifstream fin1("DataForSpline1.txt");
			int i = 0;
			while (!fin1.eof())
			{
				fin1.get(symbol);
				if (symbol == '(')
				{
					fin1 >> f[i];
					i++;
				}
			}
			fin1.close();
		}
		else
		{
			ifstream fin2("DataForSpline1.txt");
			int i = 0;
			while (!fin2.eof())
			{
				fin2.get(symbol);
				if (symbol == ',')
				{
					fin2 >> f[i];
					i++;
				}
			}
			fin2.close();
		}
	}
	if ((TaskID == 3)||(TaskID == 4))
	{
		if (TaskType == 1)
		{
			ifstream fin3("DataForSpline2.txt");
			int i = 0;
			while (!fin3.eof())
			{
				fin3.get(symbol);
				if (symbol == '(')
				{
					fin3 >> f[i];
					i++;
				}
			}
			fin3.close();
		}
		else
		{
			ifstream fin4("DataForSpline2.txt");
			int i = 0;
			while (!fin4.eof())
			{
				fin4.get(symbol);
				if (symbol == ',')
				{
					fin4 >> f[i];
					i++;
				}
			}
			fin4.close();
		}
	}
	M1 = TestFunction.SecondDerivativeOfFunction(BordA, TaskID);
	M2 = TestFunction.SecondDerivativeOfFunction(BordB, TaskID);
	c[0] = M1;
	c[N - 1] = M2;
	for (int i = 0; i <= N; i++)
	{
		aValue[i] = 0;
		bValue[i] = 0;
		cValue[i] = 0;
		fValue[i] = 0;
	}
	for (int i = 1; i <= N - 1; i++)
	{
		aValue[i] = h[i];
		bValue[i] = 2 * (h[i] + h[i + 1]);
		cValue[i] = h[i + 1];
		fValue[i] = 6 * (((f[i + 1] - f[i]) / h[i + 1]) - (f[i] - f[i - 1]) / h[i]);
	}
	SweepMethod();
	for (int i = 1; i <= N; i++)
	{
		a[i] = f[i];
		d[i] = (c[i] - c[i - 1]) / h[i];
		b[i] = ((f[i] - f[i - 1]) / h[i]) + (c[i] * h[i] / 2.0) - ((c[i] - c[i - 1]) * h[i] / 6.0);
	}
	
	for (int i = 0; i <= M; i++)
	{
		t[i] = BordA + i * T;
		S[i] = FinalSpline(t[i]);
		pogr[i] = fabs((S[i]) - TestFunction.Function(t[i],TaskID));
	}

	int index = 0;
	
	for (int i = index; i <= M; i++)
	{
		der[i] = TestFunction.FirstDerivativeOfFunction(t[i], TaskID);
		der2[i] = TestFunction.SecondDerivativeOfFunction(t[i], TaskID);
	}
	der2S[0] = der2[0];
	der2S[M] = der2[M];
	for (int i = index; i <= M; i++)
	{
		der2S[i] = Derivative2Spline(t[i]);
		derS[i] = DerivativeSpline(t[i]);
	}
	for (int i = index; i <= M; i++)
	{
		pogr1[i] = fabs(der[i] - derS[i]);
		pogr2[i] = fabs(der2[i] - der2S[i]);
	}
	MaxPogr = Max(pogr, M);
	MaxPogr1 = Max(pogr1, M);
	MaxPogr2 = Max(pogr2, M);
	cout  << MaxPogr << endl;
	cout << "Погрешность первой производной: " << MaxPogr1 << endl;
	cout << "Погрешность второй производной: " << MaxPogr2 << endl;

}

double Spline::DerivativeSpline(double t)
{
	int i = 1;
	bool ok = false;

	while (!ok)
	{
		if (t != x[N])
		{
			if ((t >= x[i - 1]) && (t < x[i]))
			{
				ok = true;
			}
			else i++;
		}
		else
		{
			ok = true;
			i = N;
		}
	}
	return b[i] + c[i] * (t - x[i]) + 0.5 * d[i] * (t - x[i]) * (t - x[i]);
}

double Spline::Derivative2Spline(double t)
{
	int i = 1;
	bool ok = false;

	while (!ok)
	{
		if (t != x[N])
		{
			if ((t >= x[i - 1]) && (t < x[i]))
			{
				ok = true;
			}
			else i++;
		}
		else
		{
			ok = true;
			i = N;
		}
	}
	return c[i] + d[i] * (t - x[i]);
}
double Spline::Max(double array[], int size)
{
	double max = array[0];
	for (int i = 1; i < size; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}
	return max;
}
