/*
 * TernaryNode.h
 *
 *  Created on: Apr 14, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_H_
#define TERNARYNODE_H_

#include "scoped_ptr.h"
#include "Container.h"

/*************************************************************************
 * TernaryNode                                                           *
 * _____________________________________________________________________ *
 *                                                                       *
 * A binary tree node with two dynamic links                             *
 * and one passive 'parent' link.                                        *
 * Parameterizes container content.                                      *
 *                                                                       *
 * [!] Scoped Pointers: Destroying one node will destroy all of          *
 *                      the nodes that the dynamic links point to.       *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type>
class TernaryNode: public Container<Content_Type>
{
	private:

				 scoped_ptr<TernaryNode>           _left;
				 scoped_ptr<TernaryNode>           _right;
		typename scoped_ptr<TernaryNode>::locator  _parent;

	public:

		TernaryNode() {}
		TernaryNode(const Content_Type & content):
			Container<Content_Type>(content) {}
	   ~TernaryNode() {}

		const scoped_ptr<TernaryNode> & left  () const { return _left;  }
			  scoped_ptr<TernaryNode> & left  ()       { return _left;  }
		const scoped_ptr<TernaryNode> & right () const { return _right; }
			  scoped_ptr<TernaryNode> & right ()       { return _right; }

		const typename scoped_ptr<TernaryNode>::locator &

				parent() const

				  { return _parent; }

			  typename scoped_ptr<TernaryNode>::locator &

				parent()

				  { return _parent; }
};



#endif /* TERNARYNODE_H_ */
