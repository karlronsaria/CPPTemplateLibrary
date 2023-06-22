/*
 * NoDataException.h
 *
 *  Created on: Apr 22, 2015
 *      Author: adaniels4
 */

#ifndef NODATAEXCEPTION_H_
#define NODATAEXCEPTION_H_

#include "Exception.h"

class NoData: public Exception
{
	public: NoData(const char * functionName):
				Exception(functionName) {}
		   ~NoData() {}

	        const char * message() { return "NoDataException"; }

};

#endif /* NODATAEXCEPTION_H_ */
