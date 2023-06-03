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

template <typename Data>
class Rational: private IntegralClass<Data>
{
    public:

        enum RatioForm
        {
            SIMPLIFIED,
            UNSIMPLIFIED
        };

    private:

        Data _numer;
        Data _denom;
        RatioForm _form;

    protected:

        /*******************************
         * --- Protected Functions --- *
         *******************************/

        // Accessors

        template <typename Type>
        bool numericOperation(const Type, Rational &, Rational &) const

        // Mutators

        void set_denominator(const Data &);
        void rationalize(float);
        void commonize(Rational &);

    public:

        /*************************************
         * --- Constructors & Destructor --- *
         *************************************/

        // Standard Constructors

        Rational();
        Rational(const RatioForm &);

        // Value-setting Constructors

        Rational(const Data &);
        Rational(const Data &, const Data &);
        Rational(const Data &, const Data &, const RatioForm &);

        // Destructor

       ~Rational();


        /******************************
         * --- Named Constructors --- *
         ******************************/

        template <typename Numeric_Type>
        friend Rational<Numeric_Type> rational(
            const Numeric_Type &
        );

        template <typename Numeric_Type>
        friend Rational<Numeric_Type> rational(
            const Numeric_Type &,
            const Numeric_Type &
        );

        template <typename Numeric_Type>
        friend Rational<Numeric_Type> reciprocal(
            const Numeric_Type &
        );


        /*********************
         * --- Accessors --- *
         *********************/

        // Standard Accessors

        const RatioForm & form() const;
        const Data & numerator() const;
        const Data & denominator() const;

        // Calculations

        const float & to_float() const;
        const double & to_double() const;
        const long double & to_long_double() const;
        const Rational simplify() const;
        const Rational reciprocal() const;

        // Verifiers

        bool is_whole() const;
        bool is_proper() const;
        bool common_with(const Rational &) const;

        // Arithmetic

        const Rational add(const Rational &) const;
        const Rational subtract(const Rational &) const;
        const Rational multiply(const Rational &) const;
        const Rational divide(const Rational &) const throw(const char *);


        /****************************
         * --- Friend Functions --- *
         ****************************/

        template <typename Numeric_Type>
        friend bool are_common(
            const Rational<Numeric_Type> &,
            const Rational<Numeric_Type> &
        );

        friend Rational<int> rationalize(double value);

        template <typename Numeric_Type>
        friend Rational<Numeric_Type> abs(
            const Rational<Numeric_Type> &
        );

        template <typename Numeric_Type>
        friend float sqrt(
            const Rational<Numeric_Type> &
        );

        template <typename Type_1, typename Type_2>
        friend float pow(
            const Type_2 &,
            const Rational<Type_1> &
        );

        template <typename Type_1, typename Type_2>
        friend float pow(
            const Rational<Type_1> &,
            const Type_2 &
        );

        template <typename Type_1, typename Type_2>
        friend float pow(
            const Rational<Type_1> &,
            const Rational<Type_2> &
        );

        template <typename Numeric_Type>
        friend float cos(
            const Rational<Numeric_Type> &
        );

        template <typename Numeric_Type>
        friend float sin(
            const Rational<Numeric_Type> &
        );

        template <typename Numeric_Type>
        friend float exp(
            const Rational<Numeric_Type> &
        );


        /*****************************************
         * --- Typecast Conversion Operators --- *
         *****************************************/

        // Convert Object to Other Type

        operator int() const;
        operator long();
        operator long long();
        operator float();
        operator double();
        operator long double ();

        operator Rational<int>() const;
        operator Rational<long int>() const;
        operator Rational<long long int> () const;


        /***********************************
         * --- Output Stream Operators --- *
         ***********************************/

        std::ostream & operator<<(
            std::ostream &
        ) const;

        template <typename Numeric_Type>
        friend std::ostream & operator<<(
            std::ostream &,
            const Rational<Numeric_Type> &
        );

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

        const Rational operator-() const;

