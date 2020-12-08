#pragma once

#include <cmath>

namespace functions
{
	double k_1_test(double x)
	{
		return 1 / 2.25;
	}

	double k_2_test(double x)
	{
		return 4;
	}

	double q_1_test(double x)
	{
		return 1;
	}

	double q_2_test(double x)
	{
		return 1;
	}

	double f_1_test(double x)
	{
		return 0;
	}

	double f_2_test(double x)
	{
		return 1;
	}

	double k_1_main(double x)
	{
		return pow(x + 1, 2);
	}

	double k_2_main(double x)
	{
		return pow(x, 2);
	}

	double q_1_main(double x)
	{
		return exp(-x) * exp(0.5);
	}

	double q_2_main(double x)
	{
		return exp(x) / exp(0.5);
	}

	double f_1_main(double x)
	{
		return cos(M_PI * x);
	}

	double f_2_main(double x)
	{
		return 1;
	}
}
