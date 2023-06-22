/*
 * arrayfunction.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Drew
 */

#ifndef ARRAYFUNCTION_H_
#define ARRAYFUNCTION_H_

namespace arrayfunction
{
	template <typename Type>
	void copy_values(Type * to,     Type * from,
			         size_t toSize, size_t fromSize)
	{
		Type * toIt   = to;
		Type * fromIt = from;

		for(size_t index = 0; index < toSize && index < fromSize; index++)
		{
			*toIt = *fromIt;

			 toIt++;
			 fromIt++;
		}
	}
}

#endif /* ARRAYFUNCTION_H_ */
