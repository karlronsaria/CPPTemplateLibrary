/*
 * modular_int.h
 *
 *  Created on: Jul 17, 2014
 *      Author: Drew
 */

#ifndef MODULAR_INT_H_
#define MODULAR_INT_H_

#include "Modular.h"

class modular_int: public Modular<int>
{
	public:

		modular_int (int modulus):
						Modular<int>::Modular(modulus) {};
		modular_int (int lowerBound, int upperBound):
						Modular<int>::Modular(lowerBound, upperBound) {};
		modular_int (const modular_int &object):
						Modular<int>::Modular(object) {};
	   ~modular_int () {};

	    using Modular<int>::operator=;
//	    modular_int & operator=  (int number);  /* A workaround. */

		modular_int & operator++ ();
		modular_int   operator++ (int);
		modular_int & operator-- ();
		modular_int   operator-- (int);
};

//modular_int & modular_int::operator=(int number)
//{
//	(*this)(number);
//
//	return *this;
//}

modular_int & modular_int::operator++()
{
   *this += 1;

	return *this;
}

modular_int modular_int::operator++(int)
{
	modular_int temp(*this);

	++*this;

	return temp;
}

modular_int & modular_int::operator--()
{
   *this -= 1;

	return *this;
}

modular_int modular_int::operator--(int)
{
	modular_int temp = *this;

	--*this;

	return temp;
}



#endif /* MODULAR_INT_H_ */
