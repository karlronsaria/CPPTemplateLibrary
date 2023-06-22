/*
 * Modular.h
 *
 *  Created on: Jul 17, 2014
 *      Author: Drew
 */

#ifndef MODULAR_H_
#define MODULAR_H_

#include "algebra.h"
#include "Specialize/ExpandedNumericClass.h"

template<typename Data>
class Modular: private ExpandedIntegralClass<Data>
{
	private:

		Data lower_bound;
		Data upper_bound;

	protected:

		Data value;

	public:

		Modular         (Data modulus);
		Modular         (Data lowerBound, Data upperBound);
		Modular         (const Modular &object);
	   ~Modular         ();

	    Data lower      () const;
	    Data upper      () const;

		Data get_value  () const;
		Data period     () const;
		Data modulus    () const;
		Data conjugate  () const;

		void set_value  (Data number);
		void add_value  (Data number);

		operator int    ();
		operator size_t ();

		std::ostream & operator<<(std::ostream &out) const;

//		Data     & operator() () const;
//		Data     & operator() (Data number);

		template<typename Numeric_Type>
		Modular  & operator=  (Numeric_Type number);

		Modular  & operator=  (const Modular &OBJECT);

		Modular  & operator+= (Data number);
		Modular  & operator-= (Data number);
		Modular  & operator*= (Data number);
		Modular  & operator/= (Data number);

		Modular  & operator+= (const Modular &OBJECT);
		Modular  & operator-= (const Modular &OBJECT);
		Modular  & operator*= (const Modular &OBJECT);
		Modular  & operator/= (const Modular &OBJECT);

		const Data operator+ (Data number) const;
		const Data operator- (Data number) const;
		const Data operator* (Data number) const;
		const Data operator/ (Data number) const;

		const Data operator+ (const Modular &OBJECT) const;
		const Data operator- (const Modular &OBJECT) const;
		const Data operator* (const Modular &OBJECT) const;
		const Data operator/ (const Modular &OBJECT) const;

		const Modular operator- () const ;

