/*
 * Height.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_HEIGHT_H_
#define TERNARYNODE_HEIGHT_H_

#include <stddef.h>
#include "../Pointer/ReturnNormally.h"
#include "../Pointer/Dereference.h"

#ifndef height_t
typedef unsigned char height_t;
#endif

namespace ternarynode
{
	template <class First_Node_Type,
			  class Secnd_Node_Type>
	void GetHeight
		(const First_Node_Type & node, height_t depth, height_t & height,
		 const Secnd_Node_Type & (*Modify)(const First_Node_Type &))
	{
		if(node.any())
		{
			if(depth > height) height = depth;

			GetHeight(Modify(node).left(),  depth + 1, height, Modify);
			GetHeight(Modify(node).right(), depth + 1, height, Modify);
		}
	}

	template <class Node_Type>
	void GetHeight(const Node_Type & node,
			       height_t depth, height_t & height)
	{
		GetHeight(node, depth, height, &ReturnNormally<Node_Type>);
	}

	// ---

	template <class First_Node_Type,
			  class Secnd_Node_Type>
	height_t Height
		(const First_Node_Type & node,
		 const Secnd_Node_Type & (*Modify)(const First_Node_Type &))
	{
		height_t height = 0;

		GetHeight(node, 0, height, Modify);

		return height;
	}

	template <class Node_Type>
	height_t Height(const Node_Type & node)
	{
		height_t height = 0;

		GetHeight(node, 0, height);

		return height;
	}

	// ---

	template <class First_Node_Type,
			  class Secnd_Node_Type>
	void GetDepth
		(const First_Node_Type & node, height_t & depth,
		 const Secnd_Node_Type & (*Modify)(const First_Node_Type &))
	{
		First_Node_Type cursor;

		while(cursor.any())
		{
			++depth;
			cursor = Modify(cursor).parent();
		}
	}

	template <class Node_Type>
	void GetDepth(const Node_Type & node, height_t & depth)
	{
		GetDepth(node, depth, &ReturnNormally<Node_Type>);
	}

	// ---

	template <class First_Node_Type,
			  class Secnd_Node_Type>
	height_t Depth
		(const First_Node_Type & node,
		 const Secnd_Node_Type & (*Modify)(const First_Node_Type &))
	{
		height_t depth = 0;

		GetDepth(node, depth, Modify);

		return depth;
	}

	template <class Node_Type>
	height_t Depth(const Node_Type & node)
	{
		height_t depth = 0;

		GetDepth(node, depth);

		return depth;
	}
}

#endif /* TERNARYNODE_HEIGHT_H_ */
