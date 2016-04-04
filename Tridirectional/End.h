/*
 * End.h
 *
 *  Created on: Apr 21, 2015
 *      Author: adaniels4
 */

#ifndef TERNARYNODE_END_H_
#define TERNARYNODE_END_H_

#include "../Node/End.h"

namespace ternarynode
{
	template <class First_Node_Type,
			  class Secnd_Node_Type,
			  class Third_Node_Type,
			  class Forth_Node_Type>

	void GetLeftEnd(const First_Node_Type & node,
			              Secnd_Node_Type & leftEnd)
	{
		node::GetEnd< First_Node_Type,
					  Secnd_Node_Type,
					  Third_Node_Type,
					  Forth_Node_Type >

	  	  	  (node, leftEnd, &Forth_Node_Type::left);
	}


	template <class First_Node_Type,
			  class Secnd_Node_Type,
			  class Third_Node_Type,
			  class Forth_Node_Type>

	void GetRightEnd(const First_Node_Type & node,
            			   Secnd_Node_Type & rightEnd)
	{
		node::GetEnd< First_Node_Type,
					  Secnd_Node_Type,
					  Third_Node_Type,
					  Forth_Node_Type >

	  	  	  (node, rightEnd, &Forth_Node_Type::right);
	}
}

#endif /* TERNARYNODE_END_H_ */
