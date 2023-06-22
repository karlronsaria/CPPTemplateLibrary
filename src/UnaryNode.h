/*
 * UnaryNode.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef UNARYNODE_H_
#define UNARYNODE_H_

#include "scoped_ptr.h"
#include "Container.h"

/*************************************************************************
 * UnaryNode                                                             *
 * _____________________________________________________________________ *
 *                                                                       *
 * A linked-list node with a single dynamic link.                        *
 * Parameterizes container content.                                      *
 *                                                                       *
 * [!] Scoped Pointers: Destroying one node will destroy all of          *
 *                      the nodes that the dynamic links point to.       *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type>
class UnaryNode: public Container<Content_Type>
{
	private:

		scoped_ptr<UnaryNode> _next;

	public:

		UnaryNode() {}
		UnaryNode(const Content_Type & content):
			Container<Content_Type>(content) {}
	   ~UnaryNode() {}

	    const scoped_ptr<UnaryNode> & next() const      { return _next; }
	          scoped_ptr<UnaryNode> & next()            { return _next; }
};

#endif /* UNARYNODE_H_ */
