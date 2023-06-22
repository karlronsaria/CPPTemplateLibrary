/*
 * Link.h
 *
 *  Created on: Apr 14, 2015
 *      Author: adaniels4
 */

#ifndef NODE_LINK_H_
#define NODE_LINK_H_

#include "../Exception/NoDataException.h"
#include "../Exception/TerminalIteratorException.h"
#include "Connect.h"

namespace node
{
	template <class Object_Type,
			  class First_Node_Type,
			  class Secnd_Node_Type,
			  class Third_Node_Type>

	Object_Type Link

		(const First_Node_Type & node,
		 Secnd_Node_Type & (Third_Node_Type::*link_method)())
	{
		try
		{
			if(node.is_null()) throw NoData(__FUNCTION__);
			else
			{
				return Object_Type((node->*link_method)());
			}
		}
		catch(Exception & e)
		{
			puts(e.message());
			return Object_Type();
		}
	}

	template <class First_Node_Type,
			  class Secnd_Node_Type,
			  class Third_Node_Type>

	void GoToLink

		(First_Node_Type & node,
		 Secnd_Node_Type & (Third_Node_Type::*link_method)())
	{
    	try
    	{
    		if(node.is_null())
    			throw NoData(__FUNCTION__);
    		else if((node->*link_method)().is_null())
    			throw TerminalIterator(__FUNCTION__);
    		else
    		{
    			node.assign((node->*link_method)());
    		}
    	}
    	catch(Exception & e)
    	{
    		puts(e.message());
    	}
	}

	template <class First_Node_Type,
			  class Secnd_Node_Type,
			  class Third_Node_Type,
			  class Forth_Node_Type,
			  class Fifth_Node_Type>

	void PushOntoLink

		(First_Node_Type & first,
		 Secnd_Node_Type & secnd,
		 Third_Node_Type & (Fifth_Node_Type::*link)(),
		 Forth_Node_Type & (Fifth_Node_Type::*other_link)())
	{
		if(!first.is_null() && !(first->*link)().is_null())

			Connect< Secnd_Node_Type,
				     Third_Node_Type,
				     Third_Node_Type,
				     Forth_Node_Type,
				     Fifth_Node_Type >

				(secnd, (first->*link)(), link, other_link);

		Connect(first, secnd, link, other_link);

		secnd.avert();
	}
}


#endif /* NODE_LINK_H_ */
