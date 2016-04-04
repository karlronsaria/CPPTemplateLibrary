/*
 * Connect.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef CONNECT_H_
#define CONNECT_H_

#include "../UnaryNode.h"
#include "../Exception/NoDataException.h"

namespace unarynode
{
	template <class First_Node_Type, class Secnd_Node_Type>
	bool Connect(First_Node_Type & first, Secnd_Node_Type & secnd)
	{
		try
		{
			if(first.is_null()) throw NoData(__FUNCTION__);
			else
			{
				first->next().assign(secnd);
				return true;
			}
		}
		catch(Exception & error)
		{
			puts(error.message());
			return false;
		}
	}
}

#endif /* CONNECT_H_ */
