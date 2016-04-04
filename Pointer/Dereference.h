/*
 * Dereference.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef DEREFERENCE_H_
#define DEREFERENCE_H_

template <class First_Pointer_Type,
		  class Secnd_Pointer_Type>

const Secnd_Pointer_Type & Dereference

	(const First_Pointer_Type & node)
{
	return *node;
}

#endif /* DEREFERENCE_H_ */
