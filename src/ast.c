/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#include "code_scan.h"
#include "ast.h"
ASTNode*ast_create_node(int type,Location loc){ASTNode*n=calloc(1,sizeof(ASTNode));if(!n)return NULL;n->type=type;n->loc=loc;return n;}
ASTNode*ast_create_ident(const char*name,Location loc){ASTNode*n=ast_create_node(1,loc);if(n&&name)snprintf(n->name,sizeof(n->name),"%s",name);return n;}
ASTNode*ast_create_number(long long val,Location loc){ASTNode*n=ast_create_node(2,loc);if(n)n->num_val=val;return n;}
ASTNode*ast_create_float(double val,Location loc){ASTNode*n=ast_create_node(2,loc);if(n){n->fval=val;n->is_float=1;}return n;}
ASTNode*ast_create_string(const char*str,Location loc){ASTNode*n=ast_create_node(3,loc);if(n&&str)n->str_val=code_scan_strdup(str);return n;}
ASTNode*ast_create_block(void){ASTNode*n=calloc(1,sizeof(ASTNode));if(!n)return NULL;n->type=AST_BLOCK;return n;}
ASTNode*ast_create_func_def(const char*name,ASTNode*body){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_FUNC_DEF,loc);if(!n)return NULL;if(name)snprintf(n->name,sizeof(n->name),"%s",name);if(body)ast_add_child(n,body);return n;}
ASTNode*ast_create_call(ASTNode*callee,ASTNode**args,int nargs){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_CALL,loc);if(!n)return NULL;if(callee){ast_add_child(n,callee);if(callee->name[0])snprintf(n->name,sizeof(n->name),"%s",callee->name);}for(int i=0;i<nargs;i++)if(args[i])ast_add_child(n,args[i]);return n;}
ASTNode*ast_create_binary(ASTNode*l,ASTNode*r,int op){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_BINARY,loc);if(!n)return NULL;if(l)ast_add_child(n,l);if(r)ast_add_child(n,r);return n;}
ASTNode*ast_create_unary(ASTNode*operand,int op){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_UNARY,loc);if(!n)return NULL;if(operand)ast_add_child(n,operand);return n;}
ASTNode*ast_create_var_decl(const char*name,ASTNode*type,ASTNode*init){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_VAR_DECL,loc);if(!n)return NULL;if(name)snprintf(n->name,sizeof(n->name),"%s",name);if(type)ast_add_child(n,type);if(init)ast_add_child(n,init);return n;}
ASTNode*ast_create_if(ASTNode*cond,ASTNode*then,ASTNode*els){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_IF,loc);if(!n)return NULL;if(cond)ast_add_child(n,cond);if(then)ast_add_child(n,then);if(els)ast_add_child(n,els);return n;}
ASTNode*ast_create_while(ASTNode*cond,ASTNode*body){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_WHILE,loc);if(!n)return NULL;if(cond)ast_add_child(n,cond);if(body)ast_add_child(n,body);return n;}
ASTNode*ast_create_for(ASTNode*init,ASTNode*cond,ASTNode*inc,ASTNode*body){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_FOR,loc);if(!n)return NULL;if(init)ast_add_child(n,init);if(cond)ast_add_child(n,cond);if(inc)ast_add_child(n,inc);if(body)ast_add_child(n,body);return n;}
ASTNode*ast_create_return(ASTNode*expr){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_RETURN,loc);if(!n)return NULL;if(expr)ast_add_child(n,expr);return n;}
ASTNode*ast_create_cast(ASTNode*type,ASTNode*expr){Location loc;memset(&loc,0,sizeof(loc));ASTNode*n=ast_create_node(AST_CAST,loc);if(!n)return NULL;if(type)ast_add_child(n,type);if(expr)ast_add_child(n,expr);return n;}
void ast_replace_child(ASTNode*p,int i,ASTNode*c){if(!p||!p->children||i<0||i>=p->nchildren)return;c->parent=p;p->children[i]=c;}
void ast_remove_child(ASTNode*p,ASTNode*c){if(!p||!p->children||!c)return;int found=0;for(int i=0;i<p->nchildren;i++){if(p->children[i]==c)found=1;if(found&&i+1<p->nchildren)p->children[i]=p->children[i+1];}if(found)p->nchildren--;}
void ast_free_node(ASTNode*n){if(!n)return;if(n->str_val)free(n->str_val);free(n->children);free(n);}
void ast_free_tree(ASTNode*n){if(!n)return;for(int i=0;i<n->nchildren;i++)ast_free_tree(n->children[i]);if(n->str_val)free(n->str_val);free(n->children);free(n);}
void ast_print(ASTNode*n,int indent){if(!n)return;for(int i=0;i<indent;i++)printf("  ");printf("ASTNode type=%d",n->type);if(n->name[0])printf(" name=%s",n->name);if(n->is_float)printf(" val=%f",n->fval);else if(n->num_val||n->type==2)printf(" val=%lld",n->num_val);if(n->loc.line)printf(" line=%d",n->loc.line);printf("\n");for(int i=0;i<n->nchildren;i++)ast_print(n->children[i],indent+1);}
int ast_count_nodes(ASTNode*n){if(!n)return 0;int c=1;for(int i=0;i<n->nchildren;i++)c+=ast_count_nodes(n->children[i]);return c;}
int ast_has_child_of_type(ASTNode*n,int type){if(!n)return 0;if(n->type==type)return 1;for(int i=0;i<n->nchildren;i++){if(ast_has_child_of_type(n->children[i],type))return 1;}return 0;}
int ast_find_node(ASTNode*n,int type,ASTNode***out,int*count,int*cap){if(!n)return 0;if(n->type==type){if(*count>=*cap){*cap=*cap?*cap*2:64;*out=realloc(*out,*cap*sizeof(ASTNode*));}(*out)[(*count)++]=n;}for(int i=0;i<n->nchildren;i++){ast_find_node(n->children[i],type,out,count,cap);}return *count;}
