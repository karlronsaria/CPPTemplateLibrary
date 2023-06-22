/*
 * NumericClass_Template.h
 *
 *  Created on: Jun 30, 2014
 *      Author: adaniels4
 */

#ifndef NUMERICCLASS_H_
#define NUMERICCLASS_H_

template<typename T>
class IntegralClass;

template<> class IntegralClass<int> {};
template<> class IntegralClass<long> {};
template<> class IntegralClass<long long> {};

template<typename T>
class FloatingPointClass;

template<> class FloatingPointClass<float> {};
template<> class FloatingPointClass<double> {};
template<> class FloatingPointClass<long double> {};

template<typename T>
class NumericClass;

template<> class NumericClass<int> {};
template<> class NumericClass<long> {};
template<> class NumericClass<long long> {};
template<> class NumericClass<float> {};
template<> class NumericClass<double> {};
template<> class NumericClass<long double> {};

#endif /* NUMERICCLASS_H_ */
