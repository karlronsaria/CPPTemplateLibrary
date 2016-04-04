/*
 * Collection.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <stddef.h>

class Collection
{
	public:

		virtual ~Collection() {}
		virtual bool   empty () const = 0;
		virtual size_t size  () const = 0;
		virtual void   clear ()       = 0;
};

#endif /* COLLECTION_H_ */
