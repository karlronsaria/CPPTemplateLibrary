/*
 * InOrder.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef TRAVERSE_INORDER_H_
#define TRAVERSE_INORDER_H_

template <class Tree_Iterator_Type>
void TraverseInOrder(Tree_Iterator_Type treeIt,
		             void (*Function)(Tree_Iterator_Type &))
{
	if(treeIt.any())
	{
		TraverseInOrder(treeIt.left(),  Function);

		Function(treeIt);

		TraverseInOrder(treeIt.right(), Function);
	}
}

#endif /* TRAVERSE_INORDER_H_ */
