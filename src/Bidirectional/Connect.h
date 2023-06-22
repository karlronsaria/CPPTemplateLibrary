/*
 * Connect.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef BINARYNODE_CONNECT_H_
#define BINARYNODE_CONNECT_H_

#include "../BinaryNode.h"
#include "../Exception/NoDataException.h"

namespace binarynode
{
	template <class First_Node_Type, class Secnd_Node_Type>
	bool Connect(First_Node_Type & first, Secnd_Node_Type & secnd)
	{
		try
		{
			if(first.is_null())
			{
				if(secnd.is_null())
				{
					throw NoData(__FUNCTION__);
				}
				else
				{
					secnd->prev().avert();
				}
			}
			else if(secnd.is_null())
			{
				first->next().avert();
			}
			else
			{
				first->next().assign(secnd);
				secnd->prev() = first;
			}

			return true;
		}
		catch(Exception & error)
		{
			puts(error.message());
			return false;
		}
	}
}

#endif /* BINARYNODE_CONNECT_H_ */
