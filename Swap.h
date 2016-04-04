/*
 * Swap.h
 *
 *  Created on: Apr 30, 2015
 *      Author: adaniels4
 */

#ifndef SWAP_H_
#define SWAP_H_

template <typename Type>
void Swap(Type & firstIt, Type & secndIt)
{
	Type temp = firstIt;
	firstIt   = secndIt;
	secndIt   = temp;
}

#endif /* SWAP_H_ */
