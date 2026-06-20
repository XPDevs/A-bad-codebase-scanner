/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_SYNTAX_H
#define CHECKS_SYNTAX_H
#include "code_scan.h"
int check_unmatched_brace(SourceFile*f,Project*p,Issue*out);int check_missing_semicolon(SourceFile*f,Project*p,Issue*out);int check_missing_return(SourceFile*f,Project*p,Issue*out);int check_unclosed_comment(SourceFile*f,Project*p,Issue*out);int check_duplicate_include(SourceFile*f,Project*p,Issue*out);int check_missing_include_guard(SourceFile*f,Project*p,Issue*out);int check_empty_translation(SourceFile*f,Project*p,Issue*out);int check_switch_fallthrough(SourceFile*f,Project*p,Issue*out);int check_duplicate_case(SourceFile*f,Project*p,Issue*out);int check_unreachable_code(SourceFile*f,Project*p,Issue*out);int check_missing_void_param(SourceFile*f,Project*p,Issue*out);int check_empty_if_body(SourceFile*f,Project*p,Issue*out);int check_empty_while_body(SourceFile*f,Project*p,Issue*out);int check_empty_for_body(SourceFile*f,Project*p,Issue*out);int check_label_duplicate(SourceFile*f,Project*p,Issue*out);int check_break_outside_loop(SourceFile*f,Project*p,Issue*out);int check_continue_outside_loop(SourceFile*f,Project*p,Issue*out);
Check*syntax_checks_get(int*n);
#endif
