/*
 * Insert.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef AVL_INSERT_H_
#define AVL_INSERT_H_

#include "Balance.h"

namespace avl
{
	template <typename Content_Type,
			  class First_Node_Type,
			  class Secnd_Node_Type,
              bool (*Order_Relation)(const Content_Type &,
  		                             const Content_Type &)>

	void Insert(First_Node_Type & treeNode, First_Node_Type & insertNode,

	   height_t (*RetrieveHeight) (const First_Node_Type &),

	   ROTATE_NODE(RotateNode, First_Node_Type, Secnd_Node_Type),

	   void     (*BalanceNode)

	   	   	   	  (First_Node_Type &,

	   	   	   	   height_t (*RetrieveHeight) (const First_Node_Type &),

	   	   	   	   ROTATE_NODE(RotateNode, First_Node_Type,
	   	   	   			                   Secnd_Node_Type)))
	{
		if(!treeNode.any()) treeNode.assign(insertNode);
		else
		{
			if(Order_Relation(treeNode->content(), insertNode->content()))

				Insert< Content_Type,
				        First_Node_Type,
				        Secnd_Node_Type,
				        Order_Relation >

					(treeNode->right(), insertNode,
					 RetrieveHeight,    RotateNode, BalanceNode);

			else

				Insert< Content_Type,
				        First_Node_Type,
				        Secnd_Node_Type,
				        Order_Relation >

					(treeNode->left(),  insertNode,
					 RetrieveHeight,    RotateNode, BalanceNode);
		}

		BalanceNode(treeNode, RetrieveHeight, RotateNode);
	}


	// -------------------------------------------------------------------
}

#endif /* AVL_INSERT_H_ */
