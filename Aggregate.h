/*
 * Aggregate.h
 *
 *  Created on: Sep 23, 2014
 *      Author: adaniels4
 */

#ifndef AGGREGATE_H_
#define AGGREGATE_H_

#include <stddef.h>

template <typename Type>
class Aggregate
{
	public:

		virtual ~Aggregate() {}

	    virtual size_t size() const = 0;

		virtual const Type & operator[](size_t index) const = 0;

		virtual       Type & operator[](size_t index)       = 0;
};

#ifndef foreach
#define foreach(list, index) \
	    for(index = 0; index < (list).size(); index++)
#endif

#ifndef foreach_in
#define foreach_in(list, index, size) \
		for(index = 0; index < size; index++)
#endif

#endif /* AGGREGATE_H_ */
