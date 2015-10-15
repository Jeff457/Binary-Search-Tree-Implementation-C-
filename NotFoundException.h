/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic D Project						*
*												*
*			NotFoundException.h		 		    *
*			Status: Working              		*
************************************************/

#ifndef _NOT_FOUND_EXCEPTION
#define _NOT_FOUND_EXCEPTION

#include <stdexcept>
#include <string>

using namespace std;

class NotFoundException : public logic_error
{
public:
	NotFoundException() : logic_error("Not Found Exception: The entry was not found") {}
}; // end NotFoundException 

#endif
