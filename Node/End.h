/*
 * End.h
 *
 *  Created on: Apr 21, 2015
 *      Author: adaniels4
 */

#ifndef NODE_END_H_
#define NODE_END_H_

namespace node
{
	template <class First_Node_Type,
			  class Secnd_Node_Type,
			  class Third_Node_Type,
			  class Forth_Node_Type>

	void GetEnd

		(const First_Node_Type & node,
			   Secnd_Node_Type & end,
		       Third_Node_Type & (Forth_Node_Type::*link)())
	{
		end.assign(node);

		while(!(end->*link)().is_null()) end.assign((end->*link)());
	}
}

#endif /* NODE_END_H_ */
