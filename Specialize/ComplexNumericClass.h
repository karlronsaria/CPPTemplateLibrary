/*
 * ComplexNumericClass.h
 *
 *  Created on: Jul 20, 2014
 *      Author: Drew
 */

#ifndef COMPLEXNUMERICCLASS_H_
#define COMPLEXNUMERICCLASS_H_

#include "Radial.h"

template<typename T>
class ComplexNumericClass;

template<> class ComplexNumericClass<int> {};
template<> class ComplexNumericClass<long> {};
template<> class ComplexNumericClass<long long> {};
template<> class ComplexNumericClass<float> {};
template<> class ComplexNumericClass<double> {};
template<> class ComplexNumericClass<long double> {};
template<> class ComplexNumericClass<radian> {};
template<> class ComplexNumericClass<long_radian> {};
template<> class ComplexNumericClass<long_long_radian> {};

#endif /* COMPLEXNUMERICCLASS_H_ */
