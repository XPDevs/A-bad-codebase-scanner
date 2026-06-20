/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_MEM_H
#define CHECKS_MEM_H
#include "code_scan.h"
int check_null_deref(SourceFile*f,Project*p,Issue*out);int check_use_after_free(SourceFile*f,Project*p,Issue*out);int check_double_free(SourceFile*f,Project*p,Issue*out);int check_memory_leak(SourceFile*f,Project*p,Issue*out);int check_mismatched_alloc(SourceFile*f,Project*p,Issue*out);int check_uninit_var(SourceFile*f,Project*p,Issue*out);int check_stack_buffer_overflow(SourceFile*f,Project*p,Issue*out);int check_heap_buffer_overflow(SourceFile*f,Project*p,Issue*out);int check_integer_overflow(SourceFile*f,Project*p,Issue*out);int check_alloca_usage(SourceFile*f,Project*p,Issue*out);int check_realloc_usage(SourceFile*f,Project*p,Issue*out);int check_flexible_array(SourceFile*f,Project*p,Issue*out);int check_off_by_one(SourceFile*f,Project*p,Issue*out);int check_memset_overflow(SourceFile*f,Project*p,Issue*out);int check_memcpy_overflow(SourceFile*f,Project*p,Issue*out);int check_strncpy_usage(SourceFile*f,Project*p,Issue*out);int check_sprintf_overflow(SourceFile*f,Project*p,Issue*out);int check_variable_length_array(SourceFile*f,Project*p,Issue*out);int check_return_local_addr(SourceFile*f,Project*p,Issue*out);int check_dangling_pointer(SourceFile*f,Project*p,Issue*out);
Check*mem_checks_get(int*n);
#endif
