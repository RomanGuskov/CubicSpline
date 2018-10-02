#pragma once
class TestFunction
{
public:
	TestFunction();
	~TestFunction();
	double Function(double t, int TaskID);
	double FirstDerivativeOfFunction(double t, int TaskID);
	double SecondDerivativeOfFunction(double t, int TaskID);
};

