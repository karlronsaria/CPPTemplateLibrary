/*
 * arraysort.h
 *
 *  Created on: Nov 3, 2014
 *      Author: Drew
 */

#ifndef ARRAYSORT_H_
#define ARRAYSORT_H_

#include "../../../Swap.h"
#include "../Orientation.h"

namespace arraysort
{
	template <typename Content_Type, template<typename> class Array_Type>
	size_t InplaceQuickSort(Array_Type<Content_Type> & array,
							size_t        left,
							size_t        right,
							Orientation   order,
							size_t      (*findPivot)(size_t, size_t));

	template <typename Content_Type, template<typename> class Array_Type>
	void QuickSort(Array_Type<Content_Type> & array,
				   size_t        left,
				   size_t        right,
				   Orientation   order,
				   size_t      (*findPivot)(size_t, size_t));
}



template <typename C, template<typename> class A>
size_t arraysort::InplaceQuickSort

		(A<C> &        array,
		 size_t        left,
		 size_t        right,
		 Orientation   order,
		 size_t      (*findPivot)(size_t, size_t))
{
	size_t i     = left;
	size_t j     = right;
	size_t pivot = array[findPivot(left, right)];

	while(i <= j)
	{
		while(in_order(array[i], pivot, order)) ++i;

		while(in_order(pivot, array[j], order)) --j;

		if(i <= j) Swap(array[left], array[right]);
	}

	return i;
}

template <typename C, template<typename> class A>
void arraysort::QuickSort

		(A<C> &        array,
		 size_t        left,
		 size_t        right,
		 Orientation   order,
		 size_t      (*findPivot)(size_t, size_t))
{
	size_t index = inplace_pivot_sort(array, left,  right,
			                          order, findPivot);

	if (left  < index - 1) quick_sort(array, left,  index - 1,
			                          order, findPivot);

	if (index < right)     quick_sort(array, index, right,
			                          order, findPivot);
}

#endif /* ARRAYSORT_H_ */
