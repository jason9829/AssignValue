#include "unity.h"
#include "TextParser.h"

#include "CException.h"
#include "Exception.h"
#include "Error.h"

#include <stdarg.h>
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

void test_parseAndCompare_given_assign_with_space_and_assign_with_melon_should_return_TRUE(void){
    char *line = "     assign melon = 3";
    char *originalLine = line;

    TEST_ASSERT_TRUE(parseAndCompare(&line,"assign  "));
    TEST_ASSERT_EQUAL_PTR(originalLine+12, line);
  }


void test_parseAndCompare_given_assign_with_extra_trailing_space_should_return_TRUE(void){
  char *line = "assign ";
  char *originalLine = line;

  TEST_ASSERT_TRUE(parseAndCompare(&line,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalLine+7, line);
}


void test_parseAndCompare_given_assign_with_space_should_return_TRUE(void){
  char *line = " ";
  char *originalLine = line;

  TEST_ASSERT_TRUE(parseAndCompare(&line," "));
}

void test_parseAndCompare_given_assign_with_equal_sign_should_return_TRUE(void){
  char *line = "=";
  char *originalLine = line;

  TEST_ASSERT_TRUE(parseAndCompare(&line,"="));
}
void test_parseAndCompare_given_assign_Orange_and__Apple_should_return_FALSE(void){
  char *line = "Orange";
  char *originalLine = line;

  TEST_ASSERT_FALSE(parseAndCompare(&line,"Apple"));
  TEST_ASSERT_EQUAL_PTR(originalLine, line);
}

void test_parseAndCompare_given_assign_Orange_with_extra_space_in_front_and__back_should_return_TRUE(void){
  char *line = "   Orange   ";
  char *originalLine = line;

  TEST_ASSERT_TRUE(parseAndCompare(&line,"Orange"));
  TEST_ASSERT_EQUAL_PTR(originalLine+12, line);
}

void test_parseAndCompare_given_assign_with_12345_and__12345_should_return_TRUE(void){
  char *line = "12345";
  char *originalLine = line;

  TEST_ASSERT_TRUE(parseAndCompare(&line,"12345"));
  TEST_ASSERT_EQUAL_PTR(originalLine+5, line);
}
void test_parseAndCompare_given_assign_with_12345_and__54321_should_return_TRUE(void){
  char *line = "12345";
  char *originalLine = line;

  TEST_ASSERT_FALSE(parseAndCompare(&line,"54321"));
  TEST_ASSERT_EQUAL_PTR(originalLine, line);
}
void test_parseAndConvertToNum_given_9_in_char_should_return_9_in_int(void){
  char *line = "9";
  char *originalLine = line;

  TEST_ASSERT_EQUAL(9,parseAndConvertToNum(&line));
}

void test_parseAndConvertToNum_given_123_in_char_should_return_123_in_int(void){
  char *line = "123";
  char *originalLine = line;

  TEST_ASSERT_EQUAL(123,parseAndConvertToNum(&line));
}

void test_parseAndConvertToNum_given_999_in_char_with_space_at_front_and_back_should_return_999_in_int(void){
  char *line = "   999   ";
  char *originalLine = line;

  TEST_ASSERT_EQUAL(999,parseAndConvertToNum(&line));
}

void test_parseAndConvertToNum_given_456_in_char_with_space_at_front_should_return_456_in_int(void){
  char *line = "   456";
  char *originalLine = line;

  TEST_ASSERT_EQUAL(456,parseAndConvertToNum(&line));
}
void test_parseAndConvertToNum_given_456_in_char_with_space_at_behind_should_return_456_in_int(void){
  char *line = "456      ";
  char *originalLine = line;

  TEST_ASSERT_EQUAL(456,parseAndConvertToNum(&line));
}

void test_parseAndConvertToNum_given_abc_in_char_return_0(void){
  char *line = "abc";
  char *originalLine = line;

  TEST_ASSERT_FALSE(parseAndConvertToNum(&line));

}


void test_parseTextAndAssignValue_given_no_table_mapping_should_throw_ERR_TABLE_IS_MISSING(void) {
  CEXCEPTION_T e;
  char *line = " assign mango = 589 ";

  Try {
    parseTextAndAssignValue(&line, NULL);
    TEST_FAIL_MESSAGE("Expect ERR_TABLE_IS_MISSING. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValue_given_no_command_should_do_nothing(void) {
  CEXCEPTION_T e;
  int tomato = 0;
  VariableMapping varTableMapping[] = {
    {"tomato", &tomato},
    {NULL, NULL},
  };
  char *line = NULL;

  Try {
    parseTextAndAssignValue(&line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValue_given_input_command_is_NULL_should_do_nothing(void) {
  CEXCEPTION_T e;
  int kiwi = 0;
  VariableMapping varTableMapping[] = {
    {"kiwi", &kiwi},
    {NULL, NULL},
  };
  char *line = "  ";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

// assign orange  = 21346 apple = 1 lemon=10
void test_parseTextAndAssignValue_VarTable_not_in_order_given_orange_21346_apple_1_lemon_10_should_assigned_correctly(void) {
  CEXCEPTION_T e;
  int orange = 0, apple = 0, lemon = 0;
  VariableMapping varTableMapping[] = {
    {"apple", &apple},
    {"orange", &orange},
    {"lemon", &lemon},
    {NULL, NULL},
  };
  char *line = "assign orange  = 21346 apple = 1 lemon=10";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);

    TEST_ASSERT_EQUAL(21346, orange);
    TEST_ASSERT_EQUAL(1, apple);
    TEST_ASSERT_EQUAL(10, lemon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

// assign orange  = 21346 apple = 1 lemon=10
void test_parseTextAndAssignValue_given_orange_21346_apple_1_lemon_10_should_assigned_correctly(void) {
  CEXCEPTION_T e;
  int orange = 0, apple = 0, lemon = 0;
  VariableMapping varTableMapping[] = {
    {"orange", &orange},
    {"apple", &apple},
    {"lemon", &lemon},
    {NULL, NULL},
  };
  char *line = "assign orange  = 21346 apple = 1 lemon=10";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);

    TEST_ASSERT_EQUAL(21346, orange);
    TEST_ASSERT_EQUAL(1, apple);
    TEST_ASSERT_EQUAL(10, lemon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}
void test_parseTextAndAssignValue_given_melon_and_value_with_trailing_spaces_should_parse_properly(void) {
  CEXCEPTION_T e;
  int melon = 0;
  VariableMapping varTableMapping[] = {
    {"melon  ", &melon},
    {NULL, NULL},
  };
  char *line = "assign melon = 89   ";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);
    TEST_ASSERT_EQUAL(89, melon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValue_given_text_without_assign_should_throw_ERR_UNKNOWN_COMMAND(void) {
  CEXCEPTION_T e;
  int papaya = 0;
  VariableMapping varTableMapping[] = {
    {"papaya", &papaya},
    {NULL, NULL},
  };
  char *line = "  papaya = 345 ";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_COMMAND. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_COMMAND, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValue_given_guava_23_cucumber_92_should_throw_ERR_UNKNOWN_VARIABLE(void) {
  CEXCEPTION_T e;
  int guava = 0;
  VariableMapping varTableMapping[] = {
    {"guava", &guava},
    {NULL, NULL},
  };
  char *line = "assign guava=23 cucumber=92";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_VARIABLE. But no exception thrown.");
  } Catch(e) {
    TEST_ASSERT_EQUAL(23, guava);
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_VARIABLE, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValue_given_malform_pineapple_without_equal_sign_should_throw_ERR_MALFORM_ASSIGN(void) {
  CEXCEPTION_T e;
  int pineapple = 0;
  VariableMapping varTableMapping[] = {
    {"pineapple", &pineapple},
    {NULL, NULL},
  };
  char *line = "assign pineapple 23 ";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORM_ASSIGN. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_MALFORM_ASSIGN, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValue_given_malform_ciku_without_number_should_throw_ERR_NOT_A_NUMBER(void) {
  CEXCEPTION_T e;
  int ciku = 0;
  VariableMapping varTableMapping[] = {
    {"ciku", &ciku},
    {NULL, NULL},
  };
  char *line = "assign ciku =  durian = 6";

  Try {
    parseTextAndAssignValue(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_NOT_A_NUMBER. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_NOT_A_NUMBER, e->errorCode);
    freeError(e);
  }
}
