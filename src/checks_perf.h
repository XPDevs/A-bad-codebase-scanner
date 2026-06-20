/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_PERF_H
#define CHECKS_PERF_H
#include "code_scan.h"
int check_pass_by_value(SourceFile*f,Project*p,Issue*out);int check_unnecessary_copy(SourceFile*f,Project*p,Issue*out);int check_loop_invariant(SourceFile*f,Project*p,Issue*out);int check_inefficient_string(SourceFile*f,Project*p,Issue*out);int check_recursion(SourceFile*f,Project*p,Issue*out);int check_nested_loop(SourceFile*f,Project*p,Issue*out);int check_redundant_branch(SourceFile*f,Project*p,Issue*out);int check_constant_loop(SourceFile*f,Project*p,Issue*out);int check_typedef_perf(SourceFile*f,Project*p,Issue*out);int check_volatile_usage(SourceFile*f,Project*p,Issue*out);
Check*perf_checks_get(int*n);
#endif
