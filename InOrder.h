/*
 * InOrder.h
 *
 *  Created on: Apr 28, 2015
 *      Author: adaniels4
 */

#ifndef INORDER_H_
#define INORDER_H_

template <typename Content_Type>
bool InOrder(const Content_Type & first, const Content_Type & secnd)
{
	return first < secnd;
}

#endif /* INORDER_H_ */
