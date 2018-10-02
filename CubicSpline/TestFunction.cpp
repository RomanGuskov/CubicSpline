#include "stdafx.h"
#include "TestFunction.h"
#include <math.h>
#include <iostream> 
#include<iomanip>
#include <ostream> 
#include <fstream>
using namespace std;
TestFunction::TestFunction()
{	
}

TestFunction::~TestFunction()
{
}

double TestFunction::Function(double t,int TaskID)
{
	if (TaskID==1)
		return log(t + 1) / (t + 1);
	if (TaskID==2)
		return 1 / (t*t + 1);
	if (TaskID == 3)
		return 1 / (2 * t + 1);
	if (TaskID == 4)
		return  t / (t + 1);
	else return -1;
}

double TestFunction::FirstDerivativeOfFunction(double t, int TaskID)
{
	if (TaskID == 1)
		return (1.0 - log(t + 1)) / ((t + 1)*(t + 1));
	if (TaskID == 2)
		return -2 * t / ((t*t + 1)*(t*t + 1));
	if (TaskID == 3)
		return  -2 / ((1 + 2 * t)*(1 + 2 * t));
	if (TaskID == 4)
		return  1 / ((t + 1)*(t + 1));
	else return -1;
}

double TestFunction::SecondDerivativeOfFunction(double t, int TaskID)
{
	if (TaskID == 1)
		return (1 / ((t + 1) * (t + 1) * (t + 1)))*(2 * log(t + 1) - 3);
	if (TaskID == 2)
		return 8 * t*t / ((t*t + 1)*(t*t + 1)*(t*t + 1)) - 2 / ((t*t + 1)*(t*t + 1));
	if (TaskID == 3)
		return 8 / ((1 + 2*t)*(1 + 2*t)*(1 + 2*t));
	if (TaskID == 4)
		return  2 * t / ((t + 1)*(t + 1)*(t + 1)) - 2 / ((t + 1)*(t + 1));
	else return -1;
}
