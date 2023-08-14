/*
 * Position.h
 *
 *  Created on: Apr 13, 2015
 *      Author: adaniels4
 */

#ifndef LISTNODE_POSITION_H_
#define LISTNODE_POSITION_H_

namespace listnode
{
	template <typename Content_Type,
			  class    First_Node_Type,
			  class    Secnd_Node_Type,
			  class    Third_Node_Type,
			  template<typename> class Forth_Node_Type>
	void GetPosition
		(const First_Node_Type & list, size_t pos, Secnd_Node_Type & ptr,

		 const Third_Node_Type (Forth_Node_Type<Content_Type>::*link)() const)
	{
		size_t index = 0;

		ptr.assign(list);

		while(index < pos && ptr.any())
		{
			ptr.assign((ptr->*link)());

			++index;
		}
	}

	template <typename Content_Type,
			  class    First_Node_Type,
			  template<typename> class Secnd_Node_Type>
	typename scoped_ptr< Secnd_Node_Type<Content_Type> >::locator Position
		(const typename
		 scoped_ptr< Secnd_Node_Type<Content_Type> >::locator & list,
		 size_t pos,

		 const First_Node_Type (Secnd_Node_Type<Content_Type>::*link)() const)
	{
		typename
		scoped_ptr< Secnd_Node_Type<Content_Type> >::locator ptr = list;

		GetPosition(list, pos, ptr, link);

		return ptr;
	}
}

#endif /* LISTNODE_POSITION_H_ */
