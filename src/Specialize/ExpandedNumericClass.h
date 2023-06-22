/*
 * ExpandedNumericClass.h
 *
 *  Created on: Jul 10, 2014
 *      Author: Drew
 */

#ifndef EXPANDEDNUMERICCLASS_H_
#define EXPANDEDNUMERICCLASS_H_

//#include "Complex.h"  [!] Circular Dependency
#include "../Rational.h"

template<typename T>
class ExpandedNumericClass;

template<> class ExpandedNumericClass<int> {};
template<> class ExpandedNumericClass<long> {};
template<> class ExpandedNumericClass<long long> {};
template<> class ExpandedNumericClass<float> {};
template<> class ExpandedNumericClass<double> {};
template<> class ExpandedNumericClass<long double> {};
//template<> class ExpandedNumericClass<complex_int> {};
//template<> class ExpandedNumericClass<complex_float> {};
template<> class ExpandedNumericClass<rational_int> {};
template<> class ExpandedNumericClass<rational_long> {};
template<> class ExpandedNumericClass<rational_long_long> {};

template<typename T>
class ExpandedIntegralClass;

template<> class ExpandedIntegralClass<int> {};
template<> class ExpandedIntegralClass<long> {};
template<> class ExpandedIntegralClass<long long> {};
template<> class ExpandedIntegralClass<rational_int> {};
template<> class ExpandedIntegralClass<rational_long> {};
template<> class ExpandedIntegralClass<rational_long_long> {};

template<typename Integral_Type>
double to_double(Integral_Type integral);

template<typename Integral_Type>
double to_double(Rational<Integral_Type> rationalNum);

template<> double to_double(int       integral);
template<> double to_double(long      integral);
template<> double to_double(long long integral);

template<typename Integral_Type>
double to_double(Integral_Type integral)
{
	return integral;
}

template<typename Integral_Type>
double to_double(Rational<Integral_Type> rationalNum)
{
	return rationalNum.to_double();
}

#endif /* EXPANDEDNUMERICCLASS_H_ */
