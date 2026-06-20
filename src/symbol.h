/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef SYMBOL_H
#define SYMBOL_H
#include "code_scan.h"
#include "parser.h"
void sym_init(Scope*scope,Scope*parent,const char*name);Symbol*sym_add(Scope*scope,const char*name,int kind,int type_id);Symbol*sym_lookup(Scope*scope,const char*name);Symbol*sym_lookup_recursive(Scope*scope,const char*name);Symbol*sym_lookup_global(Scope*scope,const char*name);void sym_add_param(Symbol*sym,Symbol*param);void sym_set_type(Symbol*sym,int type_id);int sym_get_type_id(const char*type_name);int sym_types_compatible(int t1,int t2);Symbol*sym_copy(Symbol*s);void sym_free(Symbol*s);Scope*scope_push(ParserState*ps,const char*name);void scope_pop(ParserState*ps);Symbol*scope_find(Scope*scope,const char*name,int recursive);int scope_depth(Scope*scope);void scope_print(Scope*scope,int indent);
#endif
