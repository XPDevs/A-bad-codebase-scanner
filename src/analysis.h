/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "code_scan.h"
/* Engine typedef is in code_scan.h */
Engine*engine_init(int threads);void engine_free(Engine*e);void engine_register_check(Engine*e,Check c);void engine_register_all(Engine*e);int engine_analyze_file(Engine*e,SourceFile*f,Project*p);int engine_analyze_project(Engine*e,Project*p);void engine_run_check(Engine*e,Check*ck,SourceFile*f,Project*p,int idx);void engine_set_verbose(Engine*e,int v);void engine_print_stats(Engine*e);
#endif
