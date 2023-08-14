/*
 * Splay.h
 *
 *  Created on: Apr 20, 2015
 *      Author: adaniels4
 */

#ifndef SPLAY_H_
#define SPLAY_H_

#include "Rotate.h"
#include "ROTATE_NODE.h"

namespace splay
{
	template <typename Content_Type,
			  class First_Node_Type>

	bool Search(First_Node_Type & node, const Content_Type & key)
	{
		return !node.any() || node->content() == key;
	}


	template <typename Content_Type,
			  class First_Node_Type>

	bool Insert(First_Node_Type & node, const Content_Type & key)
	{
		if(!node.any())
		{
			node.reallocate();

			node->content(key);

			return true;
		}
		else return false;
	}


	template <typename Content_Type,
			  class First_Node_Type,
			  class Secnd_Node_Type>

	bool Remove(First_Node_Type & node, const Content_Type & key)
	{
		if(!node.any()) return true;
		else if(node->content() == key)
		{
			ternarynode::Remove<First_Node_Type, Secnd_Node_Type>(node);

			return true;
		}
		else return false;
	}


	template <typename Content_Type,
			  class First_Node_Type,
			  class Secnd_Node_Type,
			  bool (*Order_Relation)(const Content_Type &,
									 const Content_Type &)>

	void Splay

		(First_Node_Type & node, const Content_Type & key,

		 bool (*Function)(First_Node_Type &, const Content_Type &))
	{
		if(!Function(node, key))
		{
			if(Order_Relation(key, node->content()))
			{
				if(!Function(node->left(), key))
				{
					if(Order_Relation(key, node->left()->content()))
					{
						Splay< Content_Type,
							   First_Node_Type,
							   Secnd_Node_Type,
							   Order_Relation >

							   (node->left()->left(), key, Function);

						ternarynode::RotateRight< First_Node_Type,
												  Secnd_Node_Type >(node);
					}
					else if(Order_Relation(node->left()->content(), key))
					{
						Splay< Content_Type,
							   First_Node_Type,
							   Secnd_Node_Type,
							   Order_Relation >

							   (node->left()->right(), key, Function);

						ternarynode::RotateLeft< First_Node_Type,
												 Secnd_Node_Type >

												 (node->left());
					}
				}

				ternarynode::RotateRight< First_Node_Type,
										  Secnd_Node_Type >(node);
			}
			else if(Order_Relation(node->content(), key))
			{
				if(!Function(node->right(), key))
				{
					if(Order_Relation(key, node->right()->content()))
					{
						Splay< Content_Type,
							   First_Node_Type,
							   Secnd_Node_Type,
							   Order_Relation >

							   (node->right()->left(), key, Function);

						ternarynode::RotateRight< First_Node_Type,
												  Secnd_Node_Type >

												  (node->right());
					}
					else if(Order_Relation(node->right()->content(), key))
					{
						Splay< Content_Type,
							   First_Node_Type,
							   Secnd_Node_Type,
							   Order_Relation >

							   (node->right()->right(), key, Function);

						ternarynode::RotateLeft< First_Node_Type,
												 Secnd_Node_Type >(node);
					}
				}

				ternarynode::RotateLeft< First_Node_Type,
										 Secnd_Node_Type >(node);
			}
		}
	}
}

#endif /* SPLAY_H_ */
