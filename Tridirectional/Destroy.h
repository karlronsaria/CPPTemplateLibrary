/*
 * Destroy.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_DESTROY_H_
#define TERNARYNODE_DESTROY_H_

#include "../Exception/NoDataException.h"

namespace ternarynode
{
	template <class First_Node_Type,
	          class Secnd_Node_Type,
	          class Third_Node_Type>

	void Destroy

		(First_Node_Type & node,
	     Secnd_Node_Type & (Third_Node_Type::*link)())
	{
		try
		{
			if(node.is_null()) throw NoData(__FUNCTION__);
			else (node->*link)().deallocate();
		}
		catch(Exception & e)
		{
			puts(e.message());
		}
	}
}

#endif /* TERNARYNODE_DESTROY_H_ */
