/*
 * Pivots.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: adaniels4
 */

#include "Pivots.h"

size_t arraysort::pivot_left(size_t position, size_t length)
{
	return position;
}

size_t arraysort::pivot_middle(size_t position, size_t length)
{
	return position + length / 2;
}

size_t arraysort::pivot_random(size_t position, size_t length)
{
	return rand() % length + position;
}
