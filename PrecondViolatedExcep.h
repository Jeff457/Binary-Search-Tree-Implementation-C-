/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic D Project						*
*												*
*			PrecondViolatedExcep.h		 		*
*			Status: Working              		*
************************************************/

#ifndef _PRECOND_VIOLATED_EXCEP
#define _PRECOND_VIOLATED_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcep : public logic_error
{
public:
	PrecondViolatedExcep(const string& message = "") : logic_error("Precondition Violated Exception: " + message) {}
}; // end PrecondViolatedExcep 
#endif
