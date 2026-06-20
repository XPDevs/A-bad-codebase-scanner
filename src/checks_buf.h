/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_BUF_H
#define CHECKS_BUF_H
#include "code_scan.h"
int check_static_buffer(SourceFile*f,Project*p,Issue*out);int check_dynamic_buffer(SourceFile*f,Project*p,Issue*out);int check_array_index(SourceFile*f,Project*p,Issue*out);int check_fixed_buffer(SourceFile*f,Project*p,Issue*out);int check_unsafe_memcpy(SourceFile*f,Project*p,Issue*out);int check_unsafe_memset(SourceFile*f,Project*p,Issue*out);int check_unsafe_memmove(SourceFile*f,Project*p,Issue*out);int check_unsafe_sprintf(SourceFile*f,Project*p,Issue*out);int check_unsafe_snprintf(SourceFile*f,Project*p,Issue*out);int check_unsafe_strcpy(SourceFile*f,Project*p,Issue*out);int check_unsafe_strcat(SourceFile*f,Project*p,Issue*out);int check_unsafe_gets(SourceFile*f,Project*p,Issue*out);int check_unsafe_scanf(SourceFile*f,Project*p,Issue*out);int check_unsafe_realpath(SourceFile*f,Project*p,Issue*out);int check_unsafe_getenv(SourceFile*f,Project*p,Issue*out);int check_read_beyond(SourceFile*f,Project*p,Issue*out);int check_write_beyond(SourceFile*f,Project*p,Issue*out);int check_unsafe_realloc(SourceFile*f,Project*p,Issue*out);int check_null_termination(SourceFile*f,Project*p,Issue*out);int check_stack_buffer_size(SourceFile*f,Project*p,Issue*out);
Check*buf_checks_get(int*n);
#endif
