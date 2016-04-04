/*
 * Remove.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef AVL_REMOVE_H_
#define AVL_REMOVE_H_

#include "../../Tridirectional/Orphan.h"
#include "../Remove.h"
#include "Balance.h"

namespace avl
{
//	template <class Node_Type>
//	void GetLeftEnd(const Node_Type & node, Node_Type & leftEnd)
//	{
//		leftEnd.assign(node);
//
//		while(!leftEnd->left().is_null())
//			leftEnd.assign(leftEnd->left());
//	}


	// -------------------------------------------------------------------


	template <class First_Node_Type,
			  class Secnd_Node_Type>

	First_Node_Type & Shift(First_Node_Type & node,

	   height_t (*RetrieveHeight) (const First_Node_Type &),

	   ROTATE_NODE(RotateNode, First_Node_Type, Secnd_Node_Type),

	   void     (*BalanceNode)

	   	   	   	  (First_Node_Type &,

				   height_t (*RetrieveHeight) (const First_Node_Type &),

				   ROTATE_NODE(RotateNode, First_Node_Type,
						                   Secnd_Node_Type)))
	{
		if(!node.is_null())
		{
			if(node->left().is_null()) return node->right();

			ternarynode::ConnectLeft< First_Node_Type,
									  Secnd_Node_Type >

							(node, Shift(node->left(), RetrieveHeight,
										 RotateNode,   BalanceNode));

			BalanceNode(node, RetrieveHeight, RotateNode);
		}

		return node;
	}


	// -------------------------------------------------------------------


	template <typename Content_Type,
			  class First_Node_Type,
			  class Secnd_Node_Type,
              bool (*Order_Relation)(const Content_Type &,
  		                             const Content_Type &)>

	bool Remove(First_Node_Type & node, const Content_Type & key,

	   height_t (*RetrieveHeight) (const First_Node_Type &),

	   ROTATE_NODE(RotateNode, First_Node_Type, Secnd_Node_Type),

	   void     (*BalanceNode)

	   	   	   	  (First_Node_Type &,

				   height_t (*RetrieveHeight) (const First_Node_Type &),

				   ROTATE_NODE(RotateNode, First_Node_Type,
						                   Secnd_Node_Type)))
	{
		if(node.is_null()) return false;
		else
		{
			if(key == node->content())
			{
				First_Node_Type leftEnd;

				if(node->right().is_null())

					leftEnd.assign(node->left());

				else

					ternarynode::GetLeftEnd< First_Node_Type,
					                         First_Node_Type,
					                         First_Node_Type,
					                         Secnd_Node_Type >

									(node->right(), leftEnd);

				if(leftEnd.is_null()) node.deallocate();
				else
				{
					ternarynode::ConnectRight< First_Node_Type,
											   Secnd_Node_Type >

											 (leftEnd,
											  Shift(node->right(),
													RetrieveHeight,
													RotateNode,
													BalanceNode));

					ternarynode::ConnectLeft< First_Node_Type,
											  Secnd_Node_Type >

											(leftEnd, node->left());

					ternarynode::Orphan(node);

					node.deallocate();

					node.assign(leftEnd);

					Balance(node, RetrieveHeight, RotateNode);

					leftEnd.avert();
				}

				return true;
			}
			else
			{
				bool found;

				if(Order_Relation(key, node->content()))
				{
					found = Remove< Content_Type,
				                    First_Node_Type,
				                    Secnd_Node_Type,
				                    Order_Relation >

								(node->left(), key, RetrieveHeight,
								 RotateNode, BalanceNode);
				}
				else
				{
					found = Remove< Content_Type,
				                    First_Node_Type,
				                    Secnd_Node_Type,
				                    Order_Relation >

								(node->right(), key, RetrieveHeight,
								 RotateNode, BalanceNode);
				}

				Balance(node, RetrieveHeight, RotateNode);

				return found;
			}
		}
	}
}

#endif /* AVL_REMOVE_H_ */
