/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CHECKS_CONCURRENCY_H
#define CHECKS_CONCURRENCY_H
#include "code_scan.h"
int check_missing_lock(SourceFile*f,Project*p,Issue*out);int check_double_lock(SourceFile*f,Project*p,Issue*out);int check_unlock_path(SourceFile*f,Project*p,Issue*out);int check_lock_order(SourceFile*f,Project*p,Issue*out);int check_thread_unsafe(SourceFile*f,Project*p,Issue*out);int check_global_data_race(SourceFile*f,Project*p,Issue*out);int check_signal_mt(SourceFile*f,Project*p,Issue*out);int check_tls_usage(SourceFile*f,Project*p,Issue*out);int check_condition_var(SourceFile*f,Project*p,Issue*out);int check_barrier_usage(SourceFile*f,Project*p,Issue*out);
Check*concurrency_checks_get(int*n);
#endif
