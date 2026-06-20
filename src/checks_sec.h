/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_SEC_H
#define CHECKS_SEC_H
#include "code_scan.h"
int check_format_string(SourceFile*f,Project*p,Issue*out);int check_command_injection(SourceFile*f,Project*p,Issue*out);int check_path_traversal(SourceFile*f,Project*p,Issue*out);int check_hardcoded_creds(SourceFile*f,Project*p,Issue*out);int check_insecure_temp(SourceFile*f,Project*p,Issue*out);int check_toctou(SourceFile*f,Project*p,Issue*out);int check_insecure_rand(SourceFile*f,Project*p,Issue*out);int check_signal_handler(SourceFile*f,Project*p,Issue*out);int check_setuid_usage(SourceFile*f,Project*p,Issue*out);int check_env_var(SourceFile*f,Project*p,Issue*out);int check_integer_truncation(SourceFile*f,Project*p,Issue*out);int check_sign_conversion(SourceFile*f,Project*p,Issue*out);int check_strcpy_usage(SourceFile*f,Project*p,Issue*out);int check_strcat_usage(SourceFile*f,Project*p,Issue*out);int check_gets_usage(SourceFile*f,Project*p,Issue*out);int check_scanf_usage(SourceFile*f,Project*p,Issue*out);int check_shell_exec(SourceFile*f,Project*p,Issue*out);int check_insecure_crypto(SourceFile*f,Project*p,Issue*out);int check_constant_seed(SourceFile*f,Project*p,Issue*out);int check_race_condition(SourceFile*f,Project*p,Issue*out);
Check*sec_checks_get(int*n);
#endif
