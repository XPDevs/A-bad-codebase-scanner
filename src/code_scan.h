/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef CODE_SCAN_H
#define CODE_SCAN_H
/* _GNU_SOURCE set by compiler flags */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>
#include <stdarg.h>
#include <setjmp.h>
#include <regex.h>
#include <errno.h>
#define CODE_SCAN_VERSION "2.0.0"
#define CODE_SCAN_MAX_PATH 4096
#define MTHOS_MAX_LINE 65536
#define MTHOS_MAX_TOKENS 262144
#define MTHOS_MAX_FILES 131072
#define MTHOS_MAX_ISSUES 1048576
#define MTHOS_MAX_SCOPES 65536
#define MTHOS_MAX_SYMBOLS 262144
#define MTHOS_MAX_INCLUDES 65536
#define MTHOS_MAX_AST_NODES 524288
#define MTHOS_MAX_BB 131072
#define MTHOS_MAX_TAINT 262144
#define CODE_SCAN_THREAD_MAX 64
#define MTHOS_BUF_SIZE 8192
typedef enum{TK_EOF=0,TK_ID,TK_NUMBER,TK_STRING,TK_CHAR,TK_LBRACE,TK_RBRACE,TK_LPAREN,TK_RPAREN,TK_LBRACK,TK_RBRACK,TK_SEMI,TK_COMMA,TK_DOT,TK_ARROW,TK_PLUS,TK_MINUS,TK_STAR,TK_SLASH,TK_PERCENT,TK_AMP,TK_PIPE,TK_CARET,TK_TILDE,TK_EXCL,TK_QUESTION,TK_COLON,TK_EQ,TK_NEQ,TK_LT,TK_GT,TK_LE,TK_GE,TK_LSHIFT,TK_RSHIFT,TK_PLUS_EQ,TK_MINUS_EQ,TK_STAR_EQ,TK_SLASH_EQ,TK_PERCENT_EQ,TK_AMP_EQ,TK_PIPE_EQ,TK_CARET_EQ,TK_LSHIFT_EQ,TK_RSHIFT_EQ,TK_INC,TK_DEC,TK_AND,TK_OR,TK_ELLIPSIS,TK_DBL_HASH,TK_HASH,TK_IF,TK_ELSE,TK_SWITCH,TK_CASE,TK_DEFAULT,TK_WHILE,TK_DO,TK_FOR,TK_RETURN,TK_BREAK,TK_CONTINUE,TK_GOTO,TK_TYPEDEF,TK_EXTERN,TK_STATIC,TK_AUTO,TK_REGISTER,TK_INLINE,TK_CONST,TK_VOLATILE,TK_RESTRICT,TK_VOID,TK_SHORT,TK_INT,TK_LONG,TK_FLOAT,TK_DOUBLE,TK_SIGNED,TK_UNSIGNED,TK_BOOL,TK_COMPLEX,TK_STRUCT,TK_UNION,TK_ENUM,TK_SIZEOF,TK_ALIGNOF,TK_ATTRIBUTE,TK_ASM,TK_BLOCK_OPEN,TK_BLOCK_CLOSE,TK_UNKNOWN}TokenType;
typedef enum{SEV_INFO=0,SEV_WARNING,SEV_ERROR,SEV_CRITICAL}Severity;
typedef enum{CAT_SYNTAX=0,CAT_SECURITY,CAT_MEMORY,CAT_TYPE,CAT_PERFORMANCE,CAT_CONCURRENCY,CAT_QUALITY,CAT_PREPROCESSOR,CAT_BUFFER,CAT_PORTABILITY,CAT_STYLE,CAT_LANG_SPECIFIC}Category;
extern const char*lang_str[];
typedef enum{AST_FILE=1,AST_FUNC_DEF,AST_FUNC_DECL,AST_VAR_DECL,AST_STRUCT,AST_UNION,AST_ENUM,AST_ENUM_VAL,AST_TYPEDEF,AST_PARAM,AST_BLOCK,AST_IF,AST_IF_ELSE,AST_WHILE,AST_DO,AST_FOR,AST_SWITCH,AST_CASE,AST_DEFAULT,AST_RETURN,AST_BREAK,AST_CONTINUE,AST_GOTO,AST_LABEL,AST_EXPR_STMT,AST_BINARY,AST_UNARY,AST_CALL,AST_ASSIGN,AST_COND,AST_MEMBER,AST_PTR_MEMBER,AST_INDEX,AST_CAST,AST_SIZEOF,AST_STRING,AST_NUMBER,AST_IDENT,AST_INIT_LIST,AST_EMPTY_STMT,AST_ASM,AST_ATTRIBUTE,AST_DECLARATOR,AST_TYPE_NAME,AST_POINTER,AST_ARRAY,AST_FUNC_PTR}ASTNodeType;
typedef struct{int line;int col;char file[CODE_SCAN_MAX_PATH];}Location;
typedef struct{int id;Location loc;Severity sev;Category cat;int code;char msg[1024];char suggestion[1024];char context[2048];}Issue;
typedef struct{TokenType type;char text[256];int line;int col;long long val;double fval;}Token;
typedef struct{int*data;int cap;int len;}IntArray;
typedef struct{char**data;int cap;int len;}StrArray;
typedef struct{char*data;long long len;long long cap;}Buffer;
typedef struct ASTNode_struct{int type;Token*tok;Location loc;struct ASTNode_struct*parent;struct ASTNode_struct**children;int nchildren;int child_cap;char name[256];long long num_val;double fval;int is_float;char*str_val;int ival;int op;}ASTNode;
struct SourceFile_struct;struct Project_struct;
typedef int(*CheckFunc)(struct SourceFile_struct*,struct Project_struct*,Issue*);
typedef struct{char name[64];CheckFunc func;Category cat;int code;int lang;}Check;
typedef struct Scope_struct{char name[256];struct Scope_struct*parent;struct Symbol_struct*symbols;int nsymbols;int depth;}Scope;
typedef struct Symbol_struct{char name[256];char file[CODE_SCAN_MAX_PATH];int line;int col;int kind;int type_id;int is_static;int is_extern;int is_const;int is_volatile;int is_typedef;int array_size;int ptr_depth;int is_function;int nparams;int defined;int referenced;int declared;struct Symbol_struct*params;struct Symbol_struct*next;struct Symbol_struct*scope_parent;}Symbol;
typedef enum{LANG_UNKNOWN=0,LANG_C,LANG_CPP,LANG_HEADER,LANG_CSHARP,LANG_JAVA,LANG_JS,LANG_TS,LANG_PYTHON,LANG_RUBY,LANG_PHP,LANG_GO,LANG_RUST,LANG_SWIFT,LANG_KOTLIN,LANG_SCALA,LANG_DART,LANG_HASKELL,LANG_LUA,LANG_R,LANG_JULIA,LANG_PERL,LANG_SHELL,LANG_SQL,LANG_HTML,LANG_CSS,LANG_YAML,LANG_MARKDOWN,LANG_XML,LANG_OBJECTIVEC,LANG_GROOVY,LANG_FORTRAN,LANG_COBOL,LANG_BASIC,LANG_PASCAL,LANG_ADA,LANG_LISP,LANG_PROLOG,LANG_ERLANG,LANG_ELIXIR,LANG_CLOJURE,LANG_FSHARP,LANG_VISUALBASIC,LANG_POWERSHELL,LANG_MATLAB,LANG_D,LANG_DOCKERFILE,LANG_JSON,LANG_TOML,LANG_CMAKE,LANG_MAKEFILE,LANG_TEX,LANG_VUE,LANG_SVELTE,LANG_SOLIDITY,LANG_GRAPHQL,LANG_TCL,LANG_COFFEESCRIPT,LANG_NIM,LANG_ZIG,LANG_OCAML,LANG_PURESCRIPT,LANG_RACKET,LANG_SCHEME,LANG_VERILOG,LANG_VHDL,LANG_VALA,LANG_THRIFT,LANG_SMALLTALK,LANG_APL,LANG_AWK,LANG_FORTH,LANG_IDL,LANG_OPENCL,LANG_OPENSCAD,LANG_PROTOBUF,LANG_SAS,LANG_STATA,LANG_VIML}Language;
typedef struct SourceFile_struct{char name[256];char path[CODE_SCAN_MAX_PATH];char*content;long long size;Token*tokens;int ntokens;ASTNode*ast;int has_ast;Scope*scope;Symbol**symbols;int nsymbols;int nissues;Issue*issues;Language lang;char include_guard[256];char**includes;int nincludes;int parsed;}SourceFile;
typedef struct Project_struct{SourceFile**files;int nfiles;int cap;Scope*global_scope;int total_issues;int total_files;int total_lines;int total_tokens;int total_functions;double analysis_time;time_t start_time;char project_name[256];char root_path[CODE_SCAN_MAX_PATH];int max_depth;int max_func_len;int max_params;int check_level;int enable_all;int threads;int verbose;int report_format;char output_path[CODE_SCAN_MAX_PATH];}Project;
typedef struct{int from;int to;char label[64];}CFEdge;
typedef struct BasicBlock_struct{int id;ASTNode*start;ASTNode*end;struct BasicBlock_struct**preds;int npreds;struct BasicBlock_struct**succs;int nsuccs;IntArray*stmts;int visited;int loop_depth;}BasicBlock;
typedef struct{BasicBlock**blocks;int nblocks;int cap;CFEdge*edges;int nedges;int nedge_cap;}CFGraph;
typedef struct{char name[256];int kind;int is_tainted;int taint_source;int is_sanitized;Location def_loc;struct TaintInfo*next;}TaintInfo;
typedef struct{int from_line;int from_col;int to_line;int to_col;char from_file[CODE_SCAN_MAX_PATH];char to_file[CODE_SCAN_MAX_PATH];int is_function_call;int is_include;}Relation;
typedef struct{Relation*data;int len;int cap;}RelationList;
typedef struct{char pattern[256];char message[1024];Category cat;Severity sev;int code;}PatternRule;
typedef struct{Check*checks;int nchecks;int cap;int total_issues;int*check_counts;double*check_times;int verbose;int threads;}Engine;
static inline void ast_add_child(ASTNode*p,ASTNode*c){if(!p||!c)return;c->parent=p;if(p->nchildren>=p->child_cap){p->child_cap=p->child_cap?p->child_cap*2:8;p->children=realloc(p->children,p->child_cap*sizeof(ASTNode*));}p->children[p->nchildren++]=c;}
static inline int ast_nchildren(ASTNode*n){return n?n->nchildren:0;}
static inline ASTNode*ast_child(ASTNode*n,int i){return(n&&n->children&&i>=0&&i<n->nchildren)?n->children[i]:NULL;}
#define LOC_TOK(o,f,i) do{(o)->loc.line=(f)->tokens[(i)].line;(o)->loc.col=(f)->tokens[(i)].col;snprintf((o)->loc.file,sizeof((o)->loc.file),"%s",(f)->path);}while(0)
extern Project*project;
extern int(*code_scan_printf)(const char*,...);
void*code_scan_alloc(size_t sz);void*code_scan_calloc(size_t nm,size_t sz);void*code_scan_realloc(void*p,size_t sz);void code_scan_free(void*p);char*code_scan_strdup(const char*s);char*code_scan_strndup(const char*s,size_t n);int code_scan_snprintf(char*buf,size_t sz,const char*fmt,...);char*code_scan_concat(const char*a,const char*b);int code_scan_starts_with(const char*s,const char*pre);int code_scan_ends_with(const char*s,const char*suf);char*code_scan_trim(char*s);char*code_scan_lower(char*s);int code_scan_str_eq(const char*a,const char*b);long long code_scan_file_size(const char*path);char*code_scan_read_file(const char*path,long long*size);int mthos_is_c_file(const char*path);int mthos_is_h_file(const char*path);int code_scan_is_source_file(const char*path);void code_scan_error(const char*fmt,...);void code_scan_warn(const char*fmt,...);void code_scan_info(const char*fmt,...);void code_scan_debug(const char*fmt,...);IntArray*int_array_new(int cap);void int_array_add(IntArray*a,int v);void int_array_free(IntArray*a);StrArray*str_array_new(int cap);void str_array_add(StrArray*a,char*s);void str_array_free(StrArray*a);Buffer*buffer_new(long long cap);void buffer_append(Buffer*b,const char*data,long long len);void buffer_append_str(Buffer*b,const char*s);void buffer_printf(Buffer*b,const char*fmt,...);void buffer_free(Buffer*b);char*buffer_detach(Buffer*b);
#endif