        // Arithmetic Constant (Number)

        template <typename Numeric_Type>
        const Rational operator+(const Numeric_Type &) const;

        template <typename Numeric_Type>
        const Rational operator-(const Numeric_Type &) const;

        template <typename Numeric_Type>
        const Rational operator*(const Numeric_Type &) const;

        template <typename Numeric_Type>
        const Rational operator/(const Numeric_Type &) const;

        // Arithmetic Constant (Object)

        const Rational operator%(const Rational &) const;

        // Arithmetic Constant (Number & Object)

        template <typename Numeric_Type>
        friend const Rational<Numeric_Type> operator+(
            int number,
            const Rational<Numeric_Type> &
        );

        template <typename Numeric_Type>
        friend const Rational<Numeric_Type> operator-(
            int number,
            const Rational<Numeric_Type> &
        );

        template <typename Numeric_Type>
        friend const Rational<Numeric_Type> operator*(
            int number,
            const Rational<Numeric_Type> &
        );

        template <typename Numeric_Type>
        friend const Rational<Numeric_Type> operator/(
            int number,
            const Rational<Numeric_Type> &
        );


        /********************************
         * --- Relational Operators --- *
         ********************************/

        // Standard (Object & Number)

        template <typename Numeric_Type>
        bool operator<(const Numeric_Type) const;

        template <typename Numeric_Type>
        bool operator>(const Numeric_Type) const;

        template <typename Numeric_Type>
        bool operator<=(const Numeric_Type) const;

        template <typename Numeric_Type>
        bool operator>=(const Numeric_Type) const;

        template <typename Numeric_Type>
        bool operator==(const Numeric_Type) const;

        template <typename Numeric_Type>
        bool operator!=(const Numeric_Type) const;

        // Reverse (Number & Object)

        template <typename Type_1, typename Type_2>
        friend bool operator<(
            const Type_1 &,
            const Rational<Type_2> &
        );

        template <typename Type_1, typename Type_2>
        friend bool operator>(
            const Type_1 &,
            const Rational<Type_2> &
        );

        template <typename Type_1, typename Type_2>
        friend bool operator<=(
            const Type_1 &,
            const Rational<Type_2> &
        );

        template <typename Type_1, typename Type_2>
        friend bool operator>=(
            const Type_1 &,
            const Rational<Type_2> &
        );

        template <typename Type_1, typename Type_2>
        friend bool operator==(
            const Type_1 &,
            const Rational<Type_2> &
        );

        template <typename Type_1, typename Type_2>
        friend bool operator!=(
            const Type_1 &,
            const Rational<Type_2> &
        );
};

typedef Rational<int> rational_int;
typedef Rational<long> rational_long;
typedef Rational<long long> rational_long_long;


/*******************************
 * --- Protected Functions --- *
 *******************************/

// Mutators

template<typename Data>
void Rational<Data>::set_denominator(const Data & d)
{
    if (d == 0)
        return;

    if (d > 0) {
        _denom = d;
        return;
    }

    _numer *= -1;
    _denom = abs(d);
}

template<typename Data>
void Rational<Data>::rationalize(float value)
{
    int count;
    int denomValue;

    count = 0;
    denomValue = (int)pow(10, count);

    while (abs(value - double((int)value)) >
        std::numeric_limits<double>::epsilon()
    ) {
        count++;
        denomValue = (int)pow(10, count);
        value *= 10;
    }

    _numer = (int)(value);
    set_denominator(denomValue);
}

template<typename Data>
void Rational<Data>::commonize(Rational & o)
{
    if (common_with(o))
        return

    *this = Rational(_numer * o._denom, _denom * o._denom, UNSIMPLIFIED);
    o = Rational(_denom * o._numer, _denom * o._denom, UNSIMPLIFIED);
}


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

// Standard Constructors

template<typename Data>
Rational<Data>::Rational():
    _form(UNSIMPLIFIED), _numer(0), _denom(1) {}

