/*
 * Pop.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef POP_H_
#define POP_H_

#include "End.h"
#include "../Exception/NoDataException.h"

namespace unarynode
{
	template <class Content_Type>
	Content_Type PopFront(scoped_ptr< UnaryNode<Content_Type> > & list)
	{
		try
		{
			if(list.is_null()) throw NoData(__FUNCTION__);
			else
			{
				scoped_ptr< UnaryNode<Content_Type> > temp;

				swap(list, temp);
				list.assign(temp->next());
				temp->next().avert();

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
	Content_Type PopBack(scoped_ptr< UnaryNode<Content_Type> > & list)
	{
		try
		{
			if(list.is_null())
			{
				throw NoData(__FUNCTION__);
			}
			else
			{
				if(list->next().is_null())
				{
					return PopFront(list);
				}
				else
				{
					Content_Type content;

					typename scoped_ptr< UnaryNode<Content_Type> >::locator
					temp = unarynode::NextToEnd(list);

					content = temp->next()->content();

					temp->next().deallocate();

					return content;
				}
			}
		}
		catch(Exception & error)
		{
			puts(error.message());

			return Content_Type();
		}
	}
}

#endif /* POP_H_ */
