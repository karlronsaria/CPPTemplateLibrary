#include "algebra.h"

template int         alg::abs<int>        (int);
template long        alg::abs<long>       (long);
template long long   alg::abs<long long>  (long long);
template float       alg::abs<float>      (float);
template double      alg::abs<double>     (double);
template long double alg::abs<long double>(long double);

int alg::sign(int value)
{
	return value >= 0 ? 1 : -1;
}

long int alg::sign(long int value)
{
	return value >= 0 ? 1L : -1L;
}

int alg::sign(float value)
{
	return sign(int(value));
}

size_t alg::min(size_t size1, size_t size2)
{
	return size2 < size1 ? size2 : size1;
}

size_t alg::max(size_t size1, size_t size2)
{
	return size2 > size1 ? size2 : size1;
}

long double alg::abs_long_d(long double value)
{
	return value < 0 ? -value : value;
}
