/*
 * Rational.h
 *
 *  Created on: Jul 15, 2014
 *      Author: Drew
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <iostream>
#include <sstream>
#include <limits>
#include "algebra.h"
#include "Specialize/NumericClass.h"
using namespace alg;

enum ProprietyType
{
	STANDARD_RATIO,
	STRICT_FRACTION
};

enum RatioForm
{
	SIMPLIFIED,
	UNSIMPLIFIED
};

enum Notation
{
	FRACTION,
	RATIO,
	PERCENT,
	DECIMAL
};

template <typename Data>
class Rational: private IntegralClass<Data>
{
	private:

		Data _numer;
		Data _denom;

		ProprietyType _type;
		RatioForm     _form;

	protected:

		/*******************************
		 * --- Protected Functions --- *
		 *******************************/

		// Mutators

		void initialize      ();
		void set_type        (const ProprietyType &);
		void set_numerator   (const Data          &);
		void set_denominator (const Data          &);
		void rationalize     (float);

		template<typename Numeric_Type>
		void rationalize     (const Rational<Numeric_Type> &);
		void commonize       (Rational       &object);

	public:

		/*************************************
		 * --- Constructors & Destructor --- *
		 *************************************/

		// Standard Constructors

		Rational();
		Rational(const Rational      &);
		Rational(const ProprietyType &);
		Rational(const RatioForm     &);
		Rational(const ProprietyType &, const RatioForm &);

		// Value-setting Constructors

		Rational(const Data &);
		Rational(const Data &, const Data &);
		Rational(const Data &, const Data &, const ProprietyType &);
		Rational(const Data &, const Data &, const RatioForm     &);
		Rational(const Data &, const Data &, const ProprietyType &,
				                             const RatioForm     &);

		// Destructor

	   ~Rational();


		/******************************
		 * --- Named Constructors --- *
		 ******************************/

	    template <typename Numeric_Type>
	    friend Rational<Numeric_Type> rational   (const Numeric_Type &);

	    template <typename Numeric_Type>
	    friend Rational<Numeric_Type> rational   (const Numeric_Type &,
	    		                                  const Numeric_Type &);
	    template <typename Numeric_Type>
	    friend Rational<Numeric_Type> reciprocal (const Numeric_Type &);


		/*********************
		 * --- Accessors --- *
		 *********************/

	    // Standard Accessors

		const ProprietyType & type               () const;
		const RatioForm     & form               () const;
		const Data          & numerator          () const;
		const Data          & denominator        () const;

		// Calculations

		const float         & ratio              () const;
		const double        & precise_ratio      () const;
		const long double   & very_precise_ratio () const;
		const Rational      & reciprocal         () const;

		// Verifiers

		      bool            is_whole           () const;
		      bool            is_proper          () const;
		      bool            common_with        (const Rational &) const;

		// Arithmetic

		const Rational      & add                (const Rational &);
		const Rational      & subtract           (const Rational &);
		const Rational      & multiply           (const Rational &);
		const Rational      & divide             (const Rational &);


		/********************
		 * --- Mutators --- *
		 ********************/

		// Standard Mutators

		void                  form                (const RatioForm &);
		void                  numerator           (const Data &);
		void                  denominator         (const Data &);

		// Calculations

		Rational            & simplify            ();
		Rational            & reciprocate         ();


		/****************************
		 * --- Friend Functions --- *
		 ****************************/

		template <typename Numeric_Type>
		friend bool are_common(const Rational<Numeric_Type> &,
							   const Rational<Numeric_Type> &);


		friend Rational<int> rationalize(double value);

		template <typename Numeric_Type>
		friend void commonize
					(Rational<Numeric_Type>         &,
				     Rational<Numeric_Type>         &);

		template <typename Numeric_Type>
		friend Rational<Numeric_Type> simplify
					(const Rational<Numeric_Type>   &);

		template <typename Numeric_Type>
		friend Rational<Numeric_Type> abs
					(const Rational<Numeric_Type>   &);

		template <typename Numeric_Type>
		friend float sqrt
					(const Rational<Numeric_Type>   &);

		template <typename Type_1, typename Type_2>
		friend float pow
					(const Type_2                   &,
					 const Rational<Type_1>         &);

		template <typename Type_1, typename Type_2>
		friend float pow
					(const Rational<Type_1>         &,
					 const Type_2                   &);

		template <typename Type_1, typename Type_2>
		friend float pow
					(const Rational<Type_1>         &,
					 const Rational<Type_2>         &);

		template <typename Numeric_Type>
		friend float cos
					(const Rational<Numeric_Type>   &);

		template <typename Numeric_Type>
		friend float sin
					(const Rational<Numeric_Type>   &);

		template <typename Numeric_Type>
		friend float exp
					(const Rational<Numeric_Type>   &);


		/***********************************
		 * --- Parenthetical Operators --- *
		 ***********************************/

	    double     operator()() const;
		Rational & operator()(const Data     &, const Data &);
		Rational & operator()(const Data     &);
		Rational & operator()(const Rational &);


		/*****************************************
		 * --- Typecast Conversion Operators --- *
		 *****************************************/

		// Convert Object to Other Type

		operator int         () const;
		operator long        ();
		operator long long   ();
		operator float       ();
		operator double      ();
		operator long double ();

		operator Rational<int>           () const;
		operator Rational<long int>      () const;
		operator Rational<long long int> () const;


		/***********************************
		 * --- Output Stream Operators --- *
		 ***********************************/

		       std::ostream & operator<< (std::ostream &) const;

		template <typename Numeric_Type>
		friend std::ostream & operator<< (std::ostream                 &,
				                          const Rational<Numeric_Type> &);

		/********************************
		 * --- Assignment Operators --- *
		 ********************************/

		template <typename Numeric_Type>
		Rational & operator=(const Numeric_Type &);

		template <typename Numeric_Type>
		Rational & operator=(const Rational<Numeric_Type> &);


		/********************************
		 * --- Arithmetic Operators --- *
		 ********************************/

		// Compound Arithmetic (Number)

		template <typename Numeric_Type>
		Rational & operator+=(const Numeric_Type &);

		template <typename Numeric_Type>
		Rational & operator-=(const Numeric_Type &);

		template <typename Numeric_Type>
		Rational & operator*=(const Numeric_Type &);

		template <typename Numeric_Type>
		Rational & operator/=(const Numeric_Type &);

		// Compound Arithmetic (Object)

		Rational & operator%=(const Rational &);

		// Arithmetic Constant (Unary Opposite)

		Rational operator-() const;

		// Arithmetic Constant (Number)

		template <typename Numeric_Type>
		Rational operator+(const Numeric_Type &) const;

		template <typename Numeric_Type>
		Rational operator-(const Numeric_Type &) const;

		template <typename Numeric_Type>
		Rational operator*(const Numeric_Type &) const;

		template <typename Numeric_Type>
		Rational operator/(const Numeric_Type &) const;

		// Arithmetic Constant (Object)

		Rational operator%(const Rational &) const;

		// Arithmetic Constant (Number & Object)

		template <typename Numeric_Type>
		friend Rational<Numeric_Type> operator+
					(int number, const Rational<Numeric_Type> &);

		template <typename Numeric_Type>
		friend Rational<Numeric_Type> operator-
					(int number, const Rational<Numeric_Type> &);

		template <typename Numeric_Type>
		friend Rational<Numeric_Type> operator*
					(int number, const Rational<Numeric_Type> &);

		template <typename Numeric_Type>
		friend Rational<Numeric_Type> operator/
					(int number, const Rational<Numeric_Type> &);


		/********************************
		 * --- Relational Operators --- *
		 ********************************/

		// Standard (Object & Number)

		template <typename Numeric_Type>
		bool operator<  (const Numeric_Type) const;

		template <typename Numeric_Type>
		bool operator>  (const Numeric_Type) const;

		template <typename Numeric_Type>
		bool operator<= (const Numeric_Type) const;

		template <typename Numeric_Type>
		bool operator>= (const Numeric_Type) const;

		template <typename Numeric_Type>
		bool operator== (const Numeric_Type) const;

		template <typename Numeric_Type>
		bool operator!= (const Numeric_Type) const;


		// Reverse (Number & Object)

		template <typename Type_1, typename Type_2>
		friend bool operator<  (const          Type_1  &,
				                const Rational<Type_2> &);

		template <typename Type_1, typename Type_2>
		friend bool operator>  (const          Type_1  &,
                                const Rational<Type_2> &);

		template <typename Type_1, typename Type_2>
		friend bool operator<= (const          Type_1  &,
                                const Rational<Type_2> &);

		template <typename Type_1, typename Type_2>
		friend bool operator>= (const          Type_1  &,
                                const Rational<Type_2> &);

		template <typename Type_1, typename Type_2>
		friend bool operator== (const          Type_1  &,
                                const Rational<Type_2> &);

		template <typename Type_1, typename Type_2>
		friend bool operator!= (const          Type_1  &,
                                const Rational<Type_2> &);
};

