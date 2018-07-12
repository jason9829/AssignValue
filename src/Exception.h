#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include "Exception.h"

/*typedef struct {        C++ can't compile
  int   errorCode;
  char *errorMsg;
}Exception;
*/
//**********This********  Equal this
typedef struct Exception Exception;
struct Exception{
  int   errorCode;
  char *errorMsg;
};

//void throwError(int errorCode,char *format,...);
void throwSimpleError (int errorCode, char *errorMsg);
void freeError(Exception *ex);



#endif // _EXCEPTION_H