		template<typename Type_1, typename Type_2>
		friend const Modular<Type_2> operator+(              Type_1   number,
				                               const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend const Modular<Type_2> operator-(              Type_1   number,
                                               const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend const Modular<Type_2> operator*(              Type_1   number,
                                               const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend const Modular<Type_2> operator/(              Type_1   number,
                                               const Modular<Type_2> &OBJECT);


		template<typename Numeric_Type>
		bool operator<  (const Numeric_Type NUMBER) const;

		template<typename Numeric_Type>
		bool operator>  (const Numeric_Type NUMBER) const;

		template<typename Numeric_Type>
		bool operator<= (const Numeric_Type NUMBER) const;

		template<typename Numeric_Type>
		bool operator>= (const Numeric_Type NUMBER) const;

		template<typename Numeric_Type>
		bool operator== (const Numeric_Type NUMBER) const;

		template<typename Numeric_Type>
		bool operator!= (const Numeric_Type NUMBER) const;


		template<typename Type_1, typename Type_2>
		friend bool operator<  (const         Type_1   NUMBER,
				                const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend bool operator>  (const         Type_1   NUMBER,
				                const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend bool operator<= (const         Type_1   NUMBER,
                                const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend bool operator>= (const         Type_1   NUMBER,
                                const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend bool operator== (const         Type_1   NUMBER,
                                const Modular<Type_2> &OBJECT);

		template<typename Type_1, typename Type_2>
		friend bool operator!= (const         Type_1   NUMBER,
                                const Modular<Type_2> &OBJECT);


		template<typename Numeric_Type>
		friend std::ostream & operator<<(std::ostream                &out,
				                         const Modular<Numeric_Type> &OBJECT);
};

//typedef Modular<int>       modular_int;
typedef Modular<long>      modular_long;
typedef Modular<long long> modular_long_long;

template<typename Data>
Modular<Data>::Modular(Data modulus)
{
	if(modulus >= 0)
	{
		lower_bound = 0;
		upper_bound = modulus;
		value 		= 0;
	}
	else
	{
		lower_bound = modulus;
		upper_bound = 0;
		value 		= modulus;
	}
}

template<typename Data>
Modular<Data>::Modular(Data lowerBound, Data upperBound)
{
	lower_bound = lowerBound;
	upper_bound = upperBound;
	value       = lowerBound;
}

template<typename Data>
Modular<Data>::Modular(const Modular &object)
{
	lower_bound = object.lower_bound;
	upper_bound = object.upper_bound;
	value       = object.value;
}

template<typename Data>
Modular<Data>::~Modular() {}

template<typename Data>
Data Modular<Data>::lower() const
{
	return lower_bound;
}

template<typename Data>
Data Modular<Data>::upper() const
{
	return upper_bound;
}

template<typename Data>
Data Modular<Data>::get_value() const
{
	return value;
}

template<typename Data>
Data Modular<Data>::period() const
{
	return alg::abs(upper_bound - lower_bound);
}

template<typename Data>
Data Modular<Data>::modulus() const
{
	return period();
}

template<typename Data>
Data Modular<Data>::conjugate() const
{
	return upper_bound - value;
}

template<typename Data>
void Modular<Data>::set_value(Data number)
{
	value = number;
}

template<typename Data>
void Modular<Data>::add_value(Data number)
{
	Data temp;

	temp   = number % period();

	value += temp;

	if(value >= upper_bound)
	{
		value -= period();
	}
	else if(value < lower_bound)
	{
		value += period();
	}
}

// Typecast Conversion

template<typename Data>
Modular<Data>::operator int()
{
	return int(value);
}

template<typename Data>
Modular<Data>::operator size_t()
{
	size_t sizeValue = 0;

	if(value > 0)
	{
		sizeValue = size_t(value);
	}

	return sizeValue;
}

// Output Stream (Constant)

template<typename Data>
std::ostream & Modular<Data>::operator<<(std::ostream &out) const
{
	out << *this;

	return out;
}

//// Parenthetical
//
//template<typename Data>
//Data & Modular<Data>::operator()() const
//{
//	return value;
//}
//
//template<typename Data>
//Data & Modular<Data>::operator()(Data number)
//{
//	value = lower_bound;
//
//   *this += (number - lower_bound);
//
//	return value;
//}

// Assignment

template<typename Data>
template<typename Numeric_Type>
Modular<Data> & Modular<Data>::operator=(Numeric_Type number)
{
	value = lower_bound;

   *this += (number - lower_bound);

	return *this;
}

template<typename Data>
Modular<Data> & Modular<Data>::operator=(const Modular &OBJECT)
{
	value = lower_bound;

   *this += OBJECT.value - lower_bound;

	return *this;
}

// Compound Arithmetic (Data)

template<typename Data>
Modular<Data> & Modular<Data>::operator+=(Data number)
{
	add_value(number);

	return *this;
}

template<typename Data>
Modular<Data> & Modular<Data>::operator-=(Data number)
{
   *this += -number;

	return *this;
}

template<typename Data>
Modular<Data> & Modular<Data>::operator*=(Data number)
{
   *this = number * value;

	return *this;
}

template<typename Data>
Modular<Data> & Modular<Data>::operator/=(Data number)
{
   *this = number / value;

	return *this;
}

// Compound Arithmetic (Object)

template<typename Data>
Modular<Data> & Modular<Data>::operator+=(const Modular &OBJECT)
{
   *this += OBJECT.value;

	return *this;
}

template<typename Data>
Modular<Data> & Modular<Data>::operator-=(const Modular &OBJECT)
{
   *this -= OBJECT.value;

	return *this;
}

template<typename Data>
Modular<Data> & Modular<Data>::operator*=(const Modular &OBJECT)
{
   *this *= OBJECT.value;

	return *this;
}

template<typename Data>
Modular<Data> & Modular<Data>::operator/=(const Modular &OBJECT)
{
   *this /= OBJECT.value;

	return *this;
}

// Arithmetic Constant (Data)

template<typename Data>
const Data Modular<Data>::operator+(Data number) const
{
	Modular temp(*this);

	temp += number;

	return temp.value;
}

template<typename Data>
const Data Modular<Data>::operator-(Data number) const
{
	Modular temp(*this);

	temp -= number;

	return temp.value;
}

template<typename Data>
const Data Modular<Data>::operator*(Data number) const
{
	Modular temp(*this);

	temp *= number;

	return temp.value;
}

template<typename Data>
const Data Modular<Data>::operator/(Data number) const
{
	Modular temp(*this);

	temp /= number;

	return temp.value;
}

// Arithmetic Constant (Object)

template<typename Data>
const Data Modular<Data>::operator+(const Modular &OBJECT) const
{
	Modular temp(*this);

	temp += OBJECT.value;

	return temp.value;
}

template<typename Data>
const Data Modular<Data>::operator-(const Modular &OBJECT) const
{
	Modular temp(*this);

	temp -= OBJECT.value;

	return temp.value;
}

template<typename Data>
const Data Modular<Data>::operator*(const Modular &OBJECT) const
{
	Modular temp(*this);

	temp *= OBJECT.value;

	return temp.value;
}

template<typename Data>
const Data Modular<Data>::operator/(const Modular &OBJECT) const
{
	Modular temp(*this);

	temp /= OBJECT.value;

	return temp.value;
}

// Unary Opposite

template<typename Data>
const Modular<Data> Modular<Data>::operator-() const
{
	Modular objectCopy(*this);

	objectCopy.value = -objectCopy.value;

	return objectCopy;
}


/****************************
 * --- Friend Operators --- *
 ****************************/

// Arithmetic Constant (Differentiable Data)

template<typename Type_1, typename Type_2>
const Modular<Type_2> operator+(              Type_1   number,
        						const Modular<Type_2> &OBJECT)
{
	return OBJECT + number;
}

template<typename Type_1, typename Type_2>
const Modular<Type_2> operator-(              Type_1   number,
        						const Modular<Type_2> &OBJECT)
{
	return OBJECT - number;
}

template<typename Type_1, typename Type_2>
const Modular<Type_2> operator*(              Type_1   number,
        						const Modular<Type_2> &OBJECT)
{
	return OBJECT * number;
}

template<typename Type_1, typename Type_2>
const Modular<Type_2> operator/(              Type_1   number,
        						const Modular<Type_2> &OBJECT)
{
	return OBJECT / number;
}


template<typename Data>
template<typename Numeric_Type>
bool Modular<Data>::operator<  (const Numeric_Type NUMBER) const
{
	return value < NUMBER;
}

template<typename Data>
template<typename Numeric_Type>
bool Modular<Data>::operator>  (const Numeric_Type NUMBER) const
{
	return value > NUMBER;
}

template<typename Data>
template<typename Numeric_Type>
bool Modular<Data>::operator<= (const Numeric_Type NUMBER) const
{
	return value <= NUMBER;
}

template<typename Data>
template<typename Numeric_Type>
bool Modular<Data>::operator>= (const Numeric_Type NUMBER) const
{
	return value >= NUMBER;
}

template<typename Data>
template<typename Numeric_Type>
bool Modular<Data>::operator== (const Numeric_Type NUMBER) const
{
	return value == NUMBER;
}

template<typename Data>
template<typename Numeric_Type>
bool Modular<Data>::operator!= (const Numeric_Type NUMBER) const
{
	return value != NUMBER;
}


template<typename Type_1, typename Type_2>
bool operator<  (const Type_1 NUMBER, const Modular<Type_2> &OBJECT)
{
	return NUMBER < OBJECT.value;
}

template<typename Type_1, typename Type_2>
bool operator>  (const Type_1 NUMBER, const Modular<Type_2> &OBJECT)
{
	return NUMBER > OBJECT.value;
}

template<typename Type_1, typename Type_2>
bool operator<= (const Type_1 NUMBER, const Modular<Type_2> &OBJECT)
{
	return NUMBER <= OBJECT.value;
}

template<typename Type_1, typename Type_2>
bool operator>= (const Type_1 NUMBER, const Modular<Type_2> &OBJECT)
{
	return NUMBER >= OBJECT.value;
}

template<typename Type_1, typename Type_2>
bool operator== (const Type_1 NUMBER, const Modular<Type_2> &OBJECT)
{
	return NUMBER == OBJECT.value;
}

template<typename Type_1, typename Type_2>
bool operator!= (const Type_1 NUMBER, const Modular<Type_2> &OBJECT)
{
	return NUMBER != OBJECT.value;
}

// Output Stream Operator

template<typename Numeric_Type>
std::ostream & operator<<(std::ostream                &out,
		                  const Modular<Numeric_Type> &OBJECT)
{
	out << OBJECT.value;

	return out;
}

#endif /* MODULAR_H_ */
