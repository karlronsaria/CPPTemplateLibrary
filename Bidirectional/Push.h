/*
 * Push.h
 *
 *  Created on: Apr 13, 2015
 *      Author: adaniels4
 */

#ifndef BINARYNODE_PUSH_H_
#define BINARYNODE_PUSH_H_

#include "Connect.h"

namespace binarynode
{
	template <class First_Node_Type, class Secnd_Node_Type>
	bool ReverseConnect(First_Node_Type & first, Secnd_Node_Type & secnd)
	{
		return Connect(secnd, first);
	}

//	template <typename Content_Type>
//	bool ReverseConnect
//		(typename scoped_ptr< BinaryNode<Content_Type> >::locator & first,
//				  scoped_ptr< BinaryNode<Content_Type> >          & secnd)
//	{
//		return Connect(secnd, first);
//	}

	template <class First_Node_Type,
	          class Secnd_Node_Type,
	          class Third_Node_Type>
	void Push
		(First_Node_Type & first,
		 Secnd_Node_Type & secnd,
		 Third_Node_Type & node,

		 bool (*connect_function)(Third_Node_Type &, First_Node_Type &))
	{
		connect_function(node, first);
		if(first.is_null()) secnd.assign(node);
		first.assign(node);
		node.avert();
	}

	template <typename Content_Type>
	void PushFront
		(         scoped_ptr< BinaryNode<Content_Type> >          & head,
		 typename scoped_ptr< BinaryNode<Content_Type> >::locator & tail,
				  scoped_ptr< BinaryNode<Content_Type> >          & node)
	{
		Push(head, tail, node, &Connect);
	}

	template <typename Content_Type>
	void PushBack
		(         scoped_ptr< BinaryNode<Content_Type> >          & head,
		 typename scoped_ptr< BinaryNode<Content_Type> >::locator & tail,
				  scoped_ptr< BinaryNode<Content_Type> >          & node)
	{
		Push(tail, head, node, &ReverseConnect);
	}
}

#endif /* BINARYNODE_PUSH_H_ */
