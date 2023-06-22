/*
 * Orphan.h
 *
 *  Created on: Apr 17, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_ORPHAN_H_
#define TERNARYNODE_ORPHAN_H_

namespace ternarynode
{
	template <class Node_Type>
	void Orphan(Node_Type & node)
	{
		node->left().avert();
		node->right().avert();
	}
}

#endif /* TERNARYNODE_ORPHAN_H_ */
