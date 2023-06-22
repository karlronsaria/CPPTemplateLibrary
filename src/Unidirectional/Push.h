/*
 * Push.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef PUSH_H_
#define PUSH_H_

#include "Connect.h"
#include "End.h"

namespace unarynode
{
	template <class Content_Type>
	void PushFront(scoped_ptr< UnaryNode<Content_Type> > & list,
				   scoped_ptr< UnaryNode<Content_Type> > & node)
	{
		unarynode::Connect(node, list);
		list.assign(node);
		node.avert();
	}

	template <class Content_Type>
	void PushBack(scoped_ptr< UnaryNode<Content_Type> > & list,
				  scoped_ptr< UnaryNode<Content_Type> > & node)
	{
		if(list.is_null())
		{
			PushFront(list, node);
		}
		else
		{
			typename scoped_ptr< UnaryNode<Content_Type> >::locator
			end = unarynode::End(list);

			unarynode::Connect(end, node);
			node.avert();
		}
	}
}

#endif /* PUSH_H_ */
