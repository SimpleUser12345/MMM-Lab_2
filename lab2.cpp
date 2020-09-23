// Lab 2

#include <iostream>
#include <cmath>

using namespace std;

const float EPS = 0.0001; 

//-----------------------
// Task 1

float f1(float x)
{
	return x*x*x*x + 4*x*x*x - 12*x*x + 1;
}

void md(float a, float b)
{
	cout << "Dihotomiya" << endl;
	int iter = 0;
	float c;
	while(fabs(b-a) > EPS)
	{
		c = (a+b)/2;
		if(f1(a)*f1(c)<0)	
		{
			b = c;
		}
		else
		{
			a = c;
		}
		iter++;
	}
	
	float x = (a+b)/2;
	cout << "iter=" << iter << endl;
	cout << "x=" << x << endl;
	cout << "f1(x)=" << f1(x) << endl;
	cout << endl;
}

void mh(float a, float b)
{
	cout << "Hordi" << endl;
	int iter = 0;
	float x1 = a-f1(a)*(b-a) / (f1(b)-f1(a));
	if(f1(a)*f1(x1) < 0)
	{
		b = x1;
	}
	else
	{
		a = x1;
	}
	float x2 = a-f1(a)*(b-a)/(f1(b)-f1(a));
	while (fabs(x2 - x1) > EPS)
	{
        if(f1(a)*f1(x2) < 0)
            b=x2;
        else
            a=x2;
        x1=x2;
        x2=a-f1(a)*(b-a)/(f1(b)-f1(a));
        iter += 1;
	}
	
	cout << "iter=" << iter << endl;
	cout << "x=" << x2 << endl;
	cout << "f1(x)=" << f1(x2) << endl;
	cout << endl;
}

//-----------------------
// Task 2

float f2(float x)
{
	return exp(-2*x) + 2 - powf(5, x);
}

float fi(float x)
{
	return log(2+exp(-2*x)) / log(5);
}

void mi(float x) // metod iteraciy
{
	cout << "Prostie iteracii" << endl;
	int iter = 0;
	float x2 = x;
	while(fabs(f2(x2)) > EPS)
	{
		x2 = fi(x2);
	}
	
	cout << "iter=" << iter << endl;
	cout << "x=" << x2 << endl;
	cout << "f2(x)=" << f2(x2) << endl;
	cout << endl;
}

float df2(float x)
{
	return -2*exp(-2*x) - powf(5, x) * log(5);
}

void mn(float x)
{
	cout << "Newton" << endl;
	int iter=0;
	float x1, x2;
    x1=x;
    x2=x1-f2(x1)/df2(x1);
    while(fabs(f2(x2))>EPS)
    {
        x1=x2;
        x2=x1-f2(x1)/df2(x1);
        iter++;
	}
	
	cout << "iter=" << iter << endl;
	cout << "x=" << x2 << endl;
	cout << "f2(x)=" << f2(x2) << endl;
	cout << endl;  
}
//-----------------------
// Task 3

float g1(float x[2])
{
	return x[0]*x[0]+x[1]*x[1]-9;
}

float g2(float x[2])
{
	return x[1]-exp(-x[0])-1;
}

float g11(float x[2])
{
	return 2*x[0];
}

float g21(float x[2])
{
	return -exp(-x[0]);
}

float g12(float x[2])
{
	return 2*x[1];
}

float g22(float x[2])
{
	return 1;
}

int inverse(float m[2][2])
{
	float a = m[0][0], b = m[0][1];
	float c = m[1][0], d = m[1][1];
	
	float det = a*d - b*c;
	if(fabs(det) < EPS)
	{
		cout << "inverse error: det==0!" << endl;
		return 1; // can't inverse
	}
	m[0][0] =  d/det; m[0][1] = -b/det;
	m[1][0] = -c/det; m[1][1] = a/det;
	
	return 0; // ok
}

void mn_syst(float x2[2])
{
	cout << "Newton dlya sistemi" << endl;
	int iter=0;
    float x1[2];

	do 
	{
	    x1[0]=x2[0]; x1[1] = x2[1]; // x1 = x2
	    
		float J[2][2] = {{g11(x1), g12(x1)},
		                 {g21(x1), g22(x1)}}; 
		
		inverse(J);
		
	  	x2[0] = x1[0] - (J[0][0]*g1(x1) + J[0][1]*g2(x1));
	  	x2[1] = x1[1] - (J[1][0]*g1(x1) + J[1][1]*g2(x1));
	  
	    iter++;
	}	
	while(fabs(x2[0]-x1[0]) > EPS || fabs(x2[1]-x1[1]) > EPS);
	
	cout << "iter=" << iter << endl;
	cout << "X = [" << x2[0] << ", " << x1[0] << "]" << endl;
	cout << "g1(X) =" << g1(x2) << endl;
	cout << "g2(X) =" << g2(x2) << endl;
	cout << endl;
}

int main()
{
	cout << "LABA 2 - VARIANT 14" << endl;
	
	cout << "EPS = " << EPS << endl << endl;
	
	cout << "Task 1" << endl;
	cout << "----------------" << endl;
	float a = -0.5, b= 0;
	
	md(a,b);
	mh(a,b);
	
	cout << "Task 2" << endl;
	cout << "----------------" << endl;
	mi(0);
	mn(0);
	
	cout << "Task 3" << endl;
	cout << "----------------" << endl;
	float x[2] = {-0.5, 2};
	mn_syst(x);
}
