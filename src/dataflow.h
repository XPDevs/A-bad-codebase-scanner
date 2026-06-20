/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef DATAFLOW_H
#define DATAFLOW_H
#include "code_scan.h"
typedef struct{char*name;int version;int def_line;int def_col;int use_count;int is_live;int is_initialized;int is_constant;}DFVar;
typedef struct{DFVar*vars;int nvars;int cap;int*defs;int*uses;int*in_set;int*out_set;int*gen_set;int*kill_set;int set_size;}DFSet;
typedef struct{ASTNode*stmt;DFSet*in;DFSet*out;DFSet*gen;DFSet*kill;int id;}DFBlock;
typedef struct{DFBlock**blocks;int nblocks;int cap;CFGraph*cfg;}DFGraph;
DFGraph*df_build(CFGraph*cfg,ASTNode*func);void df_free(DFGraph*df);DFSet*df_set_new(int size);void df_set_add(DFSet*s,int v);int df_set_contains(DFSet*s,int v);void df_set_union(DFSet*a,DFSet*b);void df_set_intersect(DFSet*a,DFSet*b);void df_set_copy(DFSet*dst,DFSet*src);void df_set_clear(DFSet*s);int df_set_equal(DFSet*a,DFSet*b);void df_reaching_defs(DFGraph*df);void df_live_vars(DFGraph*df);void df_available_exprs(DFGraph*df);void df_very_busy_exprs(DFGraph*df);int df_find_def(DFGraph*df,const char*varname);int df_find_use(DFGraph*df,const char*varname);int df_is_constant(DFGraph*df,const char*varname,int block_id);int df_get_def_count(DFGraph*df,const char*varname);int df_get_block_id(DFGraph*df,ASTNode*stmt);void df_dump(DFGraph*df);
#endif
