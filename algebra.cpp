#include "algebra.h"

template int         alg::abs<int>        (int);
template long        alg::abs<long>       (long);
template long long   alg::abs<long long>  (long long);
template float       alg::abs<float>      (float);
template double      alg::abs<double>     (double);
template long double alg::abs<long double>(long double);

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

size_t alg::min(size_t size1, size_t size2)
{
	size_t smallest = size1;

	if(size2 < size1)
	{
		smallest = size2;
	}

	return smallest;
}

size_t alg::max(size_t size1, size_t size2)
{
	size_t largest = size1;

	if(size2 > size1)
	{
		largest = size2;
	}

	return largest;
}

long double alg::abs_long_d(long double value)
{
	if(value < 0)
	{
		value = -value;
	}

	return value;
}
