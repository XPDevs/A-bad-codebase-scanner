/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_QUALITY_H
#define CHECKS_QUALITY_H
#include "code_scan.h"
int check_magic_number(SourceFile*f,Project*p,Issue*out);int check_deep_nesting(SourceFile*f,Project*p,Issue*out);int check_long_function(SourceFile*f,Project*p,Issue*out);int check_many_params(SourceFile*f,Project*p,Issue*out);int check_global_var(SourceFile*f,Project*p,Issue*out);int check_missing_const(SourceFile*f,Project*p,Issue*out);int check_shadowed_var(SourceFile*f,Project*p,Issue*out);int check_unused_var(SourceFile*f,Project*p,Issue*out);int check_unused_func(SourceFile*f,Project*p,Issue*out);int check_assignment_in_cond(SourceFile*f,Project*p,Issue*out);int check_comma_operator(SourceFile*f,Project*p,Issue*out);int check_goto_usage(SourceFile*f,Project*p,Issue*out);int check_switch_without_default(SourceFile*f,Project*p,Issue*out);int check_missing_break(SourceFile*f,Project*p,Issue*out);int check_function_complexity(SourceFile*f,Project*p,Issue*out);int check_too_many_locals(SourceFile*f,Project*p,Issue*out);int check_mixed_declarations(SourceFile*f,Project*p,Issue*out);int check_trailing_whitespace(SourceFile*f,Project*p,Issue*out);int check_tab_vs_spaces(SourceFile*f,Project*p,Issue*out);int check_long_line(SourceFile*f,Project*p,Issue*out);
Check*quality_checks_get(int*n);
#endif
