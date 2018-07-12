#include "TextParser.h"
#include "CExceptionConfig.h"
#include "CException.h"
#include "Error.h"
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>

/*
 * Parse and compare the strings. It ignore all spaces.
 * If the strings are equal, it returns non-zero, otherwise
 * zero value
 */
int parseAndCompare(char **linePtr, char *cmpStr){
  int cyclesForlinePtr = 0;
  int cyclesForcmpStr = 0;

  char *templinePtr = *linePtr;

  while(**linePtr != '\0' || *cmpStr != '\0'){
    if((toupper(**linePtr) == toupper(*cmpStr))){
      (*linePtr)++;
      templinePtr++;                                                   // How it works
      cmpStr++;                                                        // a | b | c       *linePtr
      cyclesForlinePtr++;
      cyclesForcmpStr++;                                                            // a | b | c | ' '  cmpStr
    }
    else
     if(isspace(**linePtr)){
         (*linePtr)++;
         templinePtr++;
         cyclesForlinePtr++;
     }
     else if(isspace(*cmpStr)){
         cmpStr++;
         cyclesForcmpStr++;

     }
    else if (**linePtr == '='){
      while(**linePtr != '\0' || isspace(**linePtr) ){
        if(isdigit(**linePtr)){
          return parseAndConvertToNum(linePtr);
        }
        else{
          (*linePtr)++;
          templinePtr++;
          cmpStr++;
          cyclesForlinePtr++;
          cyclesForcmpStr++;
        }
      }
    }                                                                  // compare both string byte by byte ignoring the space
    else if ((toupper(**linePtr) != toupper(*cmpStr)) && (*cmpStr) !='\0'){

      while(cyclesForlinePtr!=0 && cyclesForcmpStr!=0){                                                     // a | b | c       *linePtr
        (*linePtr)--;                                                  // a | c | b        cmpStr
        cyclesForlinePtr--;
		cmpStr--;
        cyclesForcmpStr--;                                                     // First character correct so continue
        }                                                          // Second character different so ptr revert back to 'a'
        return 0;

    }
    else
    return 1;

  } return 1;

}

/*
 * Parse and convert the first string number to value.
 * It ignore all spaces.
 * The value is returned if the number is successfully converted.
 * If there is no number, ERR_NOT_A_NUMBER
 * is thrown.
 */
int parseAndConvertToNum(char **linePtr){
  int ConvertedNum = 0;

  while(**linePtr != '\0'){
    if(isdigit(**linePtr)){                                               //  How it works
        ConvertedNum = (**linePtr - '0') + (ConvertedNum * 10);           // *linePtr = '123' ; '0','1','2','3' = 48,49,50,51 in dec
        (*linePtr)++;                                                     // **linePtr = '1' , ConvertedNum = 0
      }                                                                   // 1st, ConvertedNum = ('1' - '0') + (0*10) = 1
    else if (isspace(**linePtr)){                                         //                   =  49  -  48           = 1
        (*linePtr)++;                                                     // 2nd, ConvertedNum = ('2' - '0') + (1*10) = 12
      }                                                                   //                    = 50  -  48  +   10   = 12 ... so on
    else
        return 0;
    }

  return ConvertedNum;

}


int parseTextAndAssignValue(char **line,VariableMapping *Variableptr){

  if(Variableptr == NULL){
    throwSimpleError(ERR_TABLE_IS_MISSING,"No Variable Table was found (NULL)");
  }
  else
    if(*line == NULL || isspace(**line)){
    throwSimpleError(ERR_UNKNOWN_COMMAND,"No command was found (NULL)");
    }
    else
      if(parseAndCompare(line,"assign")){
        return 1;
      }


}
