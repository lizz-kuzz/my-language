#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include "utils_stk.hpp"

#define INFO_CALL __FUNCTION__, __LINE__, __FILE__

#if MODE != MODE_RELEASE
    #define ASSERT(stk) assert_ok(stk); to_dump(stk, logs_, INFO_CALL);
#else 
    #define ASSERT(stk)                     
#endif

extern FILE *logs_;

void to_dump      (stack *stk, FILE *log, const char *func, int line, const char *name_file);
void printf_errors(stack *stk, FILE *log);
void assert_ok    (stack *stk);
void printf_error (stack *stk, FILE *log);

unsigned long long count_hash (void *data, size_t SIZE);
unsigned long long update_hash (stack *stk);

#endif