/*
 * Position.h
 *
 *  Created on: Apr 10, 2015
 *      Author: adaniels4
 */

#ifndef UNARYNODE_POSITION_H_
#define UNARYNODE_POSITION_H_

#include "..\ListNode\Position.h"

namespace unarynode
{
	template <class Content_Type>
	void GetPosition
		(const typename
		 scoped_ptr< UnaryNode<Content_Type> >::locator & list,
		 size_t pos,
		 typename
		 scoped_ptr< UnaryNode<Content_Type> >::locator & ptr)
	{
		listnode::GetPosition(list, pos, ptr,
				              &UnaryNode<Content_Type>::next);
	}

	template <class Content_Type>
	typename scoped_ptr< UnaryNode<Content_Type> >::locator Position
		(const typename
		 scoped_ptr< UnaryNode<Content_Type> >::locator & list,
		 size_t pos)
	{
		return listnode::Position(list, pos,
				                  &UnaryNode<Content_Type>::next);
	}
}

#endif /* UNARYNODE_POSITION_H_ */
