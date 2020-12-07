#include "solver.h"

double Solver::integrate(func function, double from, double to)
{
	return function( (from + to) / 2. ) * (to - from);
}

vecvec Solver::calc_coefs()
{
	double x_curr = step;
	vecvec res = { {}, {}, {0} };  // initial condition 1

	for (size_t i = 1; i < n; i++)
	{
		if (x_curr < break_point)
		{
			double a = 1. / (n * integrate(k_1, x_curr - step, x_curr));
			res[0].push_back(a);
		}
		else if (x_curr - break_point < step)
		{
			double a = 1. / (n * integrate(k_1, x_curr - step, break_point) 
			        	   + n * integrate(k_2, break_point, x_curr));
			res[0].push_back(a);
		}
		else
		{
			double a = 1. / (n * integrate(k_2, x_curr - step, x_curr));
			res[0].push_back(a);
		}

		x_curr += step;
	}

	x_curr = 3 * step / 2.;

	for (size_t i = 1; i < n - 1; i++)
	{
		if (x_curr < break_point)
		{
			double f = n * integrate(f_1, x_curr - step, x_curr);
			double d = n * integrate(q_1, x_curr - step, x_curr);

			res[1].push_back(d);
			res[2].push_back(f);
		}
		else if (x_curr - break_point < step)
		{
			double f = n * integrate(f_1, x_curr - step, break_point) 
				     + n * integrate(f_2, break_point, x_curr);
			double d = n * integrate(q_1, x_curr - step, break_point)
				     + n * integrate(q_2, break_point, x_curr);

			res[1].push_back(d);
			res[2].push_back(f);
		}
		else
		{
			double f = n * integrate(f_2, x_curr - step, x_curr);
			double d = n * integrate(q_2, x_curr - step, x_curr);

			res[1].push_back(d);
			res[2].push_back(f);
		}
	}

	res[2].push_back(0);  // initial condition 2

	return res;
}

vecvec Solver::coefs_to_system(vecvec coefs)
{
	vecvec res = { {0}, {1}, {0} , coefs[2]};

	for (size_t i = 1; i < n; i++)
	{
		double a = coefs[0][i] / (step * step);
		double b = coefs[0][i + 1] / (step * step);
		double c = -1 * (a + b + coefs[1][i]);

		res[0].push_back(a);
		res[1].push_back(c);
		res[2].push_back(b);
	}

	res[0].push_back(0);
	res[1].push_back(1);
	res[2].push_back(0);

	return res;
}


/**
	* n - число уравнений (строк матрицы)
	* b - диагональ, лежащая над главной (нумеруется: [0;n-2])
	* c - главная диагональ матрицы A (нумеруется: [0;n-1])
	* a - диагональ, лежащая под главной (нумеруется: [1;n-1])
	* f - правая часть (столбец)
	* x - решение, массив x будет содержать ответ
*/
vec Solver::solve_matrix(vecvec matrix)
{		
	vec a = matrix[0];
	vec c = matrix[1];
	vec b = matrix[2];
	vec f = matrix[3];
	vec x;

	for (size_t i = 0; i < n; i++)
	{
		x.push_back(0);
	}
		
	double m;
	for (int i = 1; i < n; i++)
	{
		m = a[i] / c[i - 1];
		c[i] = c[i] - m * b[i - 1];
		f[i] = f[i] - m * f[i - 1];
	}

	x[n - 1] = f[n - 1] / c[n - 1];

	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = (f[i] - b[i] * x[i + 1]) / c[i];
	}

	return x;
}

Solver::Solver(
	int n_, 
	double break_point_, 
	func k_1_, 
	func q_1_, 
	func f_1_, 
	func k_2_, 
	func q_2_, 
	func f_2_
)
{
	n = n_;
	step = 1. / n_;
	break_point = break_point_;
	k_1 = k_1_;
	q_1 = q_1_;
	f_1 = f_1_;
	k_2 = k_2_;
	q_2 = q_2_;
	f_2 = f_2_;
	
}

vec Solver::solve()
{
	return(solve_matrix(coefs_to_system(calc_coefs())));
}
