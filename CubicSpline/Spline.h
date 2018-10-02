#include "TestFunction.h"
#pragma once
class Spline
{
public:
	int TaskID; //номер тестовой функции
	int TaskType; 
	double H;  //шаг для функции
	double T;  //шаг сплайна
	double BordA; //левая граница
	double BordB; //правая граница
	static const int N=500; //число разбиений для функций
	static const int M=1000; //число разбиений для сплайна (для проверки погрешностей)
	double x[N + 1];
	double t[M + 1]; 
	//параметры сплайна
	double f[N + 1];
	double a[N + 1];
	double b[N + 1];
	double c[N + 1];
	double d[N + 1];
	double h[N + 1];
	double M1, M2;
	//параметры для метода прогонки
	double aValue[N];
	double bValue[N];
	double cValue[N];
	double fValue[N];
	double S[M + 1]; //значения сплайна
	double pogr[M + 1]; //погрешность
	double pogr1[M + 1]; //погрешность первых производных
	double pogr2[M + 1];//погрешность вторых производных
	double der[M + 1]; //значения первой производной тестовой функции
	double der2[M + 1];//значения второй производной тестовой функции
	double derS[M + 1];//значения производной сплайна
	double der2S[M + 1];//значения второй производной сплайна
	TestFunction TestFunction;
	Spline(double tmin, double tmax, double h1, double h2,int TaskId,int TypeTask);
	~Spline();
	double FinalSpline(double t); //финальный сплайн
	void SweepMethod(); //метод прогонки
	void MakeSpline();
	double DerivativeSpline(double t); //первая производная сплайна
	double Derivative2Spline(double t); //вторая производная сплайна
	double MaxPogr, MaxPogr1, MaxPogr2;
	double Max(double array[], int size);
};

