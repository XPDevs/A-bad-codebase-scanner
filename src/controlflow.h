/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CONTROLFLOW_H
#define CONTROLFLOW_H
#include "code_scan.h"
CFGraph*cfg_build(ASTNode*func_body);void cfg_free(CFGraph*g);BasicBlock*cfg_new_block(CFGraph*g);void cfg_add_edge(CFGraph*g,int from,int to);void cfg_add_label(CFGraph*g,int from,int to,const char*label);int cfg_block_count(CFGraph*g);void cfg_compute_dominators(CFGraph*g);void cfg_compute_loops(CFGraph*g);int cfg_is_reachable(CFGraph*g,int block_id);int cfg_is_back_edge(CFGraph*g,int from,int to);int cfg_find_join_point(CFGraph*g,int a,int b);void cfg_dump(CFGraph*g);int cfg_has_path(CFGraph*g,int from,int to,int*visited,int visited_sz);int cfg_count_paths(CFGraph*g,int from,int to);int cfg_get_exit_blocks(CFGraph*g,int**exits);int cfg_find_loops(CFGraph*g,int**loop_heads);int cfg_get_successors(CFGraph*g,int b,BasicBlock***out);int cfg_get_predecessors(CFGraph*g,int b,BasicBlock***out);
#endif
