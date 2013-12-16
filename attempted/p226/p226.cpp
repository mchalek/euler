#include<cstdio>
#include<cmath>

double y(double);

int main(void)
{
	for(int i = 0; i < 10; i++)
		printf("y(%g) == %g\n", 0.1*i+0.3145, y(0.1*i+0.3145));

	return 0;
}

double y(double x)
{
	int n = 0;
	double tmp;
	double s, ret=0, twon;
	twon = 1;
	for(n = 0; n < 33; n++) {
		tmp = twon * x;
		s = tmp - floor(tmp) < ceil(tmp) - tmp ? tmp - floor(tmp) : ceil(tmp) - tmp;
		printf("s == %g\n", s);
		ret += s / twon;
		twon *= 2;
	}

	return ret;
}