template<typename Data>
Rational<Data>::Rational(const Rational & o):
    _numer(o._numer), _denom(o._denom), _form(o._form) {}

template<typename Data>
Rational<Data>::Rational(const Rational<Data>::RatioForm & f):
    _form(f), _numer(0), _denom(1) {}

// Value-setting Constructors

template<typename Data>
Rational<Data>::Rational(const Data & n):
    _numer(n), _denom(1), _form(UNSIMPLIFIED) {}

template<typename Data>
Rational<Data>::Rational(const Data & n, const Data & d):
    _form(UNSIMPLIFIED)
{
    _denom = 1;
    _numer = n;
    set_denominator(d);
}

template<typename Data>
Rational<Data>::Rational(const Data & n, const Data & d,
                         const Rational<Data>::RatioForm & f):
    _form(f), _numer(n), _denom(d)
{
    if (_form == SIMPLIFIED)
        *this = simplify();
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
    return Rational<Numeric_Type>(n, 1);
}

template<typename Numeric_Type>
Rational<Numeric_Type> rational(const Numeric_Type & n,
                                const Numeric_Type & d)
{
    return Rational<Numeric_Type>(n, d);
}

template<typename Numeric_Type>
Rational<Numeric_Type> reciprocal(const Numeric_Type & d)
{
    return Rational<Numeric_Type>(1, d);
}


/*********************
 * --- Accessors --- *
 *********************/

// Standard Accessors

template<typename Data>
const Rational<Data>::RatioForm & Rational<Data>::form() const
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
const float & Rational<Data>::to_float() const
{
    return _numer / (float) _denom;
}

template<typename Data>
const double & Rational<Data>::to_double() const
{
    return _numer / (double) _denom;
}

template<typename Data>
const long double & Rational<Data>::to_long_double() const
{
    return _numer / (long double) _denom;
}

