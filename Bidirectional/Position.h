/*
 * Position.h
 *
 *  Created on: Apr 13, 2015
 *      Author: adaniels4
 */

#ifndef BINARYNODE_POSITION_H_
#define BINARYNODE_POSITION_H_

#include "..\ListNode\Position.h"

namespace binarynode
{
	template <typename C>

		void GetPositionForward

				(const typename scoped_ptr< BinaryNode<C> >::locator &,
				 size_t,

				 typename scoped_ptr< BinaryNode<C> >::locator &);



	template <typename C>

		typename scoped_ptr< BinaryNode<C> >::locator

			ForwardPosition

				(const typename scoped_ptr< BinaryNode<C> >::locator &,
				 size_t);


	template <typename C>

		void GetPositionBackward

				(const typename scoped_ptr< BinaryNode<C> >::locator &,
				 size_t,

				 typename scoped_ptr< BinaryNode<C> >::locator &);


	template <typename C>

		typename scoped_ptr< BinaryNode<C> >::locator

			BackwardPosition

				(const typename scoped_ptr< BinaryNode<C> >::locator &,
				 size_t);

}

template <typename Content_Type>

void

binarynode::GetPositionForward

	(const typename
	 scoped_ptr< BinaryNode<Content_Type> >::locator & list,

	 size_t pos,

	 typename
	 scoped_ptr< BinaryNode<Content_Type> >::locator & ptr)

{
	listnode::GetPosition(list, pos, ptr,
			              &BinaryNode<Content_Type>::next);
}

template <typename Content_Type>

typename scoped_ptr< BinaryNode<Content_Type> >::locator

binarynode::ForwardPosition

	(const typename
	 scoped_ptr< BinaryNode<Content_Type> >::locator & list,

	 size_t pos)

{
	return listnode::Position(list, pos,
			                  &BinaryNode<Content_Type>::next);
}

template <typename Content_Type>

void

binarynode::GetPositionBackward

	(const typename
	 scoped_ptr< BinaryNode<Content_Type> >::locator & list,

	 size_t pos,

	 typename
	 scoped_ptr< BinaryNode<Content_Type> >::locator & ptr)

{
	listnode::GetPosition(list, pos, ptr,
			              &BinaryNode<Content_Type>::prev);
}

template <typename Content_Type>

typename scoped_ptr< BinaryNode<Content_Type> >::locator

binarynode::BackwardPosition

	(const typename
	 scoped_ptr< BinaryNode<Content_Type> >::locator & list,

	 size_t pos)

{
	return listnode::Position(list, pos,
			                  &BinaryNode<Content_Type>::prev);
}

#endif /* BINARYNODE_POSITION_H_ */
