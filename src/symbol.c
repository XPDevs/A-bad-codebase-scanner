/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#include "code_scan.h"
#include "symbol.h"
static int next_type_id=1;
static const struct{const char*name;int id;}builtin_types[]={{"void",0},{"char",1},{"short",2},{"int",3},{"long",4},{"float",5},{"double",6},{"signed",3},{"unsigned",7},{"_Bool",8},{"_Complex",9},{NULL,0}};
void sym_init(Scope*scope,Scope*parent,const char*name){memset(scope,0,sizeof(*scope));scope->parent=parent;if(name)snprintf(scope->name,sizeof(scope->name),"%s",name);else snprintf(scope->name,sizeof(scope->name),"global");scope->depth=parent?parent->depth+1:0;scope->symbols=NULL;scope->nsymbols=0;}
Symbol*sym_add(Scope*scope,const char*name,int kind,int type_id){if(!scope||!name)return NULL;for(int i=0;i<scope->nsymbols;i++){if(strcmp(scope->symbols[i].name,name)==0)return &scope->symbols[i];}Symbol*new_syms=realloc(scope->symbols,(scope->nsymbols+1)*sizeof(Symbol));if(!new_syms)return NULL;scope->symbols=new_syms;Symbol*s=&scope->symbols[scope->nsymbols++];memset(s,0,sizeof(*s));snprintf(s->name,sizeof(s->name),"%s",name);s->type_id=type_id;s->kind=kind;return s;}
Symbol*sym_lookup(Scope*scope,const char*name){if(!scope||!name)return NULL;for(int i=0;i<scope->nsymbols;i++){if(strcmp(scope->symbols[i].name,name)==0)return &scope->symbols[i];}return NULL;}
Symbol*sym_lookup_recursive(Scope*scope,const char*name){Scope*s=scope;while(s){Symbol*sym=sym_lookup(s,name);if(sym)return sym;s=s->parent;}return NULL;}
Symbol*sym_lookup_global(Scope*scope,const char*name){Scope*s=scope;while(s&&s->parent)s=s->parent;if(!s)return NULL;return sym_lookup(s,name);}
void sym_add_param(Symbol*sym,Symbol*param){if(!sym||!param)return;Symbol*newp=realloc(sym->params,(sym->nparams+1)*sizeof(Symbol));if(!newp)return;sym->params=newp;sym->params[sym->nparams++]=*param;}
void sym_set_type(Symbol*sym,int type_id){if(sym)sym->type_id=type_id;}
int sym_get_type_id(const char*type_name){for(int i=0;builtin_types[i].name;i++){if(strcmp(type_name,builtin_types[i].name)==0)return builtin_types[i].id;}static struct{char name[64];int id;}*user_types=NULL;static int nuser=0;for(int i=0;i<nuser;i++){if(strcmp(user_types[i].name,type_name)==0)return user_types[i].id;}nuser++;user_types=realloc(user_types,nuser*sizeof(*user_types));if(!user_types)return -1;snprintf(user_types[nuser-1].name,sizeof(user_types[nuser-1].name),"%s",type_name);user_types[nuser-1].id=next_type_id++;return user_types[nuser-1].id;}
int sym_types_compatible(int t1,int t2){if(t1==t2)return 1;if(t1==0||t2==0)return 1;if(t1==3&&(t2==1||t2==2||t2==4||t2==7))return 1;if(t2==3&&(t1==1||t1==2||t1==4||t1==7))return 1;if(t1==6&&t2==5)return 1;if(t2==6&&t1==5)return 1;return 0;}
Symbol*sym_copy(Symbol*s){if(!s)return NULL;Symbol*c=malloc(sizeof(*c));if(!c)return NULL;memcpy(c,s,sizeof(*c));c->params=NULL;c->nparams=0;if(s->params&&s->nparams>0){c->params=malloc(s->nparams*sizeof(Symbol));if(c->params)memcpy(c->params,s->params,s->nparams*sizeof(Symbol));}return c;}
void sym_free(Symbol*s){if(!s)return;if(s->params)free(s->params);free(s);}
Scope*scope_push(ParserState*ps,const char*name){Scope*new_scope=calloc(1,sizeof(Scope));if(!new_scope)return NULL;sym_init(new_scope,ps->scope,name);ps->scope=new_scope;return new_scope;}
void scope_pop(ParserState*ps){if(ps->scope){Scope*old=ps->scope;ps->scope=old->parent;}}
Symbol*scope_find(Scope*scope,const char*name,int recursive){if(!scope||!name)return NULL;if(recursive){Scope*s=scope;while(s){Symbol*sym=sym_lookup(s,name);if(sym)return sym;s=s->parent;}return NULL;}return sym_lookup(scope,name);}
int scope_depth(Scope*scope){int d=0;while(scope){d++;scope=scope->parent;}return d;}
void scope_print(Scope*scope,int indent){if(!scope)return;for(int i=0;i<indent;i++)code_scan_printf("  ");code_scan_printf("Scope: %s (depth %d, symbols: %d)\n",scope->name,scope->depth,scope->nsymbols);for(int i=0;i<scope->nsymbols;i++){for(int j=0;j<indent+1;j++)code_scan_printf("  ");code_scan_printf("Symbol: %s type=%d kind=%d defined=%d\n",scope->symbols[i].name,scope->symbols[i].type_id,scope->symbols[i].kind,scope->symbols[i].defined);}}
