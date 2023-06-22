/*
 * Size.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_INSTANCE_SIZE_H_
#define TERNARYNODE_INSTANCE_SIZE_H_

#include "../Size.h"
#include "../../TernaryNode.h"

namespace ternarynode
{
	template <class Content_Type>
	void GetSize(const scoped_ptr< TernaryNode<Content_Type> > & node,
			     size_t & size)
	{
		GetSize(node, size,
				&Dereference< scoped_ptr< TernaryNode<Content_Type> >,
				                          TernaryNode<Content_Type> >);
	}

	template <class Content_Type>
	size_t Size(const scoped_ptr< TernaryNode<Content_Type> > & node)
	{
		size_t size = 0;

		GetSize(node, size);

		return size;
	}
}

#endif /* TERNARYNODE_INSTANCE_SIZE_H_ */
