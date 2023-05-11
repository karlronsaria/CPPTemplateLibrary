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
	int      sign (int      value);
	long int sign (long int value);
	int      sign (float    value);

	/*
	karlr (2023_05_06)
	- rename from `smallest_size`
	*/
	size_t min (size_t size1, size_t size2);

	/*
	karlr (2023_05_06)
	- rename from `largest_size`
	*/
	size_t max (size_t size1, size_t size2);

	template<typename Data>
	Data abs(Data value);

	long double abs_long_d(long double value);
}

template<typename Data>
Data alg::abs(Data value)
{
	if(value < 0)
	{
		value = -value;
	}

	return value;
}

#endif /* ALGEBRA_H_ */
