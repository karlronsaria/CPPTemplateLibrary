/*
 * Rotate.h
 *
 *  Created on: Apr 20, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_ROTATE_H_
#define TERNARYNODE_ROTATE_H_

#include "Connect.h"

namespace ternarynode
{
	template <class First_Node_Type,
			  class Secnd_Node_Type>

	void Rotate

		(First_Node_Type & node,
		 First_Node_Type & (Secnd_Node_Type::*link)(),
		 First_Node_Type & (Secnd_Node_Type::*other_link)())
	{
		if((node->*link)().any())
		{
			First_Node_Type temp;

			temp.assign((node->*link)());

			temp->parent().assign(node->parent());

			ternarynode::Connect< First_Node_Type,
								  Secnd_Node_Type >

						 (node, (temp->*other_link)(), link);

			ternarynode::Connect< First_Node_Type,
								  Secnd_Node_Type >

						 (temp, node, other_link);

			node.assign(temp);

			temp.avert();
		}
	}


	// -------------------------------------------------------------------


	template <class First_Node_Type,
			  class Secnd_Node_Type>

	void RotateLeft(First_Node_Type & node)
	{
		Rotate(node, &Secnd_Node_Type::right, &Secnd_Node_Type::left);
	}


	// -------------------------------------------------------------------


	template <class First_Node_Type,
			  class Secnd_Node_Type>

	void RotateRight(First_Node_Type & node)
	{
		Rotate(node, &Secnd_Node_Type::left, &Secnd_Node_Type::right);
	}


	// -------------------------------------------------------------------


	template <class First_Node_Type,
			  class Secnd_Node_Type,
		      void (*Change_Height)(First_Node_Type &)>

	void RotateAndChangeHeight

		(First_Node_Type & node,
		 First_Node_Type & (Secnd_Node_Type::*link)(),
		 First_Node_Type & (Secnd_Node_Type::*other_link)())
	{
		Rotate(node, link, other_link);

		Change_Height((node->*other_link)());
		Change_Height(node);
	}
}

#endif /* TERNARYNODE_ROTATE_H_ */
