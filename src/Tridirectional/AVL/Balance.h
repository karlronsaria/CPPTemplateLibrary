/*
 * Rotate.h
 *
 *  Created on: Apr 15, 2015
 *      Author: adaniels4
 */

#ifndef AVL_BALANCE_H_
#define AVL_BALANCE_H_

#include "Height.h"
#include "../Connect.h"
#include "../ROTATE_NODE.h"

#ifndef factor_t
typedef signed char factor_t;
#endif

namespace avl
{
	template <class First_Node_Type>
	void GetBalanceFactor

		(const First_Node_Type & node,
		 factor_t & factor,
		 height_t (*RetrieveHeight)(const First_Node_Type &))
	{
		factor = (factor_t)RetrieveHeight(node->right())
			             - RetrieveHeight(node->left());
	}


	// -------------------------------------------------------------------


	template <class First_Node_Type>
	factor_t BalanceFactor

		(const First_Node_Type & node,
		 height_t (*RetrieveHeight)(const First_Node_Type &))
	{
		factor_t factor = 0;

		GetBalanceFactor(node, factor, RetrieveHeight);

		return factor;
	}


	// -------------------------------------------------------------------


	template <class First_Node_Type,
			  class Secnd_Node_Type>

	void Balance

	  (First_Node_Type & node,

	   height_t (*RetrieveHeight)(const First_Node_Type &),

	   ROTATE_NODE(RotateNode, First_Node_Type, Secnd_Node_Type))

	{
		switch(BalanceFactor<First_Node_Type>(node, RetrieveHeight))
		{
			case -2 : if(BalanceFactor(node->left(), RetrieveHeight) > 0)
					  {
						 RotateNode(node->left(),
								    &Secnd_Node_Type::right,
									&Secnd_Node_Type::left);
					  }

					  RotateNode(node, &Secnd_Node_Type::left,
								       &Secnd_Node_Type::right);
					  break;

			case  2 : if(BalanceFactor(node->right(), RetrieveHeight) < 0)
					  {
						 RotateNode(node->right(),
								    &Secnd_Node_Type::left,
									&Secnd_Node_Type::right);
					  }

					  RotateNode(node,
							     &Secnd_Node_Type::right,
							     &Secnd_Node_Type::left);
					  break;

			default : break;
		}
	}


	// -------------------------------------------------------------------


	template <class First_Node_Type,
			  class Secnd_Node_Type,
		      void (*Change_Height)(First_Node_Type &)>

	void BalanceAndChangeHeight

	  (First_Node_Type & node,

	   height_t (*RetrieveHeight)(const First_Node_Type &),

	   ROTATE_NODE(RotateNode, First_Node_Type, Secnd_Node_Type))

	{
		Change_Height(node);

		Balance(node, RetrieveHeight, RotateNode);
	}


	// -------------------------------------------------------------------


	template <class First_Node_Type,
			  class Secnd_Node_Type>

	void BalanceAndChangeHeight

	  (First_Node_Type & node,

	   height_t (*RetrieveHeight)(const First_Node_Type &),

	   ROTATE_NODE(RotateNode, First_Node_Type, Secnd_Node_Type))

	{
		BalanceAndChangeHeight< First_Node_Type,
		                        Secnd_Node_Type,
		                        QualifiedUpdateHeightOf
		                        	<First_Node_Type> >

			(node, RetrieveHeight, RotateNode);
	}
}

#endif /* AVL_BALANCE_H_ */
