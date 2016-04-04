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

	size_t smallest_size (size_t size1, size_t size2);
	size_t largest_size  (size_t size1, size_t size2);

	template<typename Data>
	Data abs(Data value);

	template int         abs<int>        (int);
	template long        abs<long>       (long);
	template long long   abs<long long>  (long long);
	template float       abs<float>      (float);
	template double      abs<double>     (double);
	template long double abs<long double>(long double);

	long double abs_long_d(long double value);
}

int alg::sign(int value)
{
	int unit;

	if(value >= 0)
	{
		unit = 1;
	}
	else
	{
		unit = -1;
	}

	return unit;
}

long int alg::sign(long int value)
{
	long int unit;

	if(value >= 0)
	{
		unit = 1;
	}
	else
	{
		unit = -1;
	}

	return unit;
}

int alg::sign(float value)
{
	return sign(int(value));
}

size_t alg::smallest_size(size_t size1, size_t size2)
{
	size_t smallest = size1;

	if(size2 < size1)
	{
		smallest = size2;
	}

	return smallest;
}

size_t alg::largest_size(size_t size1, size_t size2)
{
	size_t largest = size1;

	if(size2 > size1)
	{
		largest = size2;
	}

	return largest;
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

long double alg::abs_long_d(long double value)
{
	if(value < 0)
	{
		value = -value;
	}

	return value;
}

#endif /* ALGEBRA_H_ */
