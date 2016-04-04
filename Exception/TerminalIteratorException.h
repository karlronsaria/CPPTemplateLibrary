/*
 * TerminalIterator.h
 *
 *  Created on: Apr 22, 2015
 *      Author: adaniels4
 */

#ifndef TERMINALITERATOREXCEPTION_H_
#define TERMINALITERATOREXCEPTION_H_

#include "Exception.h"

class TerminalIterator: public Exception
{
	public: TerminalIterator(const char * functionName):
				Exception(functionName) {}
		   ~TerminalIterator() {}

	        const char * message()

	        				{ return "TerminalIteratorException"; }
};

#endif /* TERMINALITERATOREXCEPTION_H_ */
