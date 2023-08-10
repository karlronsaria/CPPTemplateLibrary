/*
 * modular_int.h
 *
 *  Created on: Jul 17, 2014
 *      Author: Drew
 */

#ifndef MODULAR_INT_H_
#define MODULAR_INT_H_

#include "Modular.h"

class modular_int: public Modular<int> {
public:
    virtual ~modular_int() = default;
    using Modular<int>::operator=;

    modular_int(int m):
        Modular<int>::Modular(m) {}

    modular_int(int t, int m):
        Modular<int>::Modular(t, m) {}

    modular_int(const modular_int&) = default;

    modular_int& operator++() { add(1); return *this; }
    modular_int& operator--() { add(-1); return *this; }
    modular_int operator++(int);
    modular_int operator--(int);
};

template <int T, int M>
class mod: public modular_int {
public:
	virtual ~mod() = default;
	using modular_int::operator=;
	mod(): modular_int(T, M) {}
	mod(const mod&) = default;
};

modular_int modular_int::operator++(int) {
    modular_int temp(*this);
    ++*this;
    return temp;
}

modular_int modular_int::operator--(int) {
    modular_int temp = *this;
    --*this;
    return temp;
}

#endif /* MODULAR_INT_H_ */
