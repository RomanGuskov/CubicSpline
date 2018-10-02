#include "stdafx.h"
#include <iostream> 
#include<iomanip>
#include "Spline.h"
#include <ostream> 
#include <iostream> 
#include <fstream>

using namespace std;
double tmin, tmax;
double hForSpline,hForFunc;
int N, M;
double Ellipse(double t, int TaskId);
void FindIntersect(Spline A, Spline B, Spline C, Spline D)
{
	double MinLength=0, Length,x1,y1,x2,y2,a1,b1,c1,d1,a2,b2,c2,d2,a3,b3,c3,d3,a4,b4,c4,d4;
	MinLength= sqrt((A.S[0] - C.S[0])*(A.S[0] - C.S[0]) + (B.S[0] - D.S[0])*(B.S[0] - D.S[0]));
	for (int i = 0; i < A.M; i++)
	{
		for (int j = 0; j < C.M; j++)
		{
			Length =sqrt((A.S[i]- C.S[j])*(A.S[i] - C.S[j]) + (B.S[i] - D.S[j])*(B.S[i] - D.S[j]));
			if (Length < MinLength)
			{
				x1 = A.S[i];
				y1 = B.S[i];
				x2 = C.S[j];
				y2 = D.S[j];
				MinLength = Length;
				a1 = A.a[i];
				b1 = A.b[i];
				c1 = A.c[i];
				d1 = A.d[i];

				a2 = B.a[i];
				b2 = B.b[i];
				c2 = B.c[i];
				d2 = B.d[i];

				a3 = C.a[j];
				b3 = C.b[j];
				c3 = C.c[j];
				d3 = C.d[j];

				a4 = D.a[j];
				b4 = D.b[j];
				c4 = D.c[j];
				d4 = D.d[j];
			}
		}
	}
	cout << "Наименьшее расстояние: " << MinLength << endl;
	cout << "Точка первого сплайна: x=" << x1 <<", y="<< y1 << endl;
	cout << "Точка второго сплайна: x=" << x2 << ", y=" << y2 << endl;
	cout << "Параметры первого сплайна: " << endl;
	cout << "Параметры X(t): а=" << a1 << ", b=" << b1 << ", c=" << c1 << ", d=" << d1 << endl;
	cout << "Параметры Y(t): а=" << a2 << ", b=" << b2 << ", c=" << c2 << ", d=" << d2 << endl;
	cout << "Параметры второго сплайна: " << endl;
	cout << "Параметры X(t): а=" << a3 << ", b=" << b3 << ", c=" << c3 << ", d=" << d3 << endl;
	cout << "Параметры Y(t): а=" << a4 << ", b=" << b4 << ", c=" << c4 << ", d=" << d4 << endl;
	MinLength = sqrt((A.S[0] - Ellipse(tmin, 1))*(A.S[0] - Ellipse(tmin, 1)) + (B.S[0] - Ellipse(tmin, 2))*(B.S[0] - Ellipse(tmin, 2)));
	for (int i = 0; i < A.M; i++)
	{
		for (int j = 0; j < A.M; j++)
		{
			Length = sqrt((A.S[i] - Ellipse(tmin + j*hForFunc, 1))*(A.S[i] - Ellipse(tmin + j*hForFunc, 1)) + (B.S[i] - Ellipse(tmin + j*hForFunc, 2))*(B.S[i] - Ellipse(tmin + j*hForFunc, 2)));
			if (Length < MinLength)
			{
				x1 = A.S[i];
				y1 = B.S[i];
				MinLength = Length;
				a1 = A.a[i];
				b1 = A.b[i];
				c1 = A.c[i];
				d1 = A.d[i];

				a2 = B.a[i];
				b2 = B.b[i];
				c2 = B.c[i];
				d2 = B.d[i];
			}
		}
	}
	cout << endl;
	cout << "Наименьшее расстояние между первым сплайном и эллипсом: " << MinLength << endl;
	cout << "Точка сплайна: x=" << x1 << ", y=" << y1 << endl;
	cout << "Параметры сплайна: " << endl;
	cout << "Параметры X(t): а=" << a1 << ", b=" << b1 << ", c=" << c1 << ", d=" << d1 << endl;
	cout << "Параметры Y(t): а=" << a2 << ", b=" << b2 << ", c=" << c2 << ", d=" << d2 << endl;
}
void MakeData(int TaskId)
{
	TestFunction Test;
	if (TaskId == 1)
	{
		ofstream fout1("DataForSpline1.txt");
		for (int i = 0; i <= N; i++)
		{
			fout1 << "(" << setprecision(10) << Test.Function(tmin + i*hForFunc, 1) << "," << setprecision(10) << Test.Function(tmin + i*hForFunc, 2) << ")" << "\n";
		}
		fout1.close();
	}
	if (TaskId == 2)
	{
		ofstream fout2("DataForSpline2.txt");
		for (int i = 0; i <= N; i++)
		{
			fout2 << "(" <<  setprecision(10)<< Test.Function(tmin + i*hForFunc, 3) << "," << setprecision(10) << Test.Function(tmin + i*hForFunc, 4) << ")" << "\n";
		}
		fout2.close();
	}
}
void SplineData(Spline A, Spline B, int TaskId) 
{
	if (TaskId == 1)
	{
		ofstream fout3("SplineData1.txt");
		for (int i = 0; i <= N; i++)
		{
			fout3 << "(" << setprecision(10) << A.S[i] << "," << setprecision(10) << B.S[i] << ")" << "\n";
		}
		fout3.close();
	}
	if (TaskId == 2)
	{
		ofstream fout4("SplineData2.txt");
		for (int i = 0; i <= N; i++)
		{
			fout4 << "(" << setprecision(10) << A.S[i] << "," << setprecision(10) << B.S[i] << ")" << "\n";
		}
		fout4.close();
	}
}
double Ellipse(double t, int TaskId)
{
	if (TaskId == 1)
		return 0.5*cos(t);
	if (TaskId == 2)
		return 0.4*sin(t);
}
int main()
{
	tmin = 0.3;
	tmax = 2.3;
	N = 500;//число разбиений для функций
	M = 1000; //число разбиений для сплайна (для проверки погрешностей)
	hForFunc = (double)((tmax - tmin)/N);
	hForSpline = (double)((tmax - tmin)/M);
	int TaskId = 1;
	setlocale(0, "Russian");
	MakeData(TaskId);
	cout << "Первая тестовая функция: X(t) = log(t + 1) / (t + 1); Y(t) = 1 / (t*t + 1)" << endl;
	cout << endl;
	cout << "Погрешность функции X(t): ";
	Spline FirstX(tmin, tmax, hForFunc, hForSpline, 1,1);
	cout << "Погрешность функции Y(t): ";
	Spline FirstY(tmin, tmax, hForFunc, hForSpline, 2,2);
	cout << endl;
	
	TaskId = 2;
	MakeData(TaskId);
	cout << "Вторая тестовая функция: X(t) = 1 / (2 * t + 1); Y(t) = t / (t + 1)" << endl;
	cout << endl;
	cout << "Погрешность функции X(t): ";
	Spline SecondX(tmin, tmax, hForFunc, hForSpline, 3,1);
	cout << "Погрешность функции Y(t): ";
	Spline SecondY(tmin, tmax, hForFunc, hForSpline, 4,2);
	SplineData(FirstX, FirstY, 1);
	SplineData(SecondX, SecondY, 2);
	cout << endl;
	FindIntersect(FirstX, FirstY, SecondX, SecondY);
	return 0;
}

