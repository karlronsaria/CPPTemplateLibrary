/*
 * Print.h
 *
 *  Created on: Apr 13, 2015
 *      Author: adaniels4
 */

#ifndef LISTNODE_PRINT_H_
#define LISTNODE_PRINT_H_

#include <iostream>
#include "../scoped_ptr.h"
#include "../Exception/NoDataException.h"

namespace listnode
{
	template <class First_Node_Type,
			  class Secnd_Node_Type,
			  class Third_Node_Type>

	void Print(const First_Node_Type & list,
			   const Secnd_Node_Type & (Third_Node_Type::*link)() const)

	{
		try
		{
			if(!list.any()) throw NoData(__FUNCTION__);
			else
			{
			   typename scoped_ptr<Third_Node_Type>::locator cursor = list;

			   while(cursor.any())
			   {
			      std::cout << cursor->content() << " ";
			      cursor = (cursor->*link)();
			   }
			}
		}
		catch(Exception & error)
		{
			puts(error.message());
		}
	}

	template <class First_Node_Type>

	void Print(const scoped_ptr<First_Node_Type> & head)

	{
		Print(head, &First_Node_Type::next);
	}

	template <class First_Node_Type>

	void PrintReversed

		(const typename
		 scoped_ptr<First_Node_Type>::locator & tail)

	{
		Print(tail, &First_Node_Type::prev);
	}
}

#endif /* LISTNODE_PRINT_H_ */
