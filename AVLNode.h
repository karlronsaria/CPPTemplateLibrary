/*
 * AVLNode.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef AVLNODE_H_
#define AVLNODE_H_

#include "scoped_ptr.h"
#include "Container.h"

#ifndef height_t
typedef unsigned char height_t;
#endif

/*************************************************************************
 * AVLNode                                                               *
 * _____________________________________________________________________ *
 *                                                                       *
 * A binary tree node with two dynamic links, one passive 'parent' link, *
 * and a small integer value 'height' for tracking the height of a node  *
 * in a tree.                                                            *
 * Parameterizes container content.                                      *
 *                                                                       *
 * [!] Scoped Pointers: Destroying one node will destroy all of          *
 *                      the nodes that the dynamic links point to.       *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type>
class AVLNode: public Container<Content_Type>
{
	private:

		height_t _height;

				 scoped_ptr<AVLNode>           _left;
				 scoped_ptr<AVLNode>           _right;
		typename scoped_ptr<AVLNode>::locator  _parent;

	public:

		AVLNode(): _height(1) {}
		AVLNode(const Content_Type & content):
			Container<Content_Type>(content), _height(1) {}
	   ~AVLNode() {}

		height_t height () const                  {  return  _height; }
		void     height (const height_t & height) { _height = height; }

		const scoped_ptr<AVLNode> & left  () const { return  _left;  }
			  scoped_ptr<AVLNode> & left  ()       { return  _left;  }
		const scoped_ptr<AVLNode> & right () const { return  _right; }
			  scoped_ptr<AVLNode> & right ()       { return  _right; }

		const typename scoped_ptr<AVLNode>::locator &

				parent() const

				  { return _parent; }

			  typename scoped_ptr<AVLNode>::locator &

				parent()

				  { return _parent; }
};

#endif /* AVLNODE_H_ */