typedef Rational<int>       rational_int;
typedef Rational<long>      rational_long;
typedef Rational<long long> rational_long_long;


/*******************************
 * --- Protected Functions --- *
 *******************************/

// Mutators

template<typename Data>
void Rational<Data>::initialize()
{
	_numer = 0;
	_denom = 1;
}

template<typename Data>
void Rational<Data>::set_type(const ProprietyType & t)
{
	_type = t;
}

template<typename Data>
void Rational<Data>::set_numerator(const Data & n)
{
	_numer = n;
}

template<typename Data>
void Rational<Data>::set_denominator(const Data & d)
{
	if(d != 0)
	{
		if(d > 0)
		{
			_denom = d;
		}
		else
		{
			_numer *= -1;
			_denom  = abs(d);
		}
	}
}

template<typename Data>
void Rational<Data>::rationalize(float value)
{
	int count;
	int denomValue;

	count      = 0;
	denomValue = (int)pow(10, count);

	while(abs(value - double((int)value)) >
		  std::numeric_limits<double>::epsilon())
	{
		count++;
		denomValue  = (int)pow(10, count);
		value      *= 10;
	}

	set_numerator((int)(value));
	set_denominator(denomValue);
}

template<typename Data>
template<typename Numeric_Type>
void Rational<Data>::rationalize(const Rational<Numeric_Type> & o)
{
	*this = o;
}

