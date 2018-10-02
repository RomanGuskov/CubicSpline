#include "TestFunction.h"
#pragma once
class Spline
{
public:
	int TaskID; //����� �������� �������
	int TaskType; 
	double H;  //��� ��� �������
	double T;  //��� �������
	double BordA; //����� �������
	double BordB; //������ �������
	static const int N=500; //����� ��������� ��� �������
	static const int M=1000; //����� ��������� ��� ������� (��� �������� ������������)
	double x[N + 1];
	double t[M + 1]; 
	//��������� �������
	double f[N + 1];
	double a[N + 1];
	double b[N + 1];
	double c[N + 1];
	double d[N + 1];
	double h[N + 1];
	double M1, M2;
	//��������� ��� ������ ��������
	double aValue[N];
	double bValue[N];
	double cValue[N];
	double fValue[N];
	double S[M + 1]; //�������� �������
	double pogr[M + 1]; //�����������
	double pogr1[M + 1]; //����������� ������ �����������
	double pogr2[M + 1];//����������� ������ �����������
	double der[M + 1]; //�������� ������ ����������� �������� �������
	double der2[M + 1];//�������� ������ ����������� �������� �������
	double derS[M + 1];//�������� ����������� �������
	double der2S[M + 1];//�������� ������ ����������� �������
	TestFunction TestFunction;
	Spline(double tmin, double tmax, double h1, double h2,int TaskId,int TypeTask);
	~Spline();
	double FinalSpline(double t); //��������� ������
	void SweepMethod(); //����� ��������
	void MakeSpline();
	double DerivativeSpline(double t); //������ ����������� �������
	double Derivative2Spline(double t); //������ ����������� �������
	double MaxPogr, MaxPogr1, MaxPogr2;
	double Max(double array[], int size);
};

