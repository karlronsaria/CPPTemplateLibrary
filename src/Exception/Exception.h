/*
 * Exception.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

class Exception
{
	public:          Exception(const char * functionName)
	                 {
						 puts("");
						 puts(functionName);
						 printf("[!] ");
	                 }

	        virtual ~Exception()
					 {
						 puts("    Press any key to continue . . . ");
						 std::cin.get();
					 }

	        virtual const char * message() = 0;
};

//template <typename Content_Type,
//          typename Return_Type,
//          class    First_Container_Type,
//          template<typename> class Secnd_Container_Type>
//
//Return_Type TryAndReturn
//
//	(First_Container_Type & container,
//	 Return_Type (Secnd_Container_Type<Content_Type>::*get_content)())
//{
//	try
//	{
//		if(!container.any())  throw  NoData();
//		else                     return (container->*get_content)();
//	}
//	catch(NodeException & e)
//	{
//		puts(e.message());
//		return Return_Type();
//	}
//}

#endif /* EXCEPTION_H_ */
