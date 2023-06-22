/*
 * Print.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef TREETRAVERSAL_PRINT_H_
#define TREETRAVERSAL_PRINT_H_

#include "InOrder.h"
#include "PostOrder.h"
#include "PreOrder.h"


template <class Tree_Type>
void PrintNode(typename Tree_Type::iterator & it)
{
	std::cout << *it << " ";
}


template <class Tree_Type>
void PreOrderPrint(typename Tree_Type::iterator it)
{
	TraversePreOrder(it, &PrintNode<Tree_Type>);
}


template <class Tree_Type>
void InOrderPrint(typename Tree_Type::iterator it)
{
	TraverseInOrder(it, &PrintNode<Tree_Type>);
}


template <class Tree_Type>
void PostOrderPrint(typename Tree_Type::iterator it)
{
	TraversePostOrder(it, &PrintNode<Tree_Type>);
}


#endif /* TREETRAVERSAL_PRINT_H_ */
