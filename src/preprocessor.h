/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "code_scan.h"
typedef struct{char name[256];char value[4096];int is_function_like;int has_params;char params[16][64];int nparams;int is_defined;}MacroDef;
typedef struct{MacroDef*macros;int nmacros;int cap;char**include_paths;int npaths;int include_cap;int depth;int max_depth;}Preprocessor;
typedef struct{char*text;int pos;int len;char*output;int out_pos;int out_cap;Preprocessor*pp;char file[CODE_SCAN_MAX_PATH];int line;int in_cond;int cond_result;int skip_depth;int error;}PPState;
void pp_init(Preprocessor*pp);void pp_add_include_path(Preprocessor*pp,const char*path);void pp_add_builtin(Preprocessor*pp,const char*name,const char*value);void pp_define(Preprocessor*pp,const char*name,const char*value);MacroDef*pp_find(Preprocessor*pp,const char*name);int pp_undef(Preprocessor*pp,const char*name);char*pp_preprocess(Preprocessor*pp,const char*source,const char*file,int*out_len);char*pp_expand_macros(Preprocessor*pp,const char*input,int*out_len);int pp_is_include_line(const char*line);int pp_is_define_line(const char*line);int pp_is_if_line(const char*line);int pp_is_ifdef_line(const char*line);int pp_is_endif_line(const char*line);int pp_is_else_line(const char*line);int pp_is_elif_line(const char*line);int pp_is_pragma_line(const char*line);int pp_is_error_line(const char*line);int pp_is_warning_line(const char*line);int pp_is_line_line(const char*line);int pp_eval_condition(Preprocessor*pp,const char*expr);void pp_free(Preprocessor*pp);
#endif
