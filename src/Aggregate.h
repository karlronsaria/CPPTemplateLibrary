/*
 * Aggregate.h
 *
 *  Created on: Sep 23, 2014
 *      Author: adaniels4
 */

#ifndef AGGREGATE_H_
#define AGGREGATE_H_

#include <stddef.h>

template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual size_t size() const = 0;
    virtual const T & operator[](int index) const = 0;
    virtual T & operator[](int index) = 0;
};

#endif /* AGGREGATE_H_ */
