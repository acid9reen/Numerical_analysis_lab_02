#pragma once

#include <functional>
#include <vector>

using func = std::function<double(double)>;
using vec = std::vector<double>;
using vecvec = std::vector<std::vector<double>>;

class Solver
{
private:
	double n;
	double step;
	double break_point;
	func k_1, q_1, f_1;
	func k_2, q_2, f_2;
	double integrate(func function, double from, double to);
	vecvec calc_coefs();
	vecvec coef_to_system(vecvec coefs);

public:
	Solver(
		int n_,
		double p_,
		func k_1_, func q_1_, func f_1_,
		func k_2_, func q_2_, func f_2_
	);
};