template<typename Data>
void Rational<Data>::commonize(Rational & o)
{
	if(!common_with(o))
	{
		form   (UNSIMPLIFIED);
		o.form (UNSIMPLIFIED);

		(*this) (_numer * o._denom, _denom * o._denom);
		      o (_denom * o._numer, _denom * o._denom);
	}
}


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

// Standard Constructors

template<typename Data>
Rational<Data>::Rational():
	_type(STANDARD_RATIO), _form(UNSIMPLIFIED) { initialize(); }

template<typename Data>
Rational<Data>::Rational(const Rational & o):
	_numer(o._numer), _denom(o._denom), _type(o._type), _form(o._form) {}

template<typename Data>
Rational<Data>::Rational(const ProprietyType & t):
	_type(t), _form(UNSIMPLIFIED) { initialize(); }

template<typename Data>
Rational<Data>::Rational(const RatioForm & f):
	_type(STANDARD_RATIO), _form(f) { initialize(); }

template<typename Data>
Rational<Data>::Rational(const ProprietyType & t, const RatioForm & f):
	_type(t), _form(f) { initialize(); }

// Value-setting Constructors

template<typename Data>
Rational<Data>::Rational(const Data & n):
	_numer(n), _denom(1), _type(STANDARD_RATIO), _form(UNSIMPLIFIED) {}

template<typename Data>
Rational<Data>::Rational(const Data & n, const Data & d):
	_type(STANDARD_RATIO), _form(UNSIMPLIFIED)
{
	initialize();

	set_numerator(n);
	set_denominator(d);
}

