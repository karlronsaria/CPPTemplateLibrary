/*
 * ROTATE_NODE.h
 *
 *  Created on: Apr 20, 2015
 *      Author: adaniels4
 */

#ifndef ROTATE_NODE_H_
#define ROTATE_NODE_H_

#ifndef ROTATE_NODE
#define ROTATE_NODE(name, type2, type3) \
\
void (*name) \
\
        (type2 &, \
		 type2 & (type3::*link)(), \
		 type2 & (type3::*other_link)())
#endif

#endif /* ROTATE_NODE_H_ */
