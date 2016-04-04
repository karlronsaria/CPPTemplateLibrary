/*
 * Size.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_SIZE_H_
#define TERNARYNODE_SIZE_H_

#include <stddef.h>
#include "../Pointer/ReturnNormally.h"
#include "../Pointer/Dereference.h"

namespace ternarynode
{
	template <class First_Node_Type,
	          class Secnd_Node_Type>
	void GetSize
		(const First_Node_Type & node, size_t & size,
		 const Secnd_Node_Type & (*Modify)(const First_Node_Type &))
	{
		if(!node.is_null())
		{
			++size;

			GetSize(Modify(node).left(),  size, Modify);
			GetSize(Modify(node).right(), size, Modify);
		}
	}

	template <class Node_Type>
	void GetSize(const Node_Type & node, size_t & size)
	{
		GetSize(node, size, &ReturnNormally<Node_Type>);
	}

	template <class First_Node_Type,
		      class Secnd_Node_Type>
	size_t Size(const First_Node_Type & node,
		        const Secnd_Node_Type & (*Modify)(const First_Node_Type &))
	{
		size_t size = 0;

		GetSize(node, size, Modify);

		return size;
	}

	template <class First_Node_Type>
	size_t Size(const First_Node_Type & node)
	{
		size_t size = 0;

		GetSize(node, size);

		return size;
	}
}

#endif /* TERNARYNODE_SIZE_H_ */