template<typename Data>
Rational<Data>::Rational(const Data & n, const Data & d,
		                 const ProprietyType & t):
	_type(t), _form(UNSIMPLIFIED)
{
	if(_type == STRICT_FRACTION && abs<Data>(n) > abs<Data>(d))
	{
		std::cerr << std::endl << std::endl

		  << "Rational<>::Rational(Data, Data, ProprietyType): [!] "
		  << "Fraction. Please enter proper fraction parameters."
		  <<  std::endl;
	}
	else
	{
		set_numerator(n);
		set_denominator(d);
	}
}

template<typename Data>
Rational<Data>::Rational(const Data & n, const Data & d,
						 const RatioForm & f):
	_type(STANDARD_RATIO), _form(f), _numer(n), _denom(d)
{
	if(_form == SIMPLIFIED) simplify();
}

template<typename Data>
Rational<Data>::Rational(const Data          & n, const Data      & d,
						 const ProprietyType & t, const RatioForm & f):
		        Rational(t, f)
{
	if(_type == STRICT_FRACTION && abs<Data>(n) > abs<Data>(d))
	{
 	   std::cerr <<  std::endl << std::endl
 	   		     << "Rational<>::Rational(Data, Data, ProprietyType): [!] "
 	   		     << "Fraction. Please enter proper fraction parameters."
 	   		     <<  std::endl;
	}
	else
	{
	   set_numerator(n);
	   set_denominator(d);
	}

	if(_form == SIMPLIFIED) simplify();
}

// Destructor

template<typename Data>
Rational<Data>::~Rational() {}


/***************************************
 * --- Named Constructors (Static) --- *
 ***************************************/

template<typename Numeric_Type>
Rational<Numeric_Type> rational(const Numeric_Type & n)
{
	Rational<Numeric_Type> object(n, 1);

	return object;
}

template<typename Numeric_Type>
Rational<Numeric_Type> rational(const Numeric_Type & n,
		                        const Numeric_Type & d)
{
	Rational<Numeric_Type> object(n, d);

	return object;
}

template<typename Numeric_Type>
Rational<Numeric_Type> reciprocal(const Numeric_Type & d)
{
	Rational<Numeric_Type> object(1, d);

	return object;
}


/*********************
 * --- Accessors --- *
 *********************/

// Standard Accessors

template<typename Data>
const ProprietyType & Rational<Data>::type() const
{
	return _type;
}

template<typename Data>
const RatioForm & Rational<Data>::form() const
{
	return _form;
}

template<typename Data>
const Data & Rational<Data>::numerator() const
{
	return _numer;
}

template<typename Data>
const Data & Rational<Data>::denominator() const
{
	return _denom;
}

// Calculations

template<typename Data>
const float & Rational<Data>::ratio() const
{
	return _numer / (float) _denom;
}

template<typename Data>
const double & Rational<Data>::precise_ratio() const
{
	return _numer / (double) _denom;
}

template<typename Data>
const long double & Rational<Data>::very_precise_ratio() const
{
	return _numer / (long double) _denom;
}

template<typename Data>
const Rational<Data> & Rational<Data>::reciprocal() const
{
	Rational thisCopy(*this);

	thisCopy.reciprocate();

	return thisCopy;
}

// Queries

template <typename Data>
bool Rational<Data>::is_whole() const
{
	return _denom == 1;
}

template <typename Data>
bool Rational<Data>::is_proper() const
{
	return _numer <= _denom;
}

template <typename Data>
bool Rational<Data>::common_with(const Rational & o) const
{
	return _denom == o._denom;
}

// Arithmetic

template <typename Data>
const Rational<Data> & Rational<Data>::add(const Rational & a)
{
	Data n, d;

	n = _numer * a._denom + _denom * a._numer * alg::sign(_numer);
	d = _denom * a._denom;

	if(n > d)
	{
		_type = STANDARD_RATIO;
	}

	numerator(n);
	denominator(d);

	return *this;
}

