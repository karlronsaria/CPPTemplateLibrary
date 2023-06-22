/*
 * Height.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_INSTANCE_HEIGHT_H_
#define TERNARYNODE_INSTANCE_HEIGHT_H_

#include "../Height.h"
#include "../../TernaryNode.h"

namespace ternarynode
{
	template <class Content_Type>
	void GetHeight(const scoped_ptr< TernaryNode<Content_Type> > & node,
			       height_t depth, height_t & height)
	{
		GetHeight(node, depth, height,
				  &Dereference< scoped_ptr< TernaryNode<Content_Type> >,
				                            TernaryNode<Content_Type> >);
	}

	template <class Content_Type>
	height_t Height(const scoped_ptr< TernaryNode<Content_Type> > & node)
	{
		height_t height = 0;

		GetHeight(node, 0, height);

		return height;
	}

	// ---

	template <class Content_Type>
	void GetDepth(const scoped_ptr< TernaryNode<Content_Type> > & node,
			      height_t depth)
	{
		GetDepth(node, depth,
				 &Dereference< scoped_ptr< TernaryNode<Content_Type> >,
				                           TernaryNode<Content_Type> >);
	}

	template <class Content_Type>
	height_t Depth(const scoped_ptr< TernaryNode<Content_Type> > & node)
	{
		height_t depth = 0;

		GetDepth(node, depth);

		return depth;
	}
}

#endif /* TERNARYNODE_INSTANCE_HEIGHT_H_ */
