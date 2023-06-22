/*
 * PostOrder.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef TRAVERSE_POSTORDER_H_
#define TRAVERSE_POSTORDER_H_

template <class Tree_Iterator_Type>
void TraversePostOrder(Tree_Iterator_Type treeIt,
		               void (*Function)(Tree_Iterator_Type &))
{
	if(!treeIt.is_null())
	{
		TraversePostOrder(treeIt.left(),  Function);
		TraversePostOrder(treeIt.right(), Function);

		Function(treeIt);
	}
}

#endif /* TRAVERSE_POSTORDER_H_ */
