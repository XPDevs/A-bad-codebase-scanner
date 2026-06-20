/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_TYPES_H
#define CHECKS_TYPES_H
#include "code_scan.h"
int check_implicit_func_decl(SourceFile*f,Project*p,Issue*out);int check_implicit_int(SourceFile*f,Project*p,Issue*out);int check_type_mismatch(SourceFile*f,Project*p,Issue*out);int check_ptr_mismatch(SourceFile*f,Project*p,Issue*out);int check_assignment_type(SourceFile*f,Project*p,Issue*out);int check_func_proto_mismatch(SourceFile*f,Project*p,Issue*out);int check_return_type(SourceFile*f,Project*p,Issue*out);int check_arg_type(SourceFile*f,Project*p,Issue*out);int check_null_compare(SourceFile*f,Project*p,Issue*out);int check_enum_mismatch(SourceFile*f,Project*p,Issue*out);int check_struct_assignment(SourceFile*f,Project*p,Issue*out);int check_union_type(SourceFile*f,Project*p,Issue*out);int check_void_pointer_arithmetic(SourceFile*f,Project*p,Issue*out);int check_function_pointer_cast(SourceFile*f,Project*p,Issue*out);
Check*type_checks_get(int*n);
#endif
