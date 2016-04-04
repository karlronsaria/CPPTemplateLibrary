/*
 * End.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef UNARYNODE_END_H_
#define UNARYNODE_END_H_

#include "../UnaryNode.h"
#include "../Exception/NoDataException.h"
#include "../Node/End.h"

namespace unarynode
{
	template <class Content_Type>
	void GetEnd
		(const    scoped_ptr< UnaryNode<Content_Type> >          & list,
		 typename scoped_ptr< UnaryNode<Content_Type> >::locator & end)
	{
		try
		{
			if(list.is_null())
			{
				throw NoData(__FUNCTION__);
			}
			else
			{
				node::GetEnd
						  < scoped_ptr< UnaryNode<Content_Type> >,
				   typename scoped_ptr< UnaryNode<Content_Type> >::locator,
				            scoped_ptr< UnaryNode<Content_Type> >,
				                        UnaryNode<Content_Type> >

				(list, end, &UnaryNode<Content_Type>::next);
			}
		}
		catch(Exception & error)
		{
			puts(error.message());
		}
	}

	template <class Content_Type>

	typename scoped_ptr< UnaryNode<Content_Type> >::locator

	End(scoped_ptr< UnaryNode<Content_Type> > & list)
	{
		typename scoped_ptr< UnaryNode<Content_Type> >::locator end;

		GetEnd(list, end);

		return end;
	}

	template <class Content_Type>

	typename scoped_ptr< UnaryNode<Content_Type> >::locator

	NextToEnd(scoped_ptr< UnaryNode<Content_Type> > & list)
	{
		typename scoped_ptr< UnaryNode<Content_Type> >::locator
		cursor = list;

		while(!cursor->next()->next().is_null())
		{
			cursor = cursor->next();
		}

		return cursor;
	}
}

#endif /* UNARYNODE_END_H_ */
