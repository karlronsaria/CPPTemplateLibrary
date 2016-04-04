/*
 * Pop.h
 *
 *  Created on: Apr 13, 2015
 *      Author: adaniels4
 */

#ifndef BINARYNODE_POP_H_
#define BINARYNODE_POP_H_

#include "../Exception/NoDataException.h"

namespace binarynode
{
	template <typename Content_Type,
	          class    First_Node_Type,
	          class    Secnd_Node_Type,
	          class    Third_Node_Type,
	          class    Forth_Node_Type>
	Content_Type Pop
		(First_Node_Type & firstNode,
		 Secnd_Node_Type & secndNode,
		 Third_Node_Type & (BinaryNode<Content_Type>::*link)(),
		 Forth_Node_Type & (BinaryNode<Content_Type>::*other_link)())
	{
		try
		{
			if(firstNode.is_null()) throw NoData(__FUNCTION__);
			else
			{
				scoped_ptr< BinaryNode<Content_Type> > temp;

				temp.assign(firstNode);
				firstNode.assign((temp->*link)());
				(temp->*link)().avert();
				(firstNode->*other_link)().avert();

				if(firstNode.is_null()) secndNode.avert();

				return temp->content();
			}
		}
		catch(Exception & error)
		{
			puts(error.message());

			return Content_Type();
		}
	}

	template <class Content_Type>
	Content_Type PopFront
		(         scoped_ptr< BinaryNode<Content_Type> >          & head,
		 typename scoped_ptr< BinaryNode<Content_Type> >::locator & tail)
	{
		return Pop(head, tail, &BinaryNode<Content_Type>::inconstant_next,
				               &BinaryNode<Content_Type>::inconstant_prev);
	}

	template <class Content_Type>
	Content_Type PopBack
		(         scoped_ptr< BinaryNode<Content_Type> >          & head,
		 typename scoped_ptr< BinaryNode<Content_Type> >::locator & tail)
	{
		return Pop(tail, head, &BinaryNode<Content_Type>::inconstant_prev,
				               &BinaryNode<Content_Type>::inconstant_next);
	}

//	template <class Content_Type>
//	Content_Type PopFront
//		(         scoped_ptr< BinaryNode<Content_Type> >          & head,
//		 typename scoped_ptr< BinaryNode<Content_Type> >::locator & tail)
//	{
//		try
//		{
//			if(head.is_null()) throw NoData();
//			else
//			{
//				scoped_ptr< BinaryNode<Content_Type> > temp;
//
//				temp.assign(head);
//				head.assign(temp->next());
//				temp->next().avert();
//				head->prev().avert();
//
//				if(head.is_null()) tail.avert();
//
//				return temp->content();
//			}
//		}
//		catch(NodeException & error)
//		{
//			puts(error.message());
//
//			return Content_Type();
//		}
//	}

//	template <class Content_Type>
//	Content_Type PopBack
//		(         scoped_ptr< BinaryNode<Content_Type> >          & head,
//		 typename scoped_ptr< BinaryNode<Content_Type> >::locator & tail)
//	{
//		try
//		{
//			if(tail.is_null()) throw NoData();
//			else
//			{
//				scoped_ptr< BinaryNode<Content_Type> > temp;
//
//				temp.assign(tail);
//				tail.assign(temp->prev());
//				temp->prev().avert();
//				tail->next().avert();
//
//				if(tail.is_null()) head.avert();
//
//				return temp->content();
//			}
//		}
//		catch(NodeException & error)
//		{
//			puts(error.message());
//
//			return Content_Type();
//		}
//	}
}

#endif /* BINARYNODE_POP_H_ */
