/*
 * Connect.h
 *
 *  Created on: Apr 14, 2015
 *      Author: adaniels4
 */

#ifndef NODE_CONNECT_H_
#define NODE_CONNECT_H_

#include "../Exception/CircularNodeException.h"
#include "../Exception/NoDataException.h"

namespace node
{
	template <class First_Node_Type,
	          class Secnd_Node_Type,
	          class Third_Node_Type,
	          class Forth_Node_Type,
	          class Fifth_Node_Type>

	bool Connect

		(First_Node_Type & first,
		 Secnd_Node_Type & secnd,
		 Third_Node_Type & (Fifth_Node_Type::*link)(),
		 Forth_Node_Type & (Fifth_Node_Type::*other_link)())
	{
		try
		{
			if(!first.any())
			{
				if(!secnd.any())   throw NoData(__FUNCTION__);
				else                  (secnd->*other_link)().avert();
			}
			else if(!secnd.any())  (first->*link)().avert();
			else if(first == secnd)   throw CircularNode(__FUNCTION__);
			else
			{
				(first->*link      )().assign(secnd);
				(secnd->*other_link)().assign(first);
			}

			return true;
		}
		catch(Exception & error)
		{
			puts(error.message());
			return false;
		}
	}

	template <class First_Node_Type,
	          class Secnd_Node_Type,
	          class Third_Node_Type>

	bool Connect

		(First_Node_Type & first,
		 First_Node_Type & secnd,
		 First_Node_Type & (Third_Node_Type::*link)(),
		 Secnd_Node_Type & (Third_Node_Type::*other_link)())
	{
		return Connect< First_Node_Type,
						First_Node_Type,
						First_Node_Type,
						Secnd_Node_Type,
						Third_Node_Type >(first, secnd, link, other_link);
	}

	template <class First_Node_Type,
	          class Secnd_Node_Type>

	bool Connect

		(First_Node_Type & first,
		 First_Node_Type & secnd,

		 First_Node_Type & (Secnd_Node_Type::*link)(),

		 typename First_Node_Type::locator &
		 	 	           (Secnd_Node_Type::*other_link)())
	{
		return Connect< First_Node_Type,
						First_Node_Type,
						First_Node_Type,
						typename First_Node_Type::locator,
						Secnd_Node_Type >(first, secnd, link, other_link);
	}
}

#endif /* NODE_CONNECT_H_ */
