/*
 * PreOrder.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef TRAVERSE_PREORDER_H_
#define TRAVERSE_PREORDER_H_

template <class Tree_Iterator_Type>
void TraversePreOrder(Tree_Iterator_Type treeIt,
		              void (*Function)(Tree_Iterator_Type &))
{
	if(treeIt.any())
	{
		Function(treeIt);

		TraversePreOrder(treeIt.left(),  Function);
		TraversePreOrder(treeIt.right(), Function);
	}
}

#endif /* TRAVERSE_PREORDER_H_ */
