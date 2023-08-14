/*
 * Remove.h
 *
 *  Created on: Apr 21, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_REMOVE_H_
#define TERNARYNODE_REMOVE_H_

#include "End.h"

namespace ternarynode
{
	template <class First_Node_Type,
			  class Secnd_Node_Type>

	void Remove(First_Node_Type & node)
	{
		First_Node_Type temp;

		if(node->left().any())
		{
			GetRightEnd< First_Node_Type,
			             First_Node_Type,
			             First_Node_Type,
			             Secnd_Node_Type >(node->left(), temp);

			if(node->left()->right().any())

				ConnectRight< typename First_Node_Type::locator,
				              First_Node_Type,
				              First_Node_Type,
				              typename First_Node_Type::locator,
				              Secnd_Node_Type >

						(temp->parent(), temp->left());
		}
		else if(node->right().any())
		{
			GetLeftEnd< First_Node_Type,
			            First_Node_Type,
			            First_Node_Type,
			            Secnd_Node_Type >(node->right(), temp);

			if(node->right()->left().any())

				ConnectLeft< typename First_Node_Type::locator,
							 First_Node_Type,
							 First_Node_Type,
							 typename First_Node_Type::locator,
							 Secnd_Node_Type >

						(temp->parent(), temp->right());
		}

		if(temp.any())
		{
			if(temp != node->left())

				ConnectLeft  < First_Node_Type,
						       Secnd_Node_Type >(temp, node->left());

			if(temp != node->right())

				ConnectRight < First_Node_Type,
						       Secnd_Node_Type >(temp, node->right());

			temp->parent().assign(node->parent());
			Orphan(node);
		}

		swap(node, temp);
	}
}

#endif /* TERNARYNODE_REMOVE_H_ */
