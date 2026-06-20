/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef TAINT_H
#define TAINT_H
#include "code_scan.h"
typedef enum{TS_NONE=0,TS_USER_INPUT,TS_FILE_READ,TS_NETWORK,TS_ENV,TS_ARGV,TS_SYSTEM,TS_UNKNOWN_SRC}TaintSource;
typedef enum{TA_PROPAGATE=1,TA_SINK,TA_SANITIZE,TA_IGNORE}TaintAction;
typedef struct TaintNode{char name[256];int var_id;int source;int is_tainted;int is_sanitized;struct TaintNode*next;}TaintNode;
typedef struct{SourceFile*file;TaintNode**vars;int nvars;int cap;int**flow;int nflow;int sink_count;Location*sinks;int nsink_cap;}TaintGraph;
TaintGraph*taint_init(SourceFile*f);void taint_free(TaintGraph*tg);int taint_add_var(TaintGraph*tg,const char*name,int source);void taint_propagate(TaintGraph*tg,int from,int to);int taint_is_tainted(TaintGraph*tg,int var_id);void taint_sanitize(TaintGraph*tg,int var_id);void taint_mark_sink(TaintGraph*tg,Location loc);int taint_analyze(TaintGraph*tg);int taint_check_sink(TaintGraph*tg,int var_id,Location loc,Issue*out);int taint_track_to_sink(TaintGraph*tg,int var_id,Location*path,int*path_len);void taint_dump(TaintGraph*tg);
#endif
