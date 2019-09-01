#pragma once

#include "errors.h"



template<class T>
class matrix
{
public:
	matrix(int n = 1, int m = 1);
	matrix(const matrix<T> &);
	~matrix() { delete[] element; };

	T & operator() (int i, int j) const;
	int rows() const { return theRows; }
	int columns() const { return theColumns; }
	matrix<T> operator+(const matrix<T> &r);
	matrix<T> operator-(const matrix<T> &r);
	matrix<T> operator*(const matrix<T> &r);
private:
	T *element;
	int theRows, theColumns;
};

template<class T>
inline matrix<T>::matrix(int n, int m) : theRows(n), theColumns(m)
{
	element = new T[n * m];
}

template<class T>
inline matrix<T>::matrix(const matrix<T> &t2) : theRows(t2.theRows), theColumns(t2.theColumns)
{
	element = new T[theRows * theColumns];
	for (int i = 0; i < theRows * theColumns; ++i)
		element[i] = t2.element[i];
}

template<class T>
inline T & matrix<T>::operator() (int i, int j) const
{
	return element[theColumns * (i - 1) + j - 1];
}

template<class T>
inline matrix<T> matrix<T>::operator+(const matrix<T> &r)
{
	if (theColumns != r.theColumns || theRows != r.theRows)
		throw illegalValue("illegal matrix");

	matrix res(theRows, theColumns);
	for (int i = 0; i < theColumns * theRows; ++i)
		res.element[i] = this->element[i] + r.element[i];

	return res;
}

template<class T>
inline matrix<T> matrix<T>::operator-(const matrix<T>& r)
{
	if (theColumns != r.theColumns || theRows != r.theRows)
		throw illegalValue("illegal matrix");

	matrix res(theRows, theColumns);
	for (int i = 0; i < theColumns * theRows; ++i)
		res.element[i] = this->element[i] - r.element[i];
	return res;
}

template<class T>
inline matrix<T> matrix<T>::operator*(const matrix<T>& r)
{
	if (theColumns != r.theRows)
		throw illegalValue("illegal matrix");

	int n = this->theRows, m = this->theColumns, s = r.theColumns;
	matrix<T> res(n, s);

	for(int i = 1; i <= n; ++i)
		for (int j = 1; j <= s; ++j) {
			T tmp(0);
			for (int k = 1; k <= m; ++k)
				tmp += this->operator()(i, k) * r(k, j);
			//if (tmp > 10000) tmp %= 10000;
			res(i, j) = tmp;
		}
	return res;
}

template<class T>
ostream &operator << (ostream &os, const matrix<T> &ma) {
	int n = ma.rows(), m = ma.columns();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			os << ma(i, j) << " ";
		os << endl;
	}
	return os;
}

template<class T>
matrix<T> operator^(const matrix<T> &ma, int x) {
	if (x <= 0)throw illegalValue("illegalValue");
	int n = ma.rows(), m = ma.columns();

	if (n != m)throw illegalValue("illegalValue");
	if (x == 1)return ma;

	matrix<T> tmp = ma ^ (x / 2);

	if (x & 1)return tmp * tmp * ma;

	return tmp * tmp;
}