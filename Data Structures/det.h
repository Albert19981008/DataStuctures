#pragma once

#include "matrix.h"
#include <iostream>
using namespace std;

class Det : public matrix<double>
{
public:
	double calcVal(int n = 1);
	Det(const matrix<double> ma);
private:
	int order;
};

inline double Det::calcVal(int n)
{
	if (n == order) {
		cout << "finished!" << endl;
		return this->operator()(n, n);
	}
	for (int i = n + 1; i <= order; ++i) {
		double k = this->operator()(i, n) / this->operator()(n, n);
		for(int j = n + 1; j <= order; ++j) 
			this->operator()(i, j) -= k * this->operator()(n, j);
	}
	return this->operator()(n, n) * this->calcVal(n + 1);
}

Det::Det(const matrix<double> ma) : matrix(ma)
{
	if (ma.columns() != ma.rows())throw illegalValue("illegalValue");
	order = ma.rows();
}