/*
 * algebra.h
 *
 *  Created on: Jul 15, 2014
 *      Author: Drew
 */

#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#include <math.h>

namespace alg
{
	int      sign (int);
	long int sign (long int);
	int      sign (float);

	size_t min (size_t, size_t);
	size_t max (size_t, size_t);

	template<typename Data>
	Data abs(Data);

	long double abs_long_d(long double);
}

template<typename Data>
Data alg::abs(Data value)
{
	return value < (Data)0 ? -value : value;
}

#endif /* ALGEBRA_H_ */
