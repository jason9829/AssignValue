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

  while(**linePtr != '\0' || *cmpStr != '\0'){
    if((toupper(**linePtr) == toupper(*cmpStr))){
      (*linePtr)++;
                                                                       // How it works
      cmpStr++;                                                        // a | b | c       *linePtr
      cyclesForlinePtr++;                                              // a | b | c | ' '  cmpStr
      cyclesForcmpStr++;                                               // If all correct, return 1
    }
    else
     if(isspace(**linePtr)){
         (*linePtr)++;
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

        else if(isspace(**linePtr)){
        (*linePtr)++;
        cmpStr++;
        cyclesForlinePtr++;
        cyclesForcmpStr++;
        }
        else if(**linePtr == '='){
          (*linePtr)++;
        }
        else
        throwSimpleError(ERR_NOT_A_NUMBER,"No number was found (Empty)");
      }

    }
    else if ((toupper(**linePtr) != toupper(*cmpStr)) && (*cmpStr) !='\0'){         // compare both string byte by byte ignoring the space
                                                                                    // a | b | c       *linePtr
      while(cyclesForlinePtr!=0 && cyclesForcmpStr!=0){                             // a | c | b        cmpStr
        (*linePtr)--;                                                               // First character correct so continue
        cyclesForlinePtr--;                                                         // Second character different so ptr revert back to 'a'
		    cmpStr--;
        cyclesForcmpStr--;
        }
        return 0;                               // If not correct then return 0 after revert back

    }
    else if (isdigit(**linePtr)){
        throwSimpleError(ERR_MALFORM_ASSIGN,"No equal sign was found");
    }

    else
      return 1;

  }   return 1;                                   // If compared true then return 1

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

  while(**linePtr != '\0' && isalpha(**linePtr) == 0){
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


int parseTextAndAssignValue(char **linePtr,VariableMapping *Variableptr){

  int VariableSize = 0;
  int MoveBackVarPtr = 0;
  if(Variableptr == NULL){
    throwSimpleError(ERR_TABLE_IS_MISSING,"No Variable Table was found (NULL)");
  }
  else
    if(*linePtr == NULL || isspace(**linePtr)){
    throwSimpleError(ERR_UNKNOWN_COMMAND,"No command was found (NULL)");
    }
    else
      if(parseAndCompare(linePtr,"assign")){
        while(Variableptr->name != NULL){   // to get the size of the variable Table
          Variableptr++;
          VariableSize++;
          MoveBackVarPtr++;
        }
        while(MoveBackVarPtr != 0 ){
          Variableptr--;
          MoveBackVarPtr--;
        }
        while(VariableSize != 0){
          *Variableptr->storage = parseAndCompare(linePtr,Variableptr->name);
          Variableptr++;
          VariableSize--;
          }
          if(Variableptr->name == NULL && **linePtr != '\0'){
            throwSimpleError(ERR_UNKNOWN_VARIABLE,"No unknown variable was found (NULL)");
          }
      }
      else
      throwSimpleError(ERR_MALFORM_ASSIGN,"No assign was found");



}
