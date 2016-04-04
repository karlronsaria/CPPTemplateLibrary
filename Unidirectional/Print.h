/*
 * Print.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef UNARYNODE_PRINT_H_
#define UNARYNODE_PRINT_H_

#include "../ListNode/Print.h"

namespace unarynode
{
//	template <class Content_Type>
//	void Print(scoped_ptr< UnaryNode<Content_Type> > & list)
//	{
//		try
//		{
//			if(list.is_null())
//			{
//				throw NoData();
//			}
//			else
//			{
//				typename scoped_ptr< UnaryNode<Content_Type> >::locator
//				cursor = list;
//
//				while(!cursor.is_null())
//				{
//					std::cout << cursor->content() << " ";
//					cursor = cursor->next();
//				}
//			}
//		}
//		catch(NodeException & error)
//		{
//			puts(error.message());
//		}
//	}

//	template <class Content_Type>
//	void Print(scoped_ptr< UnaryNode<Content_Type> > & list)
//	{
//		listnode::Print(list, &UnaryNode<Content_Type>::next);
//	}
}

#endif /* UNARYNODE_PRINT_H_ */