template <typename Data>
const Rational<Data> & Rational<Data>::subtract(const Rational & s)
{
	add(-s);

	return *this;
}

template <typename Data>
const Rational<Data> & Rational<Data>::multiply(const Rational & m)
{
	_type = STANDARD_RATIO;

	set_denominator (_numer ? _denom * m._denom : 1);
	numerator                (_numer * m._numer);

	return *this;
}

template <typename Data>
const Rational<Data> & Rational<Data>::divide(const Rational & d)
{
	try
	{
		if(d._denom)
		{
			Rational temp(d);

			temp.reciprocate();

			multiply(temp);
		}
		else
		{
			throw "Dividing by zero.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Rational<>::divide(const Rational<> &): [!] "
				  <<  message   << std::endl;
	}

	return *this;
}


/********************
 * --- Mutators --- *
 ********************/

// Standard Mutators

template <typename Data>
void Rational<Data>::form(const RatioForm & f)
{
	_form = f;

	if(f == SIMPLIFIED) simplify();
}

template <typename Data>
void Rational<Data>::numerator(const Data & n)
{
	switch(_type)
	{
		case STANDARD_RATIO  : set_numerator(n);
							   break;
		case STRICT_FRACTION :

			if(abs<Data>(n) <= abs<Data>(_denom))
		    {
				set_numerator(n);
		    }
		    else
		    {
		    	std::cerr << std::endl << std::endl

				  << "Rational<>::numerator(Data): [!] Fraction. "
				  << "Please enter a number whose absolute value "
				  << "is less than or equal to "
				  <<  abs<Data>(_denom) << "." <<  std::endl;
		    }
		    break;
	}

	switch(_form)
	{
		case SIMPLIFIED   : simplify();
							break;
		case UNSIMPLIFIED : break;
	}
}

template <typename Data>
void Rational<Data>::denominator(const Data & d)
{
	switch(_type)
	{
		case STANDARD_RATIO  : set_denominator(d);
							   break;
		case STRICT_FRACTION :

			if(abs(d) >= abs(_numer))
		    {
				set_denominator(d);
		    }
		    else
		    {
				std::cout << std::endl << std::endl

				  << "Rational<>::denominator(Data): [!] Fraction. "
				  << "Please enter a number whose absolute value is "
				  << "greater than or equal to "
				  <<  abs<Data>(_numer) << "." <<  std::endl;
		    }
		    break;
	}

	switch(_form)
	{
		case SIMPLIFIED   : simplify();
							break;
		case UNSIMPLIFIED : break;
	}
}

// Calculations

template <typename Data>
Rational<Data> & Rational<Data>::simplify()
{
	Data *least;
	Data *greatest;

	if(abs(_numer) > abs(_denom))
	{
		least    = &_denom;
		greatest = &_numer;
	}
	else
	{
		least    = &_numer;
		greatest = &_denom;
	}

	for(int count = *least; count > 1; count--)
	{
		if(*least % count == 0 && *greatest % count == 0)
		{
			*least    /= count;
			*greatest /= count;
		}
	}

	_numer *= sign(sign(_numer) * sign(_denom));
	_denom  = abs(_denom);

	return *this;
}

template <typename Data>
Rational<Data> & Rational<Data>::reciprocate()
{
	int n   = _numer;
	int d = _denom;

	_type = STANDARD_RATIO;

	(*this)(1, 1);

	set_denominator(n);
	numerator(d);

	return *this;
}


/****************************
 * --- Friend Functions --- *
 ****************************/

template <typename Numeric_Type>
bool are_common(const Rational<Numeric_Type> & o,
		        const Rational<Numeric_Type> & p)
{
	return o.denominator() == p.denominator();
}

Rational<int> rationalize(double value)
{
	Rational<int> object;

	object.rationalize(value);

	return object;
}

template <typename Numeric_Type>
void commonize(Rational<Numeric_Type> & o,
		       Rational<Numeric_Type> & p)
{
	o.commonize(p);
}

template <typename Numeric_Type>
Rational<Numeric_Type> simplify(const Rational<Numeric_Type> & o)
{
	o.simplify();

	return o;
}

template <typename Numeric_Type>
Rational<Numeric_Type> abs(const Rational<Numeric_Type> & o)
{
	return o(abs<Numeric_Type>(o._numer),
			 abs<Numeric_Type>(o._denom));
}

template <typename Numeric_Type>
float sqrt(const Rational<Numeric_Type> & o)
{
	return sqrt(o());
}

template <typename Type_1, typename Type_2>
float pow(const Type_2 & b, const Rational<Type_1> & l)
{
	return pow(b, l());
}

template <typename Type_1, typename Type_2>
float pow(const Rational<Type_1> & b, const Type_2 & l)
{
	return pow(b(), l);
}

template <typename Type_1, typename Type_2>
float pow(const Rational<Type_1> & b, const Rational<Type_2> & l)
{
	return pow(b(), l());
}

template <typename Numeric_Type>
float cos(const Rational<Numeric_Type> & o)
{
	return cos(o());
}

template <typename Numeric_Type>
float sin(const Rational<Numeric_Type> & o)
{
	return sin(o());
}

template <typename Numeric_Type>
float exp(const Rational<Numeric_Type> & o)
{
	return exp(o());
}


/***********************************
 * --- Parenthetical Operators --- *
 ***********************************/

template <typename Data>
double Rational<Data>::operator()() const
{
	return precise_ratio();
}

template <typename Data>
Rational<Data> & Rational<Data>::operator()(const Data & n,
                                            const Data & d)
{
	switch(_type)
	{
		case STANDARD_RATIO  : set_numerator(n);
							   set_denominator(d);
							   break;
		case STRICT_FRACTION :

			if(abs(n) <= abs(d))
			{
				set_numerator(n);
				set_denominator(d);
			}
			else
			{
				std::cerr << std::endl << std::endl

			      << "Rational<>::operator(Data, Data): [!] Fraction. "
			      << "Please enter proper fraction parameters."
			      << std::endl;
			}
			break;
	}

	switch(_form)
	{
		case SIMPLIFIED   : simplify();
							break;
		case UNSIMPLIFIED : break;
	}

	return *this;
}

template <typename Data>
Rational<Data> & Rational<Data>::operator()(const Data & n)
{
	_type = STANDARD_RATIO;

	set_numerator(n);
	set_denominator(1);

	switch(_form)
	{
		case SIMPLIFIED   : simplify();
							break;
		case UNSIMPLIFIED : break;
	}

	return *this;
}

template <typename Data>
Rational<Data> & Rational<Data>::operator()(const Rational & o)
{
	_type  = o._type;
	_form  = o._form;

	_numer = o._numer;
	_denom = o._denom;

	return *this;
}


/*****************************************
 * --- Typecast Conversion Operators --- *
 *****************************************/

// Convert Object to Other Type

template <typename Data>
Rational<Data>::operator int() const
{
	return int(ratio());
}

template <typename Data>
Rational<Data>::operator long()
{
	return long(ratio());
}

template <typename Data>
Rational<Data>::operator long long()
{
	return (long long)(ratio());
}

template <typename Data>
Rational<Data>::operator float()
{
	return ratio();
}

template <typename Data>
Rational<Data>::operator double()
{
	return precise_ratio();
}

template <typename Data>
Rational<Data>::operator long double()
{
	return very_precise_ratio();
}

template <typename Data>
Rational<Data>::operator Rational<int>() const
{
	return Rational<int>(int(numerator()), int(denominator()),
			             type(), form());
}

template <typename Data>
Rational<Data>::operator Rational<long int>() const
{
	return Rational<long int>((long int)(numerator()),
			                  (long int)(denominator()),
					          type(), form());
}

template <typename Data>
Rational<Data>::operator Rational<long long int>() const
{
	return Rational<long long int>((long long int)(numerator()),
			                       (long long int)(denominator()),
						           type(), form());
}


/***********************************
 * --- Output Stream Operators --- *
 ***********************************/

template <typename Data>
std::ostream & Rational<Data>::operator<<(std::ostream & out) const
{
	out << *this;

	return out;
}

template <typename Numeric_Type>
std::ostream & operator<<(std::ostream                 & out,
		                  const Rational<Numeric_Type> & o)
{
	std::ostringstream oss;

	oss << o.numerator();

	if(o.numerator()) oss << "/" << o.denominator();

	out << oss.str();

	return out;
}


/********************************
 * --- Assignment Operators --- *
 ********************************/

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator=(const Numeric_Type & n)
{
	rationalize(n);

	if(_type == STRICT_FRACTION && !is_proper())
	{
		_type = STANDARD_RATIO;
	}

	if(_form == SIMPLIFIED)
	{
		simplify();
	}

	return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> &
Rational<Data>::operator=(const Rational<Numeric_Type> & o)
{
	_type  = o.type;
	_form  = o.form;

	_numer = o.numer;
	_denom = o.denom;

	return *this;
}


/********************************
 * --- Arithmetic Operators --- *
 ********************************/

// Compound Arithmetic (Number)

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator+=(const Numeric_Type & n)
{
	Rational<Data> temp(*this);

	temp.rationalize(n);

	add(temp);

	return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator-=(const Numeric_Type & n)
{
	Rational<Data> temp(*this);

	temp.rationalize(n);

	subtract(temp);

	return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator*=(const Numeric_Type & n)
{
	Rational<Data> temp(*this);

	temp.rationalize(n);

	multiply(temp);

	return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator/=(const Numeric_Type & n)
{
	Rational<Data> temp(*this);

	temp.rationalize(n);

	divide(temp);

	return *this;
}

// Compound Arithmetic (Object)

template <typename Data>
Rational<Data> & Rational<Data>::operator%=(const Rational & o)
{
	Rational thisCopy(*this);
	Rational objectCopy(o);

	thisCopy.commonize(objectCopy);

	(*this)(thisCopy._numer % objectCopy._numer, thisCopy._denom);

    return *this;
}

// Arithmetic Constant (Unary Opposite)

template <typename Data>
Rational<Data> Rational<Data>::operator-() const
{
	Rational temp(*this);

	temp._numer *= -1;

	return temp;
}

// Arithmetic Constant (Number)

template <typename Data>
template <typename Numeric_Type>
Rational<Data> Rational<Data>::operator+(const Numeric_Type & n) const
{
	Rational temp(*this);

	temp += n;

	return temp;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> Rational<Data>::operator-(const Numeric_Type & n) const
{
	Rational temp(*this);

	temp -= n;

	return temp;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> Rational<Data>::operator*(const Numeric_Type & n) const
{
	Rational temp(*this);

	temp *= n;

	return temp;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> Rational<Data>::operator/(const Numeric_Type & n) const
{
	Rational temp(*this);

	temp /= n;

	return temp;
}

template <typename Data>
Rational<Data>
Rational<Data>::operator%(const Rational & o) const
{
	Rational temp(*this);

	temp %= o;

	return temp;
}

// Arithmetic Constant (Number & Object)

template <typename Numeric_Type>
Rational<Numeric_Type> operator+(int n, const Rational<Numeric_Type> & o)
{
	Rational<Numeric_Type> numberRatio;

	numberRatio  = rationalize(n);
	numberRatio += o;

	return numberRatio;
}

template <typename Numeric_Type>
Rational<Numeric_Type> operator-(int n, const Rational<Numeric_Type> & o)
{
	Rational<Numeric_Type> numberRatio;

	numberRatio  = rationalize(n);
	numberRatio -= o;

	return numberRatio;
}

template <typename Numeric_Type>
Rational<Numeric_Type> operator*(int n, const Rational<Numeric_Type> & o)
{
	Rational<Numeric_Type> numberRatio;

	numberRatio  = rationalize(n);
	numberRatio *= o;

	return numberRatio;
}

template <typename Numeric_Type>
Rational<Numeric_Type> operator/(int n, const Rational<Numeric_Type> & o)
{
	Rational<Numeric_Type> numberRatio;

	numberRatio  = rationalize(n);
	numberRatio /= o;

	return numberRatio;
}


/********************************
 * --- Relational Operators --- *
 ********************************/

// Standard (Object & Number)

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator<(const Numeric_Type n) const
{
	Rational thisCopy(*this);
	Rational numberRatio;

	numberRatio.rationalize(n);
	thisCopy.commonize(numberRatio);

	return thisCopy.numerator() < numberRatio.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator>(const Numeric_Type n) const
{
	Rational thisCopy(*this);
	Rational numberRatio;

	numberRatio.rationalize(n);
	thisCopy.commonize(numberRatio);

	return thisCopy.numerator() > numberRatio.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator<=(const Numeric_Type n) const
{
	Rational thisCopy(*this);
	Rational numberRatio;

	numberRatio.rationalize(n);
	thisCopy.commonize(numberRatio);

	return thisCopy.numerator() <= numberRatio.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator>=(const Numeric_Type n) const
{
	Rational thisCopy(*this);
	Rational numberRatio;

	numberRatio.rationalize(n);
	thisCopy.commonize(numberRatio);

	return thisCopy.numerator() >= numberRatio.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator==(const Numeric_Type n) const
{
	Rational thisCopy(*this);
	Rational numberRatio;

	numberRatio.rationalize(n);
	thisCopy.commonize(numberRatio);

	return thisCopy.numerator() == numberRatio.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator!=(const Numeric_Type n) const
{
	Rational thisCopy(*this);
	Rational numberRatio;

	numberRatio.rationalize(n);
	thisCopy.commonize(numberRatio);

	return thisCopy.numerator() != numberRatio.numerator();
}


// Reverse (Number & Object)

template <typename Type_1, typename Type_2>
bool operator<  (const Type_1 & n, const Rational<Type_2> & o)
{
	Rational<Type_2> objectCopy(o);
	Rational<Type_2> numberRatio;

	numberRatio.rationalize(n);
	objectCopy.commonize(numberRatio);

	return numberRatio.numerator() < objectCopy.numerator();
}

template <typename Type_1, typename Type_2>
bool operator>  (const Type_1 & n, const Rational<Type_2> & o)
{
	Rational<Type_2> objectCopy(o);
	Rational<Type_2> numberRatio;

	numberRatio.rationalize(n);
	objectCopy.commonize(numberRatio);

	return numberRatio.numerator() > objectCopy.numerator();
}

template <typename Type_1, typename Type_2>
bool operator<= (const Type_1 & n, const Rational<Type_2> & o)
{
	Rational<Type_2> objectCopy(o);
	Rational<Type_2> numberRatio;

	numberRatio.rationalize(n);
	objectCopy.commonize(numberRatio);

	return numberRatio.numerator() <= objectCopy.numerator();
}

template <typename Type_1, typename Type_2>
bool operator>= (const Type_1 & n, const Rational<Type_2> & o)
{
	Rational<Type_2> objectCopy(o);
	Rational<Type_2> numberRatio;

	numberRatio.rationalize(n);
	objectCopy.commonize(numberRatio);

	return numberRatio.numerator() >= objectCopy.numerator();
}

template <typename Type_1, typename Type_2>
bool operator== (const Type_1 & n, const Rational<Type_2> & o)
{
	Rational<Type_2> objectCopy(o);
	Rational<Type_2> numberRatio;

	numberRatio.rationalize(n);
	objectCopy.commonize(numberRatio);

	return numberRatio.numerator() == objectCopy.numerator();
}

template <typename Type_1, typename Type_2>
bool operator!= (const Type_1 & n, const Rational<Type_2> & o)
{
	Rational<Type_2> objectCopy(o);
	Rational<Type_2> numberRatio;

	numberRatio.rationalize(n);
	objectCopy.commonize(numberRatio);

	return numberRatio.numerator() != objectCopy.numerator();
}

#endif /* RATIONAL_H_ */
