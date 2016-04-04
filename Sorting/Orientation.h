/*
 * Orientation.h
 *
 *  Created on: Apr 30, 2015
 *      Author: adaniels4
 */

#ifndef ORIENTATION_H_
#define ORIENTATION_H_

enum Orientation
{
	LEAST_TO_GREATEST,
	GREATEST_TO_LEAST
};

const Orientation DEFAULT_ORIENTATION = LEAST_TO_GREATEST;

template <typename Type>
bool InOrder(const Type & value1,
		     const Type & value2,
		     Orientation order)
{
	switch(order)
	{
		case LEAST_TO_GREATEST : return value1 <= value2;
								 break;
		case GREATEST_TO_LEAST : return value2 <= value1;
								 break;
	}
}

#endif /* ORIENTATION_H_ */
