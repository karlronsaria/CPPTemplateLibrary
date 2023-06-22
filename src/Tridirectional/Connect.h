/*
 * Connect.h
 *
 *  Created on: Apr 17, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_CONNECT_H_
#define TERNARYNODE_CONNECT_H_

#include "../Node/Connect.h"

namespace ternarynode
{
	template <class First_Node_Type,
	          class Secnd_Node_Type>

	bool Connect

		(First_Node_Type & first,
		 First_Node_Type & secnd,

		 First_Node_Type & (Secnd_Node_Type::*link)())
	{
		return node::Connect< First_Node_Type,
							  First_Node_Type,
							  First_Node_Type,
							  typename First_Node_Type::locator,
							  Secnd_Node_Type >

				(first, secnd, link, &Secnd_Node_Type::parent);
	}

	template <class First_Node_Type,
			  class Secnd_Node_Type,
	          class Third_Node_Type,
	          class Forth_Node_Type,
	          class Fifth_Node_Type>

	bool ConnectLeft

		(First_Node_Type & first,
		 Secnd_Node_Type & secnd)
	{
		return node::Connect< First_Node_Type,
				              Secnd_Node_Type,
				              Third_Node_Type,
				              Forth_Node_Type,
				              Fifth_Node_Type >

				(first, secnd, &Fifth_Node_Type::left,
							   &Fifth_Node_Type::parent);
	}

	template <class First_Node_Type,
			  class Secnd_Node_Type,
	          class Third_Node_Type,
	          class Forth_Node_Type,
	          class Fifth_Node_Type>

	bool ConnectRight

		(First_Node_Type & first,
		 Secnd_Node_Type & secnd)
	{
		return node::Connect< First_Node_Type,
				              Secnd_Node_Type,
				              Third_Node_Type,
				              Forth_Node_Type,
				              Fifth_Node_Type >

				(first, secnd, &Fifth_Node_Type::right,
							   &Fifth_Node_Type::parent);
	}

	template <class First_Node_Type,
	          class Secnd_Node_Type>

	bool ConnectLeft

		(First_Node_Type & first,
		 First_Node_Type & secnd)
	{
		return node::Connect< First_Node_Type,
				              First_Node_Type,
				              First_Node_Type,
				              typename First_Node_Type::locator,
				              Secnd_Node_Type >

				(first, secnd, &Secnd_Node_Type::left,
							   &Secnd_Node_Type::parent);
	}

	template <class First_Node_Type,
	          class Secnd_Node_Type>

	bool ConnectRight

		(First_Node_Type & first,
		 First_Node_Type & secnd)
	{
		return node::Connect< First_Node_Type,
							  First_Node_Type,
							  First_Node_Type,
							  typename First_Node_Type::locator,
							  Secnd_Node_Type >

				(first, secnd, &Secnd_Node_Type::right,
							   &Secnd_Node_Type::parent);
	}
}

#endif /* TERNARYNODE_CONNECT_H_ */
