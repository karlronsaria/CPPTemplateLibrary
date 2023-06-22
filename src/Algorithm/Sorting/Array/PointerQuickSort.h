/*
 * PointerQuickSort.h
 *
 *  Created on: Apr 30, 2015
 *      Author: adaniels4
 */

#ifndef POINTERQUICKSORT_H_
#define POINTERQUICKSORT_H_

#include "../../../Swap.h"
#include "../Orientation.h"

template <typename Type>
void Swap(Type * firstIt, Type * secndIt)
{
	Swap(*firstIt, *secndIt);
}

template <typename Type>
size_t InplacePivotSort(Type * startIt,
					    size_t pivot,
					    size_t position,
					    size_t length,
					    Orientation order)
{
	swap(startIt + position, startIt + pivot);

	Type * leftIt  = startIt + position + 1;
	Type * rightIt = startIt + position + length - 1;

	while(leftIt < rightIt)
	{
		if(!InOrder(*leftIt, *rightIt, order)) swap(leftIt, rightIt);

		while( InOrder(*leftIt,  *(startIt + position), order) &&
			   leftIt  <  startIt + position + length - 1    ) leftIt++;

		while( InOrder(*(startIt + position), *rightIt, order) &&
			   rightIt >  startIt + position                 ) rightIt--;
	}

	if(!in_order(*(startIt + position), *rightIt, order))
		Swap(startIt + position, rightIt);

	pivot = rightIt - startIt;

	return pivot;
}

template <typename Type>
void QuickSort( Type * arrayIt,
			    size_t position,
                size_t length,
			    size_t (*pivot)(size_t, size_t),
                size_t (*sort )(Type *, size_t, size_t, size_t,
                                Orientation),
			    Orientation order )
{
	if(length > 1)
	{
		size_t pivotIndex = (*pivot)(position, length);

		pivotIndex = (*sort)(arrayIt, pivotIndex, position, length, order);

		if(position < pivotIndex)
		{
			QuickSort( arrayIt, position,
					            pivotIndex - position,
					            (*pivot), (*sort), order );
		}

		if(pivotIndex < position + length - 1)
		{
			QuickSort( arrayIt, pivotIndex + 1,
					            length + position - pivotIndex - 1,
					            (*pivot), (*sort), order );
		}
	}
}

#endif /* POINTERQUICKSORT_H_ */