template<typename Data>
const Rational<Data> Rational<Data>::reciprocal() const
{
    int n = _numer;
    int d = _denom;
    Rational temp(1, 1);
    temp.set_denominator(n);
    temp.numerator(d);
    return temp;
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
const Rational<Data> Rational<Data>::add(const Rational & a) const
{
    Data n, d;
    n = _numer * a._denom + _denom * a._numer * alg::sign(_numer);
    d = _denom * a._denom;
    return Rational(n, d)
}

template <typename Data>
const Rational<Data> Rational<Data>::subtract(const Rational & s) const
{
    return add(-s);
}

template <typename Data>
const Rational<Data> Rational<Data>::multiply(const Rational & m) const
{
    Rational temp(*this);
    temp.set_denominator(_numer ? _denom * m._denom : 1);
    temp.numerator(_numer * m._numer);
    return temp;
}

template <typename Data>
const Rational<Data> Rational<Data>::divide(const Rational & d)
    const
    throw(const char *)
{
    if (!d._denom)
        throw "Divide by zero.";

    return multiply(d.reciprocal());
}


// Calculations

template <typename Data>
const Rational<Data> Rational<Data>::simplify() const
{
    Rational temp(*this);
    Data *least;
    Data *greatest;

    if (abs(_numer) > abs(_denom))
    {
        least = &temp._denom;
        greatest = &temp._numer;
    }
    else
    {
        least = &temp._numer;
        greatest = &temp._denom;
    }

    for (int count = *least; count > 1; count--)
    {
        if (*least % count == 0 && *greatest % count == 0)
        {
            *least /= count;
            *greatest /= count;
        }
    }

    temp._numer *= sign(sign(temp._numer) * sign(temp._denom));
    temp._denom = abs(temp._denom);
    return temp;
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

template <typename Numeric_Type>
Rational<Numeric_Type> abs(const Rational<Numeric_Type> & o)
{
    return Rational(
        abs<Numeric_Type>(o._numer),
        abs<Numeric_Type>(o._denom)
    );
}

template <typename Numeric_Type>
float sqrt(const Rational<Numeric_Type> & o)
{
    return sqrt(o.to_float());
}

template <typename Type_1, typename Type_2>
float pow(const Type_2 & b, const Rational<Type_1> & l)
{
    return pow(b, l.to_float());
}

template <typename Type_1, typename Type_2>
float pow(const Rational<Type_1> & b, const Type_2 & l)
{
    return pow(b, l.to_float());
}

template <typename Type_1, typename Type_2>
float pow(const Rational<Type_1> & b, const Rational<Type_2> & l)
{
    return pow(b, l.to_float());
}

template <typename Numeric_Type>
float cos(const Rational<Numeric_Type> & o)
{
    return cos(o.to_float());
}

template <typename Numeric_Type>
float sin(const Rational<Numeric_Type> & o)
{
    return sin(o.to_float());
}

template <typename Numeric_Type>
float exp(const Rational<Numeric_Type> & o)
{
    return exp(o.to_float());
}


/*****************************************
 * --- Typecast Conversion Operators --- *
 *****************************************/

// Convert Object to Other Type

template <typename Data>
Rational<Data>::operator int() const
{
    return int(to_float());
}

template <typename Data>
Rational<Data>::operator long()
{
    return long(to_float());
}

template <typename Data>
Rational<Data>::operator long long()
{
    return (long long)(to_float());
}

template <typename Data>
Rational<Data>::operator float()
{
    return to_float();
}

template <typename Data>
Rational<Data>::operator double()
{
    return to_double();
}

template <typename Data>
Rational<Data>::operator long double()
{
    return to_long_double();
}

template <typename Data>
Rational<Data>::operator Rational<int>() const
{
    return Rational<int>(
        (int)numerator(),
        (int)denominator(),
        type(),
        form()
    );
}

template <typename Data>
Rational<Data>::operator Rational<long int>() const
{
    return Rational<long int>(
        (long int)numerator(),
        (long int)denominator(),
        type(),
        form()
    );
}

template <typename Data>
Rational<Data>::operator Rational<long long int>() const
{
    return Rational<long long int>(
        (long long int)numerator(),
        (long long int)denominator(),
        type(),
        form()
    );
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
std::ostream & operator<<(
        std::ostream & out,
        const Rational<Numeric_Type> & o
) {
    std::ostringstream oss;
    oss << o.numerator();

    if (o.numerator())
        oss << "/" << o.denominator();

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

    if (_form == SIMPLIFIED)
        simplify();

    return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> &
Rational<Data>::operator=(const Rational<Numeric_Type> & o)
{
    _form = o.form;
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
    *this = add(temp);
    return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator-=(const Numeric_Type & n)
{
    Rational<Data> temp(*this);
    temp.rationalize(n);
    *this = subtract(temp);
    return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator*=(const Numeric_Type & n)
{
    Rational<Data> temp(*this);
    temp.rationalize(n);
    *this = multiply(temp);
    return *this;
}

template <typename Data>
template <typename Numeric_Type>
Rational<Data> & Rational<Data>::operator/=(const Numeric_Type & n)
{
    Rational<Data> temp(*this);
    temp.rationalize(n);
    *this = divide(temp);
    return *this;
}

// Compound Arithmetic (Object)

template <typename Data>
Rational<Data> & Rational<Data>::operator%=(const Rational & o)
{
    Rational thisCopy(*this);
    Rational objectCopy(o);
    thisCopy.commonize(objectCopy);
    *this = Rational(thisCopy._numer % objectCopy._numer, thisCopy._denom);
    return *this;
}

// Arithmetic Constant (Unary Opposite)

template <typename Data>
const Rational<Data>
Rational<Data>::operator-() const
{
    Rational temp(*this);
    temp._numer *= -1;
    return temp;
}

// Arithmetic Constant (Number)

template <typename Data>
template <typename Numeric_Type>
const Rational<Data>
Rational<Data>::operator+(const Numeric_Type & n) const
{
    Rational temp(*this);
    temp += n;
    return temp;
}

template <typename Data>
template <typename Numeric_Type>
const Rational<Data>
Rational<Data>::operator-(const Numeric_Type & n) const
{
    Rational temp(*this);
    temp -= n;
    return temp;
}

template <typename Data>
template <typename Numeric_Type>
const Rational<Data>
Rational<Data>::operator*(const Numeric_Type & n) const
{
    Rational temp(*this);
    temp *= n;
    return temp;
}

template <typename Data>
template <typename Numeric_Type>
const Rational<Data>
Rational<Data>::operator/(const Numeric_Type & n) const
{
    Rational temp(*this);
    temp /= n;
    return temp;
}

template <typename Data>
const Rational<Data>
Rational<Data>::operator%(const Rational & o) const
{
    Rational temp(*this);
    temp %= o;
    return temp;
}

// Arithmetic Constant (Number & Object)

template <typename Numeric_Type>
const Rational<Numeric_Type>
operator+(int n, const Rational<Numeric_Type> & o)
{
    Rational<Numeric_Type> numberRatio;
    numberRatio = rationalize(n);
    numberRatio += o;
    return numberRatio;
}

template <typename Numeric_Type>
const Rational<Numeric_Type>
operator-(int n, const Rational<Numeric_Type> & o)
{
    Rational<Numeric_Type> numberRatio;
    numberRatio = rationalize(n);
    numberRatio -= o;
    return numberRatio;
}

template <typename Numeric_Type>
const Rational<Numeric_Type>
operator*(int n, const Rational<Numeric_Type> & o)
{
    Rational<Numeric_Type> numberRatio;
    numberRatio = rationalize(n);
    numberRatio *= o;
    return numberRatio;
}

template <typename Numeric_Type>
const Rational<Numeric_Type>
operator/(int n, const Rational<Numeric_Type> & o)
{
    Rational<Numeric_Type> numberRatio;
    numberRatio = rationalize(n);
    numberRatio /= o;
    return numberRatio;
}


/********************************
 * --- Relational Operators --- *
 ********************************/

// Standard (Object & Number)

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::numericOperation(const Numeric_Type n, Rational & first, Rational & secnd) const
{
    Rational thisCopy(*this);
    Rational numberRatio;
    numberRatio.rationalize(n);
    thisCopy.commonize(numberRatio);
    first = thisCopy;
    secnd = numberRatio;
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator<(const Numeric_Type n) const
{
    Rational a, b;
    numericOperation(n, a, b);
    return a.numerator() < b.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator>(const Numeric_Type n) const
{
    Rational a, b;
    numericOperation(n, a, b);
    return a.numerator() > b.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator<=(const Numeric_Type n) const
{
    return !(*this > n);
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator>=(const Numeric_Type n) const
{
    return !(*this < n);
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator==(const Numeric_Type n) const
{
    Rational a, b;
    numericOperation(n, a, b);
    return a.numerator() == b.numerator();
}

template <typename Data>
template <typename Numeric_Type>
bool Rational<Data>::operator!=(const Numeric_Type n) const
{
    return !(*this == n);
}


// Reverse (Number & Object)

template <typename Type_1, typename Type_2>
bool operator<(const Type_1 & n, const Rational<Type_2> & o)
{
    return o > n;
}

template <typename Type_1, typename Type_2>
bool operator>(const Type_1 & n, const Rational<Type_2> & o)
{
    return o < n;
}

template <typename Type_1, typename Type_2>
bool operator<= (const Type_1 & n, const Rational<Type_2> & o)
{
    return o >= n;
}

template <typename Type_1, typename Type_2>
bool operator>=(const Type_1 & n, const Rational<Type_2> & o)
{
    return o <= n;
}

template <typename Type_1, typename Type_2>
bool operator==(const Type_1 & n, const Rational<Type_2> & o)
{
    return o == n;
}

template <typename Type_1, typename Type_2>
bool operator!=(const Type_1 & n, const Rational<Type_2> & o)
{
    return o != n;
}

#endif /* RATIONAL_H_ */
