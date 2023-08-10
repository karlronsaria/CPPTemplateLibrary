/*
 * Modular.h
 *
 *  Created on: Jul 17, 2014
 *      Author: Drew
 */

#ifndef MODULAR_H_
#define MODULAR_H_

#include <sstream>
#include "algebra.h"
#include "Specialize/ExpandedNumericClass.h"

template <typename Data>
class Modular: private ExpandedIntegralClass<Data> {
private:
    Data _value;
    Data _terminal;
    Data _modulus;
protected:
    Modular& value(Data number) {
        _value = cycle(number);
        return *this;
    }

    Modular& add(Data number) {
        _value = cycle(_value + number);
        return *this;
    }
public:
    virtual ~Modular() = default;

    Modular(const Data& terminal, const Data& modulus):
        _terminal(terminal),
        _modulus(modulus),
        _value(terminal) {}

    Modular(const Data& modulus):
        _terminal((Data)0),
        _modulus(modulus),
        _value((Data)0) {}

    Modular(const Modular&) = default;
    Modular& operator=(const Modular&) = default;
    Modular& operator=(const Data& d) { return value(d); }

    const Data& terminal() const { return _terminal; }
    const Data& modulus() const { return _modulus; }
    const Data& value() const { return _value; }
    const Data& period() const { return alg::abs(_modulus - _terminal); }
    const Data& conjugate() const { return _modulus - _value; }
    const Data& cycle(const Data&) const;
    std::string to_string() const;

    Modular& operator+=(const Data& n) { return add(n); }
    Modular& operator-=(const Data& n) { return *this += -n; }
    Modular& operator*=(const Data& n) { return *this = n * _value; }
    Modular& operator/=(const Data& n) { return *this = n / _value; }

    Modular& operator+=(const Modular& o) { return *this += o._value; }
    Modular& operator-=(const Modular& o) { return *this -= o._value; }
    Modular& operator*=(const Modular& o) { return *this *= o._value; }
    Modular& operator/=(const Modular& o) { return *this /= o._value; }

    const Data operator+(const Data&) const;
    const Data operator-(const Data&) const;
    const Data operator*(const Data&) const;
    const Data operator/(const Data&) const;

    const Data operator+(const Modular&) const;
    const Data operator-(const Modular&) const;
    const Data operator*(const Modular&) const;
    const Data operator/(const Modular&) const;

    const Data operator-() const;

    bool operator==(const Modular& o) const { return _value == o._value; }
    bool operator!=(const Modular& o) const { return _value != o._value; }
    bool operator<=(const Modular& o) const { return _value <= o._value; }
    bool operator>=(const Modular& o) const { return _value >= o._value; }
    bool operator<(const Modular& o) const { return _value < o._value; }
    bool operator>(const Modular& o) const { return _value > o._value; }

    bool operator==(const Data& n) const { return _value == n; }
    bool operator!=(const Data& n) const { return _value != n; }
    bool operator<=(const Data& n) const { return _value <= n; }
    bool operator>=(const Data& n) const { return _value >= n; }
    bool operator<(const Data& n) const { return _value < n; }
    bool operator>(const Data& n) const { return _value > n; }
};

template <typename D>
const D& Modular<D>::cycle(const D& number) const {
    auto p = period();

    return number % p
        + ((_value < _terminal) - (_value >= _modulus)) * p;
}

template <typename D>
std::string Modular<D>::to_string() const {
    std::ostringstream oss;
    oss << _value;
    return oss.str();
}

template <typename D>
const D Modular<D>::operator-() const {
    Modular objectCopy(*this);
    objectCopy._value = -objectCopy._value;
    return objectCopy;
}

#define CONST_OP(type, get, def, op) \
template <typename D> \
const D Modular<D>::operator##def(const type& n) const { \
    Modular temp(*this); \
    temp op n##get; \
    return temp._value; \
}

#define CONST_DATA_OP(def, op) \
CONST_OP(D,, def, op)

#define CONST_OBJ_OP(def, op) \
CONST_OP(Modular, ._value, def, op)

CONST_DATA_OP(+, +=)
CONST_DATA_OP(-, -=)
CONST_DATA_OP(*, *=)
CONST_DATA_OP(/, /=)

CONST_OBJ_OP(+, +=)
CONST_OBJ_OP(-, -=)
CONST_OBJ_OP(*, *=)
CONST_OBJ_OP(/, /=)

#undef CONST_DATA_OP
#undef CONST_OBJ_OP

#endif /* MODULAR_H_ */
