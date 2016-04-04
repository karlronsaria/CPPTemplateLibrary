/*
 * Pivots.h
 *
 *  Created on: Apr 30, 2015
 *      Author: adaniels4
 */

#ifndef PIVOTS_H_
#define PIVOTS_H_

#include <stdlib.h>

namespace arraysort
{
	size_t pivot_left   (size_t pos, size_t len);

	size_t pivot_middle (size_t pos, size_t len);

	size_t pivot_random (size_t pos, size_t len);
}

#endif /* PIVOTS_H_ */
