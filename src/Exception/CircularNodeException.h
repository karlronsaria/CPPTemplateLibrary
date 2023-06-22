/*
 * CircularNodeException.h
 *
 *  Created on: Apr 22, 2015
 *      Author: adaniels4
 */

#ifndef CIRCULARNODEEXCEPTION_H_
#define CIRCULARNODEEXCEPTION_H_

#include "Exception.h"

class CircularNode: public Exception
{
	public: CircularNode(const char * functionName):
				Exception(functionName) {}
		   ~CircularNode() {}

	        const char * message() { return "CircularNodeException"; }

};

#endif /* CIRCULARNODEEXCEPTION_H_ */
