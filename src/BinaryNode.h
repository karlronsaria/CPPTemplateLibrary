/*
 * BinaryNode.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef BINARYNODE_H_
#define BINARYNODE_H_

#include "scoped_ptr.h"
#include "Container.h"

/*************************************************************************
 * BinaryNode                                                            *
 * _____________________________________________________________________ *
 *                                                                       *
 * A double-linked-list node with a dynamic 'next' link and              *
 * a passive 'prev' link.                                                *
 * Parameterizes container content.                                      *
 *                                                                       *
 * [!] Scoped Pointers: Destroying one node will destroy all of          *
 *                      the nodes that the dynamic links point to.       *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type>
class BinaryNode: public Container<Content_Type>
{
	private:

		scoped_ptr<BinaryNode>                   _next;
		typename scoped_ptr<BinaryNode>::locator _prev;

	public:

		BinaryNode() {}
		BinaryNode(const Content_Type & content):
			Container<Content_Type>(content) {}
	    virtual ~BinaryNode() {}

	    const scoped_ptr<BinaryNode> & next() const      { return _next; }
	          scoped_ptr<BinaryNode> & next()            { return _next; }
              scoped_ptr<BinaryNode> & inconstant_next() { return _next; }

		const typename scoped_ptr<BinaryNode>::locator & prev() const
														{ return _prev; }
		      typename scoped_ptr<BinaryNode>::locator & prev()
		                                                { return _prev; }
		      typename scoped_ptr<BinaryNode>::locator & inconstant_prev()
		                                                { return _prev; }
};

#endif /* BINARYNODE_H_ */